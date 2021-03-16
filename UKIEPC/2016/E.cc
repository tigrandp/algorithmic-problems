#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;



uint32_t cost[441][441];
uint32_t dist[441][441];

int main(){
  for (int i=441; i--;) for (int j=441; j--;) cost[i][j]=dist[i][j]=(1u<<29u);
  deque<pair<int,int>> todo;

  int c,r; cin>>r>>c;
  for (int i=1; i<=r; i++){
    string row; cin>>row;
    for (int j=1; j<=c; j++) switch (row[j-1]){
      case 'D': cost[i][j]=0; if (i==1 or j==1 or i==r or j==c) dist[i][j]=0, todo.push_back({i,j}); break;
      case 'c': cost[i][j]=1; break;
      case '.': cost[i][j]=0; break;
    }
  }

  int tc,tr; cin>>tr>>tc;
  assert(cost[tr][tc]==1);

  while (not todo.empty()){
    int r=todo.front().first,c=todo.front().second;todo.pop_front();
    for (int dr=1,dc=0,z=4; z--; swap(dr,dc*=-1)){
      int a=r+dr,b=c+dc;
      if (dist[r][c]+cost[a][b]<dist[a][b]){
        todo.push_back({a,b});
        dist[a][b]=dist[r][c]+cost[a][b];
      }
    }
  }

  if (dist[tr][tc]==(1u<<29u)) {
    cout<<"IMPOSSIBLE"<<endl;
  }else{
    cout<<dist[tr][tc]<<endl;
  }
}
