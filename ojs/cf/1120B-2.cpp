#include <cstdio>
#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 5009;
char s[N];
int tn = 1;
int tr[N * N / 2][26];
int r[N * N / 2];

map<int, int> mp[N];

int main() {
  int i, j, n, a, b;
  scanf("%d %d %d %s", &n, &a, &b, s);
  for(i = 0; i < n; i++) {
    int v = 0;
    for(j = i; j < n; j++) {
      if(!tr[v][s[j] - 'a']) {
        r[tn] = j;
        tr[v][s[j] - 'a'] = tn++;
      }
      v = tr[v][s[j] - 'a'];
    }
  }
  int cost = 0;
  for(i = 0; i < n;) {
    int v = 0;
    for(j = i; j < n && r[tr[v][s[j] - 'a']] < i; j++)
      v = tr[v][s[j] - 'a'];
    if(j == i || (j - i) * a < b) {
      i++;
      cost += a;
    } else {
      i = j;
      cost += b;
    }
  }
  printf("%d\n", cost);
}
