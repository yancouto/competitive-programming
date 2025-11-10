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

int a[11234];

int main() {
  int t, n;
  scanf("%d", &t);
  while(t--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a + n);
    for(int i = 1; i < n - 1; i += 2)
      swap(a[i], a[i+1]);
    int i;
    for(i = 0; i < n; i++)
      if(i < n - 1 && a[i] > a[i+1])
        break;
    if(i == n) puts("YES");
    else puts("NO");
  }
}