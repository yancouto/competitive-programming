#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define yn asd

char a[123], b[123];

vector<int> get(char s[]) {
  if (s[0] == '0') return {0, 1};
  vector<int> v;
  char prev = '1';
  int ct = 1, i;
  for (i = 1; s[i]; i++) {
    if (s[i] != prev) {
      prev = s[i];
      v.pb(ct);
      ct = 0;
    }
    ct++;
  }
  v.pb(ct);
  if (prev == '1') v.pb(0);
  // printf("\n%s: ", s);
  // for (int x : v) printf("%d, ", x);
  // putchar('\n');
  return v;
}

void go() {
  scanf("%s %s", a, b);
  if (strcmp(a, b) == 0) {
    puts("0");
    return;
  }
  vector<int> va = get(a);
  if (b[0] == '0') {
    int ct = va.size();
    if (*va.rbegin() == 0) ct--;
    printf("%d\n", ct);
    return;
  }
  vector<int> vb = get(b);
  if (vb.size() > va.size()) {
    puts("IMPOSSIBLE");
    return;
  }
  if (va == vb) {
    printf("0\n");
    return;
  }
  int bn = vb.size();
  int an = va.size();
  int ans = an + accumulate(vb.begin(), vb.end(), 0) - (va[an - 1] == 0);
  for (int i = 0; i < an; i++) {
    if (i + bn < an) continue;
    if (i + bn == an - 1 && va[an - 1] == 0) continue;
    int c = i;
    bool bad = false;
    int j;
    for (j = 0; j < bn && i + j < an; j++) {
      if (i + j == an - 1 || (i + j + 1 == an - 1 && va[an - 1] == 0 && i)) {
        if (vb[j] < va[i + j]) bad = true;
        c += vb[j] - va[i + j];
      } else {
        if (vb[j] != va[i + j]) bad = true;
      }
    }
    for (; j < bn; j++) c += vb[j];
    // if (!bad) printf("i = %d c = %d\n", i, c);
    if (!bad) ans = min(ans, c);
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    printf("Case #%d: ", tt);
    go();
  }
  return 0;
}