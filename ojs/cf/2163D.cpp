#include <bits/stdc++.h>
using namespace std;
#define l first
#define r second
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

int n, qn;
const int N = 312345;
pii q[N];
map<pii, int> memo; // prolly not necessary

int query(int l, int r) {
  if(memo.count(pii(l, r))) return memo[pii(l, r)];
  int x;
  printf("? %d %d\n", l, r); fflush(stdout);
  scanf("%d", &x);
  memo[pii(l, r)] = x;
  return x;
}

ll go() {
  memo.clear();
  scanf("%d %d", &n, &qn);
  for(int i = 0; i < qn; i++)
    scanf("%d %d", &q[i].l, &q[i].r);
  sort(q, q + qn, [](pii a, pii b) { return pii(a.l, b.r) < pii(b.l, a.r); });
  int nqn = 0;
  for(int i = 0; i < qn; i++) {
    if(nqn > 0 && q[i].r <= q[nqn-1].r) continue;
    q[nqn++] = q[i];
  }
  qn = nqn;
  if(qn == 0) return query(q[0].l, q[0].r);
  int l = 0, r = qn - 1;
  while(l < r) {
    int m = (l + r) / 2;
    int mexr = query(q[m+1].l, n);
    int mexl = query(1, q[m].r);
    if(mexl == mexr) {
      assert(mexl == 0);
      return 0;
    }
    if(mexl > mexr) r = m;
    else l = m + 1;
  }
  return query(q[l].l, q[l].r);
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    printf("! %d\n", go());
    fflush(stdout);
  }
}