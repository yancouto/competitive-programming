#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int N, B;

int sz[30];

void go() {
  memset(sz, 0, sizeof sz);
  int f = 0;
  for (int i_ = 0; i_ < N * B; i_++) {
    int d;
    scanf("%d", &d);
    int j = f;
    if (d == 9) {
      j = f;
    } else {
      while (j + 1 < N && sz[j] == B - 1) j++;
      if (sz[j] == B - 1) j = f;  // might as well chose the first
    }
    printf("%d\n", j + 1);
    if (++sz[j] == B) f++;
  }
}

int main() {
  int t;
  scanf("%d %d %d %*d", &t, &N, &B);
  while (t--) go();
  return 0;
}