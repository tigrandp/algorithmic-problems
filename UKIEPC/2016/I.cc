#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	double cost;
	int lawns, ignore;

	cout.precision(8);

	ignore = scanf("%lf", &cost);
	ignore = scanf("%d", &lawns);

	double sum = 0;

	for(int i = 0; i < lawns; i++) {
		double w,l;
		ignore = scanf("%lf %lf", &w, &l);
		sum = sum + (w * l * cost);
	}

	cout<<fixed<<sum<<"\n";
}
