#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    printf("%d\n", 1 + (n - 1) * 2);
    printf("1 1 %d\n", n);
    for (int i = 1; i < n; i++) {
      printf("%d 1 %d\n", i + 1, i);
      printf("%d %d %d\n", i + 1, i + 1, n);
    }
  }
}