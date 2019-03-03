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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 512345;
int a[N], b[N];

int main() {
	int i, j;
  int m, k, n, s;
	rd(m); rd(k); rd(n); rd(s);
  for(i = 0; i < m; i++) rd(a[i]);
  map<int, int> mp;
  for(i = 0; i < s; i++) {
    rd(b[i]);
    mp[b[i]]++;
  }
  set<int> all;
  map<int, deque<int>> ocs;
  for(i = m - 1; i >= 0; i--) {
    if(mp.count(a[i])) {
      all.insert(i);
      ocs[a[i]].push_front(i);
      if(ocs[a[i]].size() > mp[a[i]]) {
        all.erase(all.find(ocs[a[i]].back()));
        ocs[a[i]].pop_back();
      }
    }
    assert(all.size() <= s);
    if(all.size() == s && m - i >= k) {
      int r = max(*all.rbegin(), i + k - 1);
      int lf = min(i / k, n - 1);
      int rg = min((m - r - 1) / k, (n - 1) - lf);
      //printf("i %d r %d lf %d rg %d\n", i, r, lf, rg);
      assert(lf + rg + 1 <= n);
      if(lf + 1 + rg >= n) {
        printf("%d\n", (i - lf * k) + (r - i + 1 - k) + (m - r - 1 - rg * k));
        for(j = 0; j < (i - lf * k); j++) printf("%d ", j + 1);
        int ct = s;
        for(j = i; j <= r; j++) {
          if(!all.count(j)) {
            if(ct == k)
              printf("%d ", j + 1);
            else
              ct++;
          }
        }
        for(j = 0; j < (m - r - 1 - rg * k); j++) printf("%d ", m - j);
        putchar('\n');
        return 0;
      }
    }
  }
  puts("-1");
}
