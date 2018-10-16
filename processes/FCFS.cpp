#include <iostream>
#include <algorithm>
using namespace std;

class FCFS
{
	private:
		int pid, at, bt;
	public:
		void input_at(){
			cin>>at;
		}
		void input_bt(){
			cin>>bt;
		}
		void output(){
			cout<<pid<<at<<bt<<endl;
		}
		int returnBT(){
			return bt;
		}
		int returnAT(){
			return at;
		}
};

int main()
{
	int n;
	cout<<"Enter the number of processes:";
	cin>>n;
	FCFS process[n];
	int ct[n], tat[n], wt[n];
	cout<<"Enter the arrival time:";
	for(int i=0;i<n;i++){
		process[i].input_at();
	}
	cout<<"Enter the burst time:";
	for(int i=0;i<n;i++){
		process[i].input_bt();
	}
	
	ct[0] = process[0].returnBT();
	for(int i=1;i<n;i++){
		ct[i] = ct[i-1] + process[i].returnBT();
	}

	for(int i=0;i<n;i++){
		cout<<"Process:"<<i+1<<ct[i]<<endl;
	}

	for(int i=0;i<n;i++){
		tat[i] = ct[i] - process[i].returnAT();
	}

	for(int i=0;i<n;i++){
		wt[i] = tat[i] - process[i].returnBT();
	}

	cout<<"Pid\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=0;i<n;i++){
		cout<<i+1<<"\t"<<process[i].returnAT()<<"\t"<<process[i].returnBT()<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
	}
	int average_wt = 0;
	for(int i=0;i<n;i++){
		average_wt = average_wt + wt[i];
	}
	average_wt = average_wt/n;
	cout<<"Average waiting time:"<<average_wt<<endl;

	return 0;
}