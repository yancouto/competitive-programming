#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) \
  int t;                 \
  scanf("%d", &t);       \
  for (int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
  int a, b, c;
  for_tests(t, tt) {
    scanf("%d %d %d", &a, &b, &c);
    if ((a + b + c) % 3)
      puts("NO");
    else if (c - (b - a) < b)
      puts("NO");
    else
      puts("YES");
  }
}