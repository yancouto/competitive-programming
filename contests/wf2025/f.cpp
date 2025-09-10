#include <bits/stdc++.h>
using namespace std;

#define ff  first
#define ss  second
#define pb  push_back

const int N = 1e5 + 10;
const int mod = 1e9 + 7;
#define pb push_back
#define maxn 200200

int tgt[maxn];
vector<int> cats[maxn];
vector<int> opts[maxn];

int used[maxn];
int mrk[maxn];

main(){
  
  int nt;
  cin >> nt;
  while(nt--){
    int n,m;
    cin >> n >> m;
    
    for(int i=0;i<n;i++)
      opts[i].clear();
      
    for(int i=1;i<=m;i++)
      cats[i].clear(), used[i] = mrk[i] = 0;
    
    for(int i=0;i<n;i++){
      int k;
      cin >> tgt[i] >> k;
      cats[tgt[i]].pb(i);
      while(k--){
        int val;
        cin >> val;
        opts[i].pb(val);
      }
    }
    
    int bad = 0;
    int free_slots = 0;
    
    for(int pos=m;pos>=1;pos--){
      
      int mxval = 0;
      int new_slots = 0;
      
      for(int c : cats[pos]){
        
        for(int id : opts[c]){
          
          if(!used[id]){
            mrk[id]++;
            if(mrk[id] == 1)
              new_slots++;
            mxval = max(mxval, mrk[id]);
          }
          
        }
        
      }
      
      for(int c : cats[pos])
        for(int id : opts[c])
          used[id] = 1;
      
      if(mxval != cats[pos].size())
        bad = 1;
        
      if(cats[pos].size() == 0){
        free_slots++;
        continue;
      }
      
      free_slots++;
      
      if(new_slots > free_slots)
        bad = 1;
      
      free_slots -= new_slots;
      
    }
    
    if(bad)
      cout << "no" << endl;
    else 
      cout << "yes" << endl;
    
    
  }
  
}