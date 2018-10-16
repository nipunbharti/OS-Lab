#include <iostream>
#include <queue>
using namespace std;

int system_time, current_process=-1;
queue <int> ready_queue;

class SRT{
	private:
		int pid, at, bt, ct, tat, wt, start_time, copy_bt;
		bool flag;

	public:
		SRT() : flag(true) {
			start_time = 0;
			ct=0;
		}

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
			copy_bt = bt;
		}

		int get_pid()
		{
			return pid;
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
			ct = system_time + 2;
		}

		void update_bt(int tq)
		{
			if(bt<tq){
				system_time+=(tq-bt);
				bt = 0;
				// ct = system_time;
			}
			else{
				system_time+=tq;
				bt-=2;
				// ct = system_time;
			}
			cout<<"AT:"<<at<<endl;
			cout<<"BT:"<<bt<<endl;
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

void showq(queue <int> gq)
{
    queue <int> g = gq;
    cout<<"Queue:";
    while (!g.empty())
    {
        cout <<g.front();
        g.pop();
    }
    cout <<'\n';
}

bool check_in_queue(int pid)
{
	queue <int> g = ready_queue;
	int flag = false;
	while (!g.empty())
    {
        if(pid == g.front()){
        	flag = true;
        	break;
        }
        g.pop();
    }
    return flag;
}

bool compare(SRT p, SRT q)
{
	return p.get_at() < q.get_at();
}

int get_process_index(queue <int> q, int n)
{
	for(int i=0;i<n;i++){
		if(process[i].get_pid() == ready_queue.front()){
			return i;
		}
	}
	return -1;
}

void get_index(int *completetion_flag, int n, int time_quanta)
{
	if(ready_queue.size() == 0){
		// cout<<"Empty"<<endl;
		for(int i=0;i<n;i++){
			if(process[i].get_flag() == true){
				system_time = process[i].get_at();
				// ready_queue.push(process[i].get_pid());
				// cout<<"Empty:"<<process[ready_queue.front()].get_at()<<endl;
				break;
			}
		}
	}
	int index = get_process_index(ready_queue, n);
	if(index != -1){
		process[index].update_bt(time_quanta);
	}
	for(int i=0;i<n;i++){
		if(process[i].get_at() <= system_time && process[i].get_flag() && !check_in_queue(process[i].get_pid())){
			ready_queue.push(process[i].get_pid());
		}
	}
	if(index != -1){
		if(process[index].get_bt()>0){
			ready_queue.push(ready_queue.front());
			ready_queue.pop();
		}
		else{
			process[index].set_flag();
			ready_queue.pop();
		}
	}
	int count=0;
	for(int i=0;i<n;i++){
		if(process[i].get_flag() == true){
			count++;
		}
	}
	*completetion_flag = count;
	cout<<"system_time:"<<system_time<<endl;
	showq(ready_queue);
}

int main()
{
	int n, time_quanta;
	cout<<"Enter the number of processes:";
	cin>>n;
	cout<<"Enter the time quanta:";
	cin>>time_quanta;
	cout<<"Enter the pid, arrival times and busrt times:";
	for(int i=0;i<n;i++){
		process[i].input_pid();
		process[i].input_at();
		process[i].input_bt();
	}
	sort(process, process+n, compare);
	ready_queue.push(process[0].get_pid());
	int completetion_flag = n;
	system_time = process[0].get_at();
	// if(system_time != 0){

	// }
	current_process = 0;
	int count=0;
	while(ready_queue.size() > 0 || completetion_flag!=0){
		get_index(&completetion_flag, n, time_quanta);
	}
	for(int i=0;i<n;i++){
		process[i].compute_tat();
		process[i].compute_wt();
	}
	// cout<<"Pid\tAT\tBT\tCT"<<endl;
	// for(int i=0;i<n;i++){
	// 	cout<<i+1<<"\t"<<process[i].get_at()<<"\t"<<process[i].get_bt()<<"\t"<<process[i].get_ct()<<endl;
	// }
	cout<<"Pid\tAT\tBT\tCT\tTAT\tWT"<<endl;
	for(int i=0;i<n;i++){
		cout<<process[i].get_pid()<<"\t"<<process[i].get_at()<<"\t"<<process[i].get_copy_bt()<<"\t"<<process[i].get_ct()<<"\t"<<process[i].get_tat()<<"\t"<<process[i].get_wt()<<endl;
	}
}