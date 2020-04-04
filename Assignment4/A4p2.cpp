#include <iostream>
using namespace std;

class programming1 {
	protected:
		int var, org;
	public:
		programming1(int x){
			var = x;
			org = var;
		}
		void play () {
			if (var ==1) {
				printf("%d\n", var);
				var = org;
			}
			else if (var%2) {
				printf("%d\t", var);
				var = 3*var + 1;
				play();
			}
			else {
				printf("%d\t", var);
				var = var/2;
				play();
			}
		}
};

int main(int argc, char* argv[]){
	int x = atoi (argv[1]);
	if(x<50 && x>1){
	programming1 p1(atoi (argv[1]));
	p1.play();
	}
	else printf("Integer x, %d, not between 1 and 50\n", x);
	return 0;
}
