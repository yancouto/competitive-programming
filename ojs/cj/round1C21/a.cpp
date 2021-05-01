#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair

int n, k;
double go() {
  int x;
  scanf("%d %d", &n, &k);
  set<int> s;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    s.insert(x);
  }
  if (s.size() == k) return 0;
  int beg = *s.begin() - 1;
  int end = k - *s.rbegin();
  int max_wins = max(beg, end);
  multiset<int> sizes;
  for (auto it = s.begin(); it != s.end() && next(it) != s.end(); ++it) {
    int x = *it;
    int y = *next(it);
    int sz = y - x - 1;
    max_wins = max(max_wins, sz);
    if (sz > 0) {
      sizes.insert(1 + ((sz - 1) / 2));
    }
  }
  sizes.insert(beg);
  sizes.insert(end);
  int my_ans = 0;
  int i = 0;
  for (auto it = sizes.rbegin(); i < 2; i++, ++it) {
    my_ans += *it;
  }
  max_wins = max(max_wins, my_ans);
  return max_wins / double(k);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    printf("Case #%d: %.10f\n", tt, go());
  }
  return 0;
}