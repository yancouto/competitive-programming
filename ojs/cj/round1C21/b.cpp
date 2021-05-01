#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define yn asd

ll y;
int yn;
char ys[50];
char xs[50];

ll parse() { return strtoll(xs, NULL, 10); }

void solve(int offset, ll val) {
  sprintf(xs + offset, "%lld", val);
  while (xs[offset]) offset++;
  if (offset > yn) return;
  if (offset == yn && parse() >= y) return;
  solve(offset, val + 1);
}

ll go() {
  scanf("%lld", &y);
  if (y < 12) return 12;
  y++;
  sprintf(ys, "%lld", y);
  yn = strlen(ys);
  ll best = LLONG_MAX;
  ll val = 0;
  for (int i = 0; i < yn - 1; i++) {
    val = val * 10ll + (ys[i] - '0');
    for (ll add = -20; add <= 20; add++) {
      if (val + add <= 0 || val + add >= y) continue;
      solve(0, val + add);
      ll x = parse();
      if (x >= y) best = min(best, x);
    }
  }
  return best;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    printf("Case #%d: %lld\n", tt, go());
  }
  return 0;
}