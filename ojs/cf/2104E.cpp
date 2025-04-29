#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for (int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1e6 + 9;
char s[N], t[N];
int nx[N][26], ans[N];

int main() {
  int n, k, i, j;
  scanf("%d %d %s", &n, &k, s);
  for (i = 0; i < k; i++) nx[n][i] = nx[n + 1][i] = n;
  for (i = n - 1; i >= 0; i--) {
    for (j = 0; j < k; j++) nx[i][j] = nx[i + 1][j];
    nx[i][s[i] - 'a'] = i;
  }
  ans[n] = ans[n + 1] = 1;
  for (i = n - 1; i >= 0; i--) {
    ans[i] = INT_MAX;
    for (j = 0; j < k; j++)
      if (nx[i][j] == n)
        ans[i] = 1;
      else
        ans[i] = min(ans[i], 1 + ans[nx[i][j] + 1]);
  }
  for_tests(q, qi) {
    scanf("%s", t);
    j = 0;
    for (i = 0; t[i]; i++)
      if (nx[j][t[i] - 'a'] == n) {
        puts("0");
        break;
      } else
        j = nx[j][t[i] - 'a'] + 1;
    if (t[i]) continue;
    printf("%d\n", ans[j]);
  }
}