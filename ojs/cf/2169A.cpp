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

int n, a, x;

void go() {
  scanf("%d %d", &n, &a);
  int gt = 0, lt = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d", &x);
    if(x > a) gt++;
    else if(x < a) lt++;
  }
  if(gt >= lt) printf("%d\n", a + 1);
  else printf("%d\n", a - 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) go();
}