// #include <iostream>
// #include <algorithm>
// using namespace std;

// int system_time;

// class FCFS
// {
// 	private:
// 		int pid, at, bt;
// 	public:
// 		void input_at(){
// 			cin>>at;
// 		}
// 		void input_bt(){
// 			cin>>bt;
// 		}
// 		void output(){
// 			cout<<pid<<at<<bt<<endl;
// 		}
// 		int returnBT(){
// 			return bt;
// 		}
// 		int returnAT(){
// 			return at;
// 		}
// }process[100];

// bool compare(FCFS p, FCFS q)
// {
// 	return p.returnAT() < q.returnAT();
// }

// int no_of_process(int n)
// {
// 	int count = 0;
// 	for(int i=1;i<n;i++){
// 		if(process[i].returnAT() <= system_time){
// 			count++;
// 		}
// 	}
// 	return count;
// }

// int main()
// {
// 	int n;
// 	cout<<"Enter the number of processes:";
// 	cin>>n;
// 	int ct[n], tat[n], wt[n];
// 	cout<<"Enter the arrival time:";
// 	for(int i=0;i<n;i++){
// 		process[i].input_at();
// 	}
// 	cout<<"Enter the burst time:";
// 	for(int i=0;i<n;i++){
// 		process[i].input_bt();
// 	}

// 	sort(process, process+n, compare);
	
// 	ct[0] = process[0].returnBT();
// 	system_time = ct[0];
// 	for(int i=1;i<n+1;i++){
// 		int c = no_of_process(n);
// 		if(i != n+1){
// 			ct[i] = ct[i-1] + process[i].returnBT();
// 		}
// 		tat[i-1] = ct[i-1] - process[i-1].returnAT();
// 		wt[i-1] = tat[i-1] - process[i-1].returnBT();
// 	}

// 	for(int i=0;i<n;i++){
// 	}

// 	cout<<"Pid\tAT\tBT\tCT\tTAT\tWT"<<endl;
// 	for(int i=0;i<n;i++){
// 		cout<<i+1<<"\t"<<process[i].returnAT()<<"\t"<<process[i].returnBT()<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
// 	}

// 	return 0;
// }


#include <iostream>
#include <algorithm>
using namespace std;

int systemTime,avgWtTime = 0;

class process
{
	private:
		int pid,at,bt,ct,tat,wt;
	public:
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
			systemTime = ct;
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

int main()
{
	int n;
	cout<<"Enter No. of Processes\n";
	cin>>n;

	process p[n];

	for(int i=0;i<n;i++)
	{
		cout<<"Process "<<i+1<<endl;
		p[i].setPid();
		p[i].setAt();
		p[i].setBt();
	}

	sort(p,p+n,comparator);
	systemTime = p[0].getAt();

	for(int i=0;i<n+1;i++)
	{
		p[i].computeCt();
		p[i].computeTat();
		p[i].computeWt();
		if(i!=n-1 && p[i].getCt()<p[i+1].getAt()){
			systemTime = p[i+1].getAt();
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