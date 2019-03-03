#include <cstdio>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <set>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstring>
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


void Z(char s[], int n, int z[]) { // z[i] = |lcp(s,s[i..n])|
	for(int i = 1, m = -1; i < n; i++) {
		z[i] = (m != -1 && m + z[m] >= i)?min(m + z[m] - i, z[i - m]):0;
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m]) m = i;
	}
}



char s[N];
int z[N][N];

int memo[N];
int a, b, n;
int solve(int i) {
  if(i >= n) return 0;
  int &r = memo[i];
  if(r != -1) return r;
  r = a + solve(i + 1);
  int sz = 0;
  for(int k = 0; k < i; k++) {
    sz = max(sz, min(i - k, z[k][i]));
  }
  for(int s = 1; s <= sz; s++)
    r = min(r, b + solve(i + s));
  return r;
}

int main() {
  srand(time(NULL));
  const ll B = rand() % 100 + 150;
  int i, j;
  scanf("%d %d %d %s", &n, &a, &b, s);
  for(i = 0; i < n; i++) {
    Z(s + i, n - i, &z[i][i]);
  }
  memset(memo, -1, sizeof memo);
  printf("%d\n", solve(0));
}
