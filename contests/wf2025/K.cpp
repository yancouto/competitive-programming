#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 6e5 + 10;
const int oo = 2e18 + 10;

vector < pair <int,int> > g[N];
int component[N];
int cnt = 1;
int min_f[N], min_g[N];
int val[N];
int impo = 0;
vector < int > nodes_f[N];
vector < int > nodes_g[N];

void dfs ( int u, int valu, int ty ) { 
  component[u] = cnt;
  val[u] = valu;
  if ( ty == 0 )
    min_f[ cnt ] = min ( min_f[ cnt ], valu ), nodes_f[ cnt ].push_back (u);
  else min_g [ cnt ] = min ( min_g[cnt], valu ), nodes_g[ cnt ].push_back (u);
  
  for ( auto &v : g[u] ) { 
    if ( component[v.first] ) {
      if ( v.second != valu + val[v.first] ) impo = 1;
    }
    else {
      dfs ( v.first, v.second - valu, ty ^ 1 );
    }
  }
}

 main () { 
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  for (int i = 0; i < N; ++i) { 
    min_f[i] = min_g[i] = oo;
  }
  
  int n, m, k, tx, ty; cin >> n >> m >> k >> tx >> ty;
  for ( int i = 0 ;i  < k; ++i ) { 
    int u, v, val; cin >> u >> v >> val;
    
    g[u].push_back ({v + n, val});
    g[v + n].push_back ({u, val});
  }
  
  for ( int i = 1; i <= n + m; ++i ) {
    if ( !component[i] ) {
      dfs ( i, 0, (i<=n) );
      if ( min_f[ cnt ] + min_g [ cnt ] < 0 ) impo = 1;
      if ( min_f[ cnt ] <= 0 ) { 
        for ( auto &e : nodes_g[ cnt ] ) val[e] += min_f[cnt];
        for ( auto &e : nodes_f[ cnt ] ) val[e] -= min_f[cnt];
        min_g[cnt] += min_f[cnt];
        min_f[cnt] = 0;
      }
      else {
        for ( auto &e : nodes_f[ cnt ] ) val[e] += min_g[cnt];
        for ( auto &e : nodes_g[ cnt ] ) val[e] -= min_g[cnt];
        min_f[cnt] += min_g[cnt];
        min_g[cnt] = 0;
      }
      cnt++;
    }
  }
  
  if ( impo ) cout << "impossible\n";
  else { 
    if ( component[tx] == component[ty + n] ) cout << val[tx] + val[ty + n] << '\n';
    else {
      int vm = min_f [component[tx]];
      int v2 = min_g [component[ty + n]];
      cout << val[tx] + val[ty + n] - (vm + v2) << '\n';
    }
  }
}