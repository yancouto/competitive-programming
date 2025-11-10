#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

const int N = 212345;
int p[N], inv[N];
char x[N];

int main() {
  int t, n;
  scanf("%d", &t);
  while(t--) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
      scanf("%d", &p[i]);
      inv[p[i]] = i;
    }
    scanf(" %s", x + 1);
    if(x[1] == '1' || x[n] == '1') {
      puts("-1");
      continue;
    }
    set<pii> acts;
    int p1 = inv[1];
    if(p1 != 1) acts.insert(pii(1, p1));
    if(p1 != n) acts.insert(pii(p1, n));
    int pn = inv[n];
    if(pn != 1) acts.insert(pii(1, pn));
    if(pn != n) acts.insert(pii(pn , n));
    acts.insert(pii(min(p1, pn), max(p1, pn)));
    if(x[p1] == '1' || x[pn] == '1') {
      puts("-1");
      continue;
    }
    printf("%d\n", int(acts.size()));
    for(auto [a, b] : acts)
      printf("%d %d\n", a, b);
  }
}