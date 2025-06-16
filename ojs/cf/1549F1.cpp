#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define LLD "%I64d"
#define debug(args...) \
  {                    \
  }
#else
#define LLD "%lld"
#define debug(args...) fprintf(stderr, args)
#endif

int ct[5][5];

int main() {
  int n, i, x, y;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d %d", &x, &y);
    ct[x % 4][y % 4]++;
  }
  ll ans = 0;
  int x1, x2, x3, y1, y2, y3;
  for (x1 = 0; x1 < 4; x1++)
    for (y1 = 0; y1 < 4; y1++)
      for (x2 = 0; x2 < 4; x2++)
        for (y2 = 0; y2 < 4; y2++)
          for (x3 = 0; x3 < 4; x3++)
            for (y3 = 0; y3 < 4; y3++) {
              if (pii(x1, y1) > pii(x2, y2) || pii(x2, y2) > pii(x3, y3))
                continue;
              ll ct1 = ct[x1][y1];
              ll ct2 = ct[x2][y2];
              ll ct3 = ct[x3][y3];
              if (!ct1 || !ct2 || !ct3) continue;
              int g1 = max((x2 - x1 + 16) % 4, (y2 - y1 + 16) % 4);
              int g2 = max((x3 - x1 + 16) % 4, (y3 - y1 + 16) % 4);
              int g3 = max((x3 - x2 + 16) % 4, (y3 - y2 + 16) % 4);
              if ((g1 + g2 + g3) % 4) continue;
              ll dv = 1;
              if (pii(x1, y1) == pii(x2, y2)) {
                ct2--;
                dv = 2;
                if (pii(x2, y2) == pii(x3, y3)) ct3 -= 2, dv = 6;
              } else if (pii(x2, y2) == pii(x3, y3) ||
                         pii(x1, y1) == pii(x3, y3))
                ct3--, dv = 2;
              ans += (ct1 * ct2 * ct3) / dv;
              // printf("[(%d,%d)(%d,%d)(%d,%d)] %lld * %lld * %lld / %lld\n",
              // x1,
              //        y1, x2, y2, x3, y3, ct1, ct2, ct3, dv);
            }
  printf("%lld\n", ans);
}