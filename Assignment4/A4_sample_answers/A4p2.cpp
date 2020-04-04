#include <iostream>
#include <stdlib.h>

using namespace std;

class HW4_p2
{
protected: int var;

public:
	void play()
	{
		int t=var;
		cout<<t<<"\t"; 
		while(t!=1) 
		{
			if(t%2)
				t=3*t+1;
			else
				t=t/2;
			cout<<t<<"\t";
		}
		cout<<endl;
	}

	HW4_p2(int v) {var = v;}
};

void usage(char *s)
{
	cerr<<"usage: "<<s<<" <integer>\n";
	exit(0);
}

int main(int argc, char *argv[])
{
	int v;
	if(argc!=2) usage(argv[0]);
	v=atoi(argv[1]);
	if(v<=0 || v>50) {cerr<<"<integer> should be between 1 and 50\n"; exit(0);}
	
	HW4_p2 myhw(v);
	myhw.play();
	return 0;
}