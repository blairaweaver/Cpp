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

class HW4_p3 : public HW4_p2
{
private: int var2;

public:
	int getgcd()
	{
		int a,b,t;
		a = var;
		b = var2;

		while (b != 0) {
			t = b;
			b = a % b;
			a = t;
		}
		return a;
	}

	HW4_p3(int v, int v2) : HW4_p2(v) {var2=v2; }
};

void usage(char *s)
{
	cerr<<"usage: "<<s<<" <integer1> <integer2>\n";
	exit(0);
}

int main(int argc, char *argv[])
{
	int v,v2,i;
	if(argc!=3) usage(argv[0]);
	v=atoi(argv[1]);
	v2=atoi(argv[2]);
	if(v<=0 || v>50 || v2<=0 || v2>50) {cerr<<"the two integers should be between 1 and 50\n"; exit(0);}
	
	HW4_p3 myhw(v,v2);
	cout<<"iterated integer sequence for "<<v<<" is:"<<endl;
	myhw.play();
	
	cout<<"\ncomputing gcd\n";
	cout<<"The gcd of "<<v<<" and "<<v2<<" is "<<myhw.getgcd()<<endl;
	return 0;
}