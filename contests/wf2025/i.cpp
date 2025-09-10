#include <bits/stdc++.h>
using namespace std;
#define next iuhviu
#define ff  first
#define ss  second
#define pb  push_back
#define maxn 55
int pos[maxn];
int next[maxn];

main(){
  
  int n,k;
  cin >> n;
  
  cin >> k;if(k == 1) return 0;
  
  for(int i=1;i<=n;i++){
    
    int max_k = k, k_shift = 0;
    
    for(int j=1;j<n;j++){
      cout << i << " " << 1 << endl;
      cin >> k;if(k == 1) return 0;
      if(k > max_k){
        max_k = k;
        k_shift = j;
      }
    }
    
    cout << i << " " << 1 + k_shift << endl; 
    cin >> k;if(k == 1) return 0;
    
  }
  
  assert(k == n);
  
  for(int i=1;i<=n;i++){
    cout << i << " " << 1 << endl;
    cin >> k;if(k == 1) return 0;
    
    for(int j=1;j<=n;j++)
      if(j != i){
        cout << j << " " << -1 << endl;
        cin >> k;if(k == 1) return 0;
        if(k == n) 
          next[i] = j;
        cout << j << " " << 1 << endl;
        cin >> k;if(k == 1) return 0;
      }
    cout << i << " " << -1 << endl;
    cin >> k;if(k == 1) return 0;
  }
  
  for(int i=0, aux = 1;i<n;i++, aux = next[aux]){
    pos[aux] = i;
  }
  
  for(int i=1;i<=n;i++){
    cout << i << " " << -pos[i] << endl;
    cin >> k;if(k == 1) return 0;
  }
  
}