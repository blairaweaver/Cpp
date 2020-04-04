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

class programming2: public programming1 {
	private:
		int var2;
	public:
		programming2(int x, int y):programming1(x){
			var2=y;
		}
		void getgcd () {
			int t, b, a;
			a = var; b = var2;
			while (b != 0) {//Euclidean algorithm
				t = b;
                		b = a % b;
                		a = t;
        		}
			printf("The gcd of %d and %d is %d\n",var, var2, a);
		}
};

int main(int argc, char* argv[]){
	programming2 p1(atoi (argv[1]), atoi (argv[2]));
	printf("iteratedintegre sequence for %d is:\n", atoi (argv[1]));
	p1.play();
	printf("computing gcd\n");
	p1.getgcd();
	return 0;
}
