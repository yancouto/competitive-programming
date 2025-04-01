#include <bits/stdc++.h>
using namespace std;

const int N = 112345;

int x[N], y[N], p[N];

int main() {
  int n, k, i;
  scanf("%d %d", &n, &k);
  for (i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]), p[i] = i;
  bool all_eq_x = true;
  for (i = 1; i < n; i++) all_eq_x = all_eq_x && (x[i] == x[i - 1]);
  if (all_eq_x)
    for (i = 0; i < n; i++) swap(x[i], y[i]);
  if (k == 1) {
    printf("0\n");
    return 0;
  }
  sort(p, p + n, [](int a, int b) { return x[a] < x[b]; });
  double dist2 = 1e20;
  for (i = 0; i + k - 1 < n; i++) {
    double xa = x[p[i]], xb = x[p[i + k - 1]], ya = y[p[i]],
           yb = y[p[i + k - 1]];
    dist2 = min(dist2, (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
  }
  double ans = atan2(0, -1) * dist2 / 4;

  cout << setprecision(20) << ans << endl;
}