#include <iostream>
#include <iomanip>
using namespace std;

typedef long double ld;

ld s[20];
ld p[20];
ld over_band;

ld e[20];
ld m[20];

ld g[20];

int main(){
  // Get the data
  int b; cin>>b;
  cout.precision(3);

  for (int i=0; i<b; i++){
    cin>>s[i]>>p[i];
    p[i] = p[i] / 100;
  }
  cin>>over_band;
  over_band = over_band / 100;

  int f; cin>>f;

  for(int j=0; j < f; j++){
    cin>>e[j]>>m[j];

    ld my_e = e[j];
    int k;
    ld t = 0;
    // work out what tax brand we start in.
    for(k = 0; k < b ; k++) {
      my_e -= s[k];
      if (my_e <= 0) {
        // we've found the tax band to start in.
        if (my_e + (m[j] / (1 - p[k])) < 0) {
          // Even with the interest, we're still in the band. leave here.
          t += m[j] / (1 - p[k]);
          m[j] = 0;
          break;
        } else {
          // adding the tax on moves us up a band.
          t -= my_e; // ADD the space that was left in this band.
          m[j] += -my_e * p[k]; // Add the tax onto the total for the space.
          m[j] += my_e; // Remove the space from this band.
          my_e = 0; // reset to 0
        }
      }  
    }
    if (m[j] > 0) {
      // we have some left that needs to be taxed at the top rate.
      t += m[j] / (1 - over_band);
    }

    
    cout<<fixed<<t<<"\n";
  }
}
