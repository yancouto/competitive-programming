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

char s[112345];

int main() {
  int n, i;
  for_tests(t, tt) {
    scanf("%d %s", &n, s);
    if (s[0] == 'A' && s[n - 1] == 'A')
      puts("Alice");
    else if (s[n - 1] == 'A' && s[n - 2] == 'A')
      puts("Alice");
    else if (all_of(s, s + n - 1, [](char x) { return x == 'A'; }))
      puts("Alice");
    else
      puts("Bob");
  }
}