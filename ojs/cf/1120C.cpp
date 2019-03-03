#include <cstdio>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <set>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
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

const int N = 212345;
ll c[N];
vector<int> adj[N];

void go(int u, int p) {
  if(u) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
  for(int v : adj[u])
    go(v, u);
}

ll memo[N][2];
ll solve(int u, bool root) {
  ll &r = memo[u][root];
  if(r != -1) return r;
  if(adj[u].empty())
    return root? c[u] : 1e16;
  ll tot = 0;
  for(int v : adj[u])
    tot += min(solve(v, false), solve(v, true));
  if(!root) return r = tot;
  r = 1e16;
  for(int v : adj[u]) {
    ll ntot = tot - min(solve(v, false), solve(v, true));
    r = min(r, ntot + solve(v, true) - c[v] + c[u]);
  }
  return r;
}

int mrk[N], mrkn;
int seen[N][2][2];
void build(int u, bool root, bool really_root) {
  if(seen[u][root][really_root]) return;
  seen[u][root][really_root] = 1;
  if(really_root) mrk[u] = 1, mrkn++;
  if(adj[u].empty()) return;
  ll tot = 0;
  for(int v : adj[u])
    tot += min(solve(v, false), solve(v, true));
  vector<int> pos;
  ll r = solve(u, root);
  if(root)
    for(int v : adj[u]) {
      ll ntot = tot - min(solve(v, false), solve(v, true));
      debug("%d,%d,%d> %lld vs %lld\n", u, root, really_root,r, ntot + solve(v, true) - c[v] + c[u]);
      if(r == ntot + solve(v, true) - c[v] + c[u]) {
        pos.pb(v);
        debug("pos.pb(%d)\n", v);
      }
    }
    debug(">s %d\n", (int)pos.size());
  for(int v : pos)
    build(v, true, false);
  if(!root || pos.size() > 1) {
    for(int v : adj[u]) {
      ll ans = min(solve(v, true), solve(v, false));
      if(ans == solve(v, true)) build(v, true, true);
      if(ans == solve(v, false)) build(v, false, false);
    }
  } else {
    debug("s %d\n", (int)pos.size());
    assert(pos.size() == 1);
    int x = pos[0];
    for(int v : adj[u]) {
      if(v == x) continue;
      ll ans = min(solve(v, true), solve(v, false));
      if(ans == solve(v, true)) build(v, true, true);
      if(ans == solve(v, false)) build(v, false, false);
    }
  }
}

int main() {
  int i, n;
  rd(n);
  for(i = 0; i < n; i++) rd(c[i]);
  for(i = 0; i < (n - 1); i++) {
    int a, b;
    rd(a); rd(b); a--; b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  go(0, 0);
  memset(memo, -1, sizeof memo);
  ll ans = min(solve(0, false), solve(0, true));
  if(ans == solve(0, false)) build(0, false, false);
  if(ans == solve(0, true)) build(0, true, true);
  printf("%lld %d\n", ans, mrkn);
  for(i = 0; i < n; i++)
    if(mrk[i])
      printf("%d ", i + 1);
  putchar('\n');
}
