#include <iostream>
using namespace std;

int system_time = 0;

class SJF{

	private:
		int at, bt, ct, tat, wt;
		bool flag;

	public:
		SJF() : flag(true) {}

		void input_at()
		{
			cin>>at;
		}

		void input_bt()
		{
			cin>>bt;
		}

		int get_at()
		{
			return at;
		}

		int get_bt()
		{
			return bt;
		}

		bool get_flag()
		{
			return flag;
		}

		void compute_ct()
		{
			ct = system_time + bt;
			system_time = ct;
			flag = false;
		}

		void compute_tat()
		{
			tat = ct - at;
		}

		void compute_wt()
		{
			wt = tat - bt;
		}

		int get_ct()
		{
			return ct;
		}

		int get_tat()
		{
			return tat;
		}

		int get_wt()
		{
			return wt;
		}

}process[100];

int get_index(int n)
{
	int index = -1;
	for(int i=0;i<n;i++)
	{
		if(index == -1)
		{
			if(process[i].get_at()<=system_time && process[i].get_flag()==true)
				index=i;
		}
		else
		{
			if(process[i].get_at()<=system_time && process[i].get_flag()==true && process[i].get_bt()<process[index].get_bt())
				index=i;	
		}
	}
	return index;
}

bool compare(SJF p, SJF q)
{
	return p.get_at() < q.get_at();
}

int main()
{
	int n;
	cout<<"Enter the number of process:";
	cin>>n;
	cout<<"Enter the arrival times:";
	for(int i=0;i<n;i++){
		process[i].input_at();
	}
	cout<<"Enter the burst times:";
	for(int i=0;i<n;i++){
		process[i].input_bt();
	}
	sort(process, process+n, compare);
	system_time = process[0].get_at();
	int prev_ct = 0;
	for(int i=0;i<n;i++){
		int index = get_index(n);
		// if(i!=0 && prev_ct < process[i].get_at()){
			
		// }
		process[index].compute_ct();
		prev_ct = process[index].get_ct();
		process[index].compute_tat();
		process[index].compute_wt();
	}
	cout<<"Pid\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=0;i<n;i++){
		cout<<i+1<<"\t"<<process[i].get_at()<<"\t"<<process[i].get_bt()<<"\t"<<process[i].get_ct()<<"\t"<<process[i].get_tat()<<"\t"<<process[i].get_wt()<<endl;
	}
	int average_wt = 0;
	for(int i=0;i<n;i++){
		average_wt = average_wt + process[i].get_wt();
	}
	average_wt = average_wt/n;
	cout<<"Average waiting time:"<<average_wt<<endl;
	return 0;
}