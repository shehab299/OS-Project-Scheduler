#include<iostream>
#include"pair.h"
#include<queue>
using namespace std;
class Process
{
	const int PID;
	const int AT;
	const int CU;
	int RT;
	int TT;
	int TRT;
	int WT;
	int FT;
	int IO;
	Process* child;
	queue <pair<int>>IOQ;
public:		
	Process(int p,int a,int c);
	Process(const Process & p);	
	void set_TT(int t=0);
	void set_WT();
	void set_TRT();
	void set_RT(int t=0);
	void set_IO(int t=0);
	void set_FT(int t=0);	
	void run();
	void runIO();
	int get_PID()const;
	int get_AT()const;
	int get_CU()const;
	int get_RT()const;
	int get_WT()const;
	int get_PID()const;
	int get_TRT()const;
	int get_FT()const;
	bool needIO();
	bool can_Migrate_RR_SJF(int RTF)const;
	bool can_Migrate_FCFS_RR(int MAXW)const;
	bool canFork(double f)const;
	~Process();
};
Process::Process(int p,int a,int c):PID(p),AT(a),CU(c)
{

}
void Process::set_TT(int t=0)
{
	TT=(t>=0)?t:0;
}
void Process::set_FT(int t=0)
{
	FT=(t>=0)?t:0;
}
void Process::set_TRT()
{
	TRT=TT-AT;
}
void Process::set_WT()
{
	WT=TRT-CU;
}
void Process::set_RT(int t=0)
{
	RT=((t-AT)>=0)?(t-AT):0;
}
void Process::set_IO(int t=0)
{
	IO=(t>=0)?t:0;
}

int Process::get_AT()const
{
	return AT;
}
int Process::get_PID()const
{
	return PID;
}
int Process::get_CU()const
{
	return CU;
}
int Process::get_TRT()const
{
	return TRT;
}
int Process::get_WT()const
{
	return WT;
}
int Process::get_RT()const
{
	return RT;
}
int Process::get_FT()const
{
	return FT;
}
bool Process::can_Migrate_RR_SJF(int RTF)const
{
	return(FT<RTF);
}
bool Process::can_Migrate_RR_SJF(int RTF)const
{
	return(FT<RTF);
}
bool Process::can_Migrate_FCFS_RR(int MAXW)const
{
	return (WT>MAXW);
}
bool Process::needIO()
{
	if(IOQ.empty())
		return false;
	else
	{
		pair<int> cur=IOQ.front();
		if(cur.get_first()==FT)
		{			
			set_IO(cur.get_second());
			IOQ.pop();
			return true;
		}
	}
}
 Process::~Process()
 {
	 delete child;
 }







