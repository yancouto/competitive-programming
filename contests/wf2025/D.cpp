#include <bits/stdc++.h>
using namespace std;

#define ff  first
#define ss  second
#define pb  push_back

const int N = 1e5 + 10;
const int mod = 1e9 + 7;


int dp [N][30];
vector <vector<int>> perms;
string mat[N];
string s;

int R[] = {-2, 0, 0, 1, -1};
int C[] = {-2, 1, -1, 0, 0};

string dirs = "XEWSN"; 

int n, m; 

map <char,int> rev_dir;

bool can_move ( int r, int c, int d ) { 
  int nr = r + R[d];
  int nc = c + C[d];
  if ( nr < 0 || nc < 0 || nr >= n || nc >= m || mat[nr][nc] == '#' ) return false;
  return true;
}

bool can_move_p ( int r, int c, vector<int> perm, char val ) {
  bool valid = true;
  for ( int i = 0; i < 4; ++i ) { 
    if ( dirs[perm[i]] != val ) 
      valid &= !can_move ( r, c, perm[i] );
    else {
      return ( valid && can_move (r, c, perm[i]) );
    }
  }
}

int go ( int idx, int r, int c, int perm ) { 
  if ( idx == s.size() ) return 0;
  
  auto &rf = dp[idx][perm];
  if (rf != -1) return rf;
  
  rf = N;
  for ( int i = 0; i < perms.size(); ++i ) { 
    if ( can_move_p ( r, c, perms[i], s[idx] ) ) {
      int cost = (i != perm);
      rf = min ( rf, go ( idx + 1, r + R[rev_dir[s[idx]]], c + C[rev_dir[s[idx]]], i ) + cost );
    }
  }
  
  return rf;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  rev_dir['E'] = 1;
  rev_dir['W'] = 2;
  rev_dir['S'] = 3;
  rev_dir['N'] = 4;
  
  
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> mat[i];
  cin >> s;
  
  vector <int> perm = {1, 2, 3, 4};
  do {
    perms.pb ( perm );
  } while ( next_permutation (perm.begin(), perm.end()) );
  
  int ini_r = 0, ini_c = 0;
  for ( int i = 0; i < n; ++i ) { 
    for (int j  = 0; j < m; ++j ) { 
      if ( mat[i][j] == 'S' ) ini_r = i, ini_c = j;
    }
  }
  
  memset ( dp, -1, sizeof dp );
  cout << go ( 0, ini_r, ini_c, 25 ) - 1 << '\n';
}
