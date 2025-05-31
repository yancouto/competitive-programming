
// incomplete
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

enum T {
  eq,
  ge,
  any,
};

const int N = 312345;

int b[N], ty[N];

// c_a = min(c_a, a_b)
bool same(int a, int b) {

  
}

bool apply(int x, int y, int z) {
  if(x == y && y == z) return true;
  if(x == z) return same(z, y);
  if(y == z) return same(z, x);
}

int x[N], y[N], z[N];

int main() {
  int i, n, q, t;
  scanf("%d", &t);
  while(t--) {
    scanf("%d %d", &n, &q);
    for(i = 0; i < n; i++) {
      scanf("%d", &b[i]);
      ty[i] = eq;
    }
    for(i = 0; i < q; i++)
      scanf("%d %d %d", &x[i], &y[i], &z[i]);
    for(i = q - 1; i >= 0; i--)
      if(!apply(x[i]-1, y[i]-1, z[i]-1))
        break;
    if(i >= 0) puts("-1");
    else {
      for(i = 0; i < n; i++) printf("%d ", b[i]);
      putchar('\n');
    }
  }
}