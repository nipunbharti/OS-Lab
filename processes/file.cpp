   // Universal Directory for all Header Files
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include<iostream>
#include<time.h>
#include<sys/stat.h>
#include<string>
#include<fstream>

using namespace std;

int n;		//No of Text File
int ST;			//System Clock	  	
struct process
{
	int pid,at,bt,ct,tat,wt,p,mark,flag,rat;
	string time;
}pr[100];

struct File
{
	char str[100];
}F[100];

void init()
{
	for(int i=0;i<100;i++)
	{
		pr[i].at=pr[i].bt=pr[i].ct=pr[i].tat=pr[i].wt=pr[i].mark=pr[i].p=pr[i].flag=0;
		pr[i].pid=i;
	}
}

int wc(string temp)
{
	ifstream inFile;
	string word;
	int count=0;
	
	inFile.open(temp.c_str());

	while(inFile >> word){++count;}
	inFile.close();
	
	return count;
}

class fcfs
{
	private:
		process fc[100],rr[100];
		
			
	public:
		void intit()
		{
			for(int i=0;i<100;i++)
				pr[i].ct=pr[i].tat=pr[i].wt=pr[i].mark=pr[i].flag=pr[i].rat=0;
		}
		void disp(process temp[])
		{
			float avg=0;
			for(int i=0;i<n;i++)
				avg=avg+temp[i].wt;
			cout<<"The Average Waiting Time is : "<<avg/n<<endl;
			cout<<"PID\tTime\t\t\t\tAT\tBT\tP\tCT\tTAT\tWT\n";
			for(int i=0;i<n;i++)
				cout<<pr[i].pid<<"\t"<<pr[i].time<<"\t"<<temp[i].at<<"\t"<<pr[i].bt<<"\t"<<pr[i].p<<"\t"<<temp[i].ct<<"\t"<<temp[i].tat<<"\t"<<temp[i].wt<<endl;
		}
		int minarr(process temp[], int s)
		{
			int min=temp[0].at,minp=temp[0].p;
			int pn=0;
			for(int i=1;i<n;i++)
			{
				if(temp[i].at<=min)
				{
					if(s==0)
					{
						min=temp[i].at;
						minp=temp[i].bt;
						pn=i;
					}
					else if(s==1 && minp<temp[i].p)
					{
						min=temp[i].at;
						minp=temp[i].p;
						pn=i;	
					}
					
				}

			}
			//cout<<pn<<endl;	
			return pn;	
		}
		int nxtjob(int s,process temp[])
		{
			int pn=s,min;
			for(int i=0;i<n;i++)
				if(temp[i].flag==0 && temp[i].at<=ST && temp[i].mark!=1)
				{
					min=temp[i].at;
					pn=i;
					break;
				}
			
			for(int i=0;i<n;i++)
				if(temp[i].at<min && ST>=temp[i].at && temp[i].flag==0 && temp[i].mark!=1)
				{
					min=temp[i].at;
					pn=i;
				}
			return pn;
		}
		int minat(process temp[])
		{
			int min;
			int pn=0;
			
			for(int i=0;i<n;i++)
				if(temp[i].flag==0 && temp[i].mark==0)
				{
					min=temp[i].at;
					pn=i;
					break;
				}
			for(int i=0;i<n;i++)
				if(temp[i].at<min && temp[i].flag==0 && temp[i].mark==0)
				{
					min=temp[i].at;
					pn=i;
				}
			return pn;
		}
		int check(process temp[])
		{
			for(int i=0;i<n;i++)
				if(ST>temp[i].at && temp[i].flag==0 && temp[i].mark==0)
					return 1;
			
			return 0;
		}
		int mcheck(process temp[])
		{
			for(int i=0;i<n;i++)
				if(temp[i].mark==0)
					return 0;
			return 1;
		}

		// Assignment of valid Arrival Pts
		void trat(process temp[])
		{
			int end=0,min,start=0,pn;
			while(end!=1)
			{
				end=1;
				for(int i=0;i<n;i++)
					if(temp[i].rat==0)
					{
						min=temp[i].at;
						pn=i;
						break;
					}
				for(int i=0;i<n;i++)
					if(min>temp[i].at && temp[i].rat==0)
					{
						min=temp[i].at;
						pn=i;
					}

				temp[pn].at=start;
				temp[pn].rat=1;
				start++;

				for(int i=0;i<n;i++)
					if(temp[i].rat==0)
					{	

						end=0;
						break;
					}
			}
		}
		// Driver function for running Round Robin
		void rrmain()
		{
			intit();
			ST=0;
			int end=0;
			for(int i=0;i<n;i++)
				rr[i]=pr[i];
			int tq,np;

			cout<<"Time Quanta : ";
			cin>>tq;
			//disp(rr);
			trat(rr);
			//disp(rr);
			int pre=minarr(rr,0);
			ST=rr[pre].at;
			rr[pre].mark=1;
			queue <int> qu;
			qu.push(pre);
			while(end!=1)
			{
				np=0;
				if(rr[pre].bt>tq)
				{	
					rr[pre].bt=rr[pre].bt-tq;
					ST=ST+tq;
					np=0;
				}
				else
				{
					ST=ST+rr[pre].bt;
					rr[pre].ct=ST;
					rr[pre].bt=0;
					rr[pre].flag=1;
					qu.pop();
					np=1;

				}
				if(mcheck(rr)==0 && check(rr)==0 && qu.empty())
					ST=rr[minat(rr)].at;
				
				for(int i=0;i<n;i++)
				{
					if(rr[nxtjob(pre,rr)].mark!=1)
					{
						qu.push(nxtjob(pre,rr));
						rr[nxtjob(pre,rr)].mark=1;
					}
				}
				if(np==0)
				{
					pre=qu.front();
					qu.pop();
					qu.push(pre);
				}
				pre=qu.front();

				if(qu.empty())
					end=1;
			}
			for(int i=0;i<n;i++)
			{
				rr[i].tat=rr[i].ct-rr[i].at;
				rr[i].wt=rr[i].tat-pr[i].bt;
			}
			disp(rr);


		}
		
}fq;


int main()
{
	n=4;      // No of text Files
	init();
	strcpy(F[0].str,"File3.txt");
	strcpy(F[1].str,"File4.txt");
	strcpy(F[2].str,"File1.txt");
	strcpy(F[3].str,"File2.txt");
	
	// Timestamp and Word count
	struct stat time;
	for(int i=0;i<n;i++)    
	{
		stat(F[i].str,&time);
		struct tm * timeinfo(localtime(&time.st_ctime));
		pr[i].time=asctime(timeinfo);
		pr[i].time.erase(pr[i].time.find_last_not_of("\n\r\t")+1);
		pr[i].at=mktime(timeinfo);  // Storing Value in Process Structure in ms
		pr[i].bt=wc(F[i].str);

	}
	fq.rrmain();
	return 0;
}