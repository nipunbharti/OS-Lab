#include <iostream>
using namespace std;

int system_time, current_process=-1;

class Priority_NPE{
	private:
		int pid, at, bt, priority, ct, tat, wt;
		bool flag;

	public:
		Priority_NPE() : flag(true) {}

		void input_pid()
		{
			cin>>pid;
		}

		void input_at()
		{
			cin>>at;
		}

		void input_bt()
		{
			cin>>bt;
		}

		void input_priority()
		{
			cin>>priority;
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

		int get_priority()
		{
			return priority;
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

		int get_pid()
		{
			return pid;
		}

}process[100];

bool compare(Priority_NPE p, Priority_NPE q)
{
	return p.get_at() < q.get_at();
}

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
			if(process[i].get_at()<=system_time && process[i].get_flag()==true && process[i].get_priority()>process[index].get_priority())
				index=i;
		}
	}
	return index;
}

int get_arrival_of_next_process(int n)
{
	int count = 0;
	for(int i=0;i<n;i++){
		if(process[i].get_at() < system_time && process[i].get_flag() == true){
			count++;
		}
	}
	if(count == 0){
		return -1;
	}
	else{
		return 1;
	}
}

void update_system_time(int n)
{
	int copy = system_time;
	int closest = system_time;
	for(int i=0;i<n;i++){
		if(process[i].get_at() > system_time && process[i].get_flag() == true){
			copy = process[i].get_at();
			closest = copy;
			break;	
		}
	}
	system_time = copy;
}

int main()
{
	int n;
	cout<<"Enter the number of processes:";
	cin>>n;
	cout<<"Enter the pid, arrival times, burst times and priority:"<<endl;
	for(int i=0;i<n;i++){
		cout<<"Process "<<i+1<<":";
		process[i].input_pid();
		process[i].input_at();
		process[i].input_bt();
		process[i].input_priority();
	}
	sort(process, process+n, compare);
	system_time = process[0].get_at();
	for(int i=0;i<n;i++){
		int index = get_index(n);
		process[index].compute_ct();
		process[index].compute_tat();
		process[index].compute_wt();
		cout<<"Before:"<<system_time<<endl;
		if(get_arrival_of_next_process(n) == -1){
			update_system_time(n);
			cout<<system_time<<endl;
		}
	}
	cout<<"Pid\tAT\tBT\tPriority\tCT\tTAT\tWT"<<endl;
	for(int i=0;i<n;i++){
		cout<<process[i].get_pid()<<"\t"<<process[i].get_at()<<"\t"<<process[i].get_bt()<<"\t"<<process[i].get_priority()<<"\t"<<process[i].get_ct()<<"\t"<<process[i].get_tat()<<"\t"<<process[i].get_wt()<<endl;
	}
}