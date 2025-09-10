#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long

char num[100], numn;
int best[120];
int curd[120];
int mp[120], p[120];
int n, g;

int memo1[21234567];
int can(int x) {
  if(x < 0) return false;
  if(x == 0) return true;
  int &r = memo1[x];
  if(r != -1) return r;
  r = 0;
  for(int i = 0; !r && i < n; i++)
    if(can(x - p[i]))
      r = 1;
  return r;
}

int maiord(int i) {
  if(i == numn - 7) return 2;
  else return 0;
}

int memo[21][3][3][3][1099][10];
int dp(int i, bool g0, bool menor, bool maior, int mod, int wd) {
  if(!num[i]) return (mod == 0? 0 : -10000);
  int &r = memo[i][g0][menor][maior][mod][wd];
  if(r != -1) return r;
  r = 0;
  int cd = num[i] - '0';
  for(int d = 0; d <= 9; d++) {
    if(!menor && d > cd) continue;
    if(!maior && d < maiord(i)) continue;
    int add = (mp[d] == wd);
    if(!g0 && d == 0) add = 0;
    r = max(r, add + dp(i + 1, g0 || (d > 0), menor || (d < cd), maior || (d > maiord(i)), (mod * 10 + d) % g, wd));
  }
  return r;
}

main() {
  for(int i = 0; i < 9; i++) mp[i] = i;
  mp[9] = 6;
  memset(memo1, -1, sizeof memo1);
  memset(memo, -1, sizeof memo);
  scanf(" %s %lld", num, &n);
  for(int i = 0; num[i]; i++) {
    best[mp[num[i] - '0']]++;
  }
  long long mx = atoll(num);
  numn = strlen(num);
  for(int i = 0; i < n; i++) {scanf("%lld", &p[i]); g = __gcd(g, p[i]);}
  best[0] = max(best[0], 1ll);
  for(int i = 1; i <= 5000009 && i <= mx; i++)
    if(can(i)) {
      for(int x = i; x; x /= 10) curd[mp[x % 10]]++;
      for(int d = 0; d < 9; d++) {
        best[d] = max(best[d], curd[d]);
        curd[d] = 0;
      }
    }
  if(mx >= 2000000) {
    for(int d = 0; d < 9; d++)
      best[d] = max(best[d], dp(0, false, false, false, 0, d));
  }
  for(int d = 0; d < 9; d++)
    if(best[d] > 0)
      printf("%lld %lld\n", d, best[d]);
}