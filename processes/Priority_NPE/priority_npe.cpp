/*
Author:- Yashovardhan Siramdas
CED16I028

Lab Session 2, 31-07-18
Priority,Non Premptive
*/

#include <iostream>
#include <algorithm>
using namespace std;

int systemTime,avgWtTime = 0;

class process
{
	private:
		int pid,at,bt,p,ct,tat,wt;
		bool flag;
	public:
		void initFlag()
		{
			flag = false;
		}
		void setPid()
		{
			cout<<"Enter pid:- ";
			cin>>pid;
		}
		void setAt()
		{
			cout<<"Enter at:- ";
			cin>>at;
		}
		void setBt()
		{
			cout<<"Enter bt:- ";
			cin>>bt;
		}
		void setP()
		{
			cout<<"Enter p:- ";
			cin>>p;
		}
		void computeCt()
		{
			ct = systemTime + bt;
			systemTime = ct;
			flag = true;
		}
		void computeTat()
		{
			tat = ct - at;
		}
		void computeWt()
		{
			wt = tat - bt;
		}
		int getPid()
		{
			return pid;
		}
		int getAt()
		{
			return at;
		}
		int getBt()
		{
			return bt;
		}
		int getP()
		{
			return p;
		}
		int getFlag()
		{
			return flag;
		}
		int getCt()
		{
			return ct;
		}
		int getTat()
		{
			return tat;
		}
		int getWt()
		{
			return wt;
		}

};

bool comparator(process p, process q)
{
	return (p.getAt() < q.getAt());
}

void syncSystemTime(process p[],int n)
{
	int processCounter = 0,currentProcess=-1;	
	for(int i=0;i<n;i++)
	{
		if(p[i].getFlag() == false && processCounter == 0)
		{
			currentProcess = i;
			processCounter++;
		}
		else if(p[i].getFlag() == false && processCounter != 0)
		{
			if(p[currentProcess].getAt()>p[i].getAt())
			{
				currentProcess = i;
				processCounter++;
			}
		}
	}
	if(p[currentProcess].getAt() > systemTime)
	{
		systemTime = p[currentProcess].getAt();
	}
}

int main()
{
	int n;
	cout<<"Enter No. of Processes\n";
	cin>>n;

	process p[n];

	for(int i=0;i<n;i++)
	{
		cout<<"Process "<<i+1<<endl;
		p[i].initFlag();
		p[i].setPid();
		p[i].setAt();
		p[i].setBt();
		p[i].setP();
	}

	sort(p,p+n,comparator);
	systemTime = p[0].getAt();

	for(int i=0;i<n;i++)
	{
		int processCounter = 0,currentProcess = -1;
		for(int j=0;j<n;j++)
		{
			if(processCounter==0)
			{
				if(p[j].getFlag()==false && p[j].getAt()<=systemTime)
				{
					currentProcess = j;
					processCounter = 1;
				}
			}
			else
			{
				if(p[j].getFlag()==false && p[j].getAt()<=systemTime && p[j].getP()>p[currentProcess].getP())
				{
					currentProcess = j;
					processCounter++;
				}
			}
		}

		p[currentProcess].computeCt();
		p[currentProcess].computeTat();
		p[currentProcess].computeWt();
		syncSystemTime(p,n);

	}




	cout<<"pid\tat\tbt\tp\tct\ttat\twt\n";
	for(int i=0;i<n;i++)
		cout<<p[i].getPid()<<"\t"<<p[i].getAt()<<"\t"<<p[i].getBt()<<"\t"<<p[i].getP()<<"\t"<<p[i].getCt()<<"\t"<<p[i].getTat()<<"\t"<<p[i].getWt()<<"\t"<<endl;

	for(int i=0;i<n;i++)
		avgWtTime += p[i].getWt();

	avgWtTime = avgWtTime / n;

	cout<<"Avg Wt: "<<avgWtTime<<endl;

}