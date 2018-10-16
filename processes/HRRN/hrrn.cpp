/*
Author:- Yashovardhan Siramdas
CED16I028

Lab Session 2, 31-07-18
Highest Response Ratio Next
*/

#include <iostream>
#include <algorithm>
using namespace std;

int systemTime,avgWtTime = 0;

class process
{
	private:
		int pid,at,ct,tat,wt;
		float bt,r;
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
		void computeCt()
		{
			ct = systemTime + bt;
			flag = true;
		}
		void computeTat()
		{
			tat = ct - at;
		}
		void computeWt()
		{
			wt = systemTime - at;
		}
		void computeResponseRatio()
		{
			computeWt();
			r = 1 + (wt/bt);
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
		float getResponseRatio()
		{
			return r;
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
	}

	sort(p,p+n,comparator);
	systemTime = p[0].getAt();
	for(int i=0;i<n;i++)
	{
		p[i].computeWt();
		p[i].computeResponseRatio();
	}

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
					processCounter++;
				}
			}
			else
			{
				if(p[j].getFlag()==false && p[j].getAt()<=systemTime && p[j].getResponseRatio()>p[currentProcess].getResponseRatio())
				{
					currentProcess = j;
					processCounter++;
				}
			}
		}

		p[currentProcess].computeCt();
		p[currentProcess].computeTat();
		p[currentProcess].computeWt();
		systemTime = p[currentProcess].getCt();
		syncSystemTime(p,n);
		for(int k=0;k<n;k++)
		{
			if(p[k].getFlag() == false)
			{
				p[k].computeResponseRatio();
			}
		}

	}

	cout<<"pid\tat\tbt\tct\ttat\twt\n";
	for(int i=0;i<n;i++)
		cout<<p[i].getPid()<<"\t"<<p[i].getAt()<<"\t"<<p[i].getBt()<<"\t"<<p[i].getCt()<<"\t"<<p[i].getTat()<<"\t"<<p[i].getWt()<<"\t"<<endl;

	for(int i=0;i<n;i++)
		avgWtTime += p[i].getWt();

	avgWtTime = avgWtTime / n;

	cout<<"Avg Wt: "<<avgWtTime<<endl;

}