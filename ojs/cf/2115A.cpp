
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
int a[5123];

int solve(int i, int cur) {
  cur = __gcd(cur, a[i]);
  if(cur == 1) return 1;
  int ans = INT_MAX;
  for(int j = i + 1; j < n; j++)
    ans = min(ans, 1 + solve(j, cur));
  return ans;
}

const int N = 5009;
int dp[N][N];
int mn[N][N];
  

int main() {
  int t, i, j;
  scanf("%d", &t);
  while(t--) {
    scanf("%d", &n);
    int g = 0;
    for(i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      if(i == 0) g = a[i];
      else g = __gcd(a[i], g);
    }
    int ct_eq = 0;
    for(i = 0; i< n ;i ++) {
      a[i] /= g;
      if(a[i] == 1) ct_eq++;
    }
    if(ct_eq > 0) {
      printf("%d\n", n - ct_eq);
      continue;
    }
    for(int cur = 0; cur <= 5000; cur++)
      mn[n][cur] = 1e9;
    for(int i = n - 1; i >= 0; i--)
      for(int cur = 1; cur <= 5000; cur++) {
        int ncur = __gcd(cur, a[i]);
        if(ncur <= 1) dp[i][cur] = 1;
        else dp[i][cur] = 1 + mn[i+1][ncur];
        mn[i][cur] = min(mn[i+1][cur], dp[i][cur]);
      }
    int best = 1e9;
    for(i = 0; i < n; i++) best = min(best, dp[i][a[i]]);
    printf("%d\n", n - 1 + (best - 1));
  }
}
