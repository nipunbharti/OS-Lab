#include <iostream>
using namespace std;

int system_time, current_process=-1;

class SRT{
	private:
		int at, bt, ct, tat, wt, start_time, copy_bt;
		bool flag;

	public:
		SRT() : flag(true) {
			start_time = 0;
			ct=0;
		}

		void input_at()
		{
			cin>>at;
		}

		void input_bt()
		{
			cin>>bt;
			copy_bt = bt;
		}

		int get_at()
		{
			return at;
		}

		int get_bt()
		{
			return bt;
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

		bool get_flag()
		{
			return flag;
		}

		void compute_ct()
		{
			ct = system_time + 1;
		}

		void update_bt()
		{
			bt = bt - (system_time - start_time);
			ct = system_time;
		}

		void update_start_time()
		{
			start_time = system_time;
		}

		void set_flag()
		{
			flag = false;
		}

		void compute_tat()
		{
			tat = ct - at;
		}

		void compute_wt()
		{
			wt = tat - copy_bt;
		}

		int get_copy_bt()
		{
			return copy_bt;
		}

}process[100];

bool compare(SRT p, SRT q)
{
	return p.get_at() < q.get_at();
}

void get_index(int *completetion_flag, int n)
{
	bool change_process = false;
	for(int i=0;i<n;i++){
		if(process[i].get_at() <= system_time){
			if(process[current_process].get_bt() > process[i].get_bt() && process[i].get_bt() != 0){
				process[i].update_start_time();
				process[current_process].update_bt();
				current_process = i;
				change_process = true;
				break;
			}
		}
	}
	if(!change_process){
		process[current_process].update_bt();
		int min_bt = 0;
		for(int i=0;i<n;i++){
			if(process[i].get_at() <= system_time && process[i].get_bt() != 0){
				if(process[i].get_bt() < process[min_bt].get_bt()){
					min_bt = i;
				}
			}
		}
		current_process = min_bt;
		process[current_process].update_start_time();
	}
	for(int i=0;i<n;i++){
		if(process[i].get_bt() == 0 && process[i].get_flag() != false){
			process[i].set_flag();
			(*completetion_flag)--;
		}
		cout<<"Process"<<i<<": "<<process[i].get_bt()<<" "<<process[i].get_ct()<<endl;
	}
	cout<<current_process<<endl;
}

int main()
{
	int n;
	cout<<"Enter the number of processes:";
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
	int completetion_flag = n;
	system_time = process[0].get_at();
	current_process = 0;
	int count=0;
	while(completetion_flag > 0){
		system_time++;
		count++;
		get_index(&completetion_flag, n);
		cout<<"Completion flag: "<<completetion_flag<<endl;
	}
	for(int i=0;i<n;i++){
		process[i].compute_tat();
		process[i].compute_wt();
	}
	cout<<"Pid\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=0;i<n;i++){
		cout<<i+1<<"\t"<<process[i].get_at()<<"\t"<<process[i].get_copy_bt()<<"\t"<<process[i].get_ct()<<"\t"<<process[i].get_tat()<<"\t"<<process[i].get_wt()<<endl;
	}
}