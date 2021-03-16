#include <iostream>
using namespace std;

int main(){
  int have[10]={};
  string s; cin>>s; for (auto i: s) ++have[i-'0'];

  pair<int,int> res={have[0]+2,0};
  for (int i=1; i<10; i++)
    res=min(res,{have[i]+1,i});

  if (res.second==0){
    --res.first;
    cout<<1;
  }
  for (int i=res.first; i--;) cout<<res.second;
  cout<<endl;
}
