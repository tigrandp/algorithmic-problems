#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long double ld;

int main(){
  long long n; cin>>n;
  cout.precision(10);

  if (n<=10){
    ld fact[1001]={1.L};
    ld res[1001]={};
    for (int i=1; i<=n; i++){
      fact[i]=fact[i-1]*i;
    }

    res[0]=1;
    for (int i=2; i<=n; i++){
      res[i]=(res[i-1]+res[i-2])*(i-1);
    }

    cout<<fixed<<1-res[n]/fact[n]<<endl;
  }else{
    cout<<fixed<<1-1/M_E<<endl;
  }
}
