#include <bits/stdc++.h>
using namespace std;

#define ff  first
#define ss  second
#define pb  push_back

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  long long n;
  long long h; 
  
  cin >> n >> h;
  
  if ( h > n * n ) cout << "impossible\n";
  else if ( h < 2 * n - 1 ) cout << "impossible\n";
  else {
    if ( n == 1 ) { 
      cout << "1\n";
    }
    else if ( h == 2 || h == n * n - 2 ) cout << "impossible\n";
    else {
      vector <int> use;
      vector <int> dont_use;
    
      int mrk = 0;
      
      for (int i = n; i >= 1; --i) { 
        if ( h == 2 * i + 1 || h < 2 * i - 1 ) { 
          if ( i == n ) mrk = 1, h--;
          else dont_use.push_back (2 * i - 1);
        }
        else {
          use.push_back (2 * i - 1);
          h -= 2 * i - 1;
        }
      }
      
      sort ( use.begin(), use.end() );
      sort ( dont_use.rbegin(), dont_use.rend() );
      
      if (mrk) cout << 2 * n - 1 << " ";
      
      for ( auto &e : use ) cout << e << " ";
      for ( auto &e : dont_use ) cout << e << " ";
      cout << '\n';
    } 
  }
  
}