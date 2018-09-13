#include <bits/stdc++.h>
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

struct tr {
	char a, b;
	int p;
};

vector<tr> adj[30];

int memo[26][101][101];
char s[101];
int solve(int a, int l, int r) {
	if(l == r) return a == s[l] - 'a'? 0 : 1e9;
	int &ret = memo[a][l][r];
	if(ret != -1) return ret;
	ret = 1e9;
	for(tr &t : adj[a])
		for(int i = l; i < r; i++)
			ret = min(ret, t.p + solve(t.a, l, i) + solve(t.b, i + 1, r));
	return ret;
}


int main() {
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		printf("CASE #%d\n", tt);
		int r, l, i;
		for(i = 0; i < 30; i++) adj[i].clear();
		scanf("%d %d", &r, &l);
		for(i = 0; i < r; i++) {
			char a, b, c; int p;
			scanf(" %c %c %c %d", &a, &b, &c, &p);
			adj[a - 'A'].pb(tr{b - 'A', c - 'A', p});
		}
		for(i = 0; i < l; i++) {
			memset(memo, -1, sizeof memo);
			int ns;
			scanf("%d %s", &ns, s);
			int ans = solve(0, 0, ns - 1);
			if(ans < 1e8) printf("POSSIBLE WITH %d DIAMONDS\n", ans + ns);
			else puts("IMPOSSIBLE");
		}
	}
}
