#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int MAX = 120;
int tr[MAX][10];
int pr[MAX], ba[MAX];
char s[100], op[12][100];

ll memo[12][MAX][2][2];
ll solve(int i, int v, bool pre, bool all0) {
	if(ba[v]) return 0;
	if(!s[i]) return 1;
	ll &r = memo[i][v][pre][all0];
	if(r != -1) return r;
	r = 0;
	for(int d = 0; d < 10; d++) {
		if(pre && d > s[i] - '0') break;
		int p = v;
		while(p && tr[p][d] == -1)
			p = pr[p];
		if(tr[p][d] != -1) p = tr[p][d];
		if(all0 && !d) p = 0;
		r += solve(i + 1, p, pre && d == s[i] - '0', all0 && !d);
	}
	return r;
}
int k;

int main() {
	int i, j, tn, n; ll x;
	for_tests(t, tt) {
		scanf("%d", &k);
		memset(tr, -1, sizeof tr);
		memset(ba, 0, sizeof ba);
		tn = 0;
		for(i = 0; i < k; i++) {
			scanf("%s", op[i]);
			int v = 0;
			for(j = 0; op[i][j]; j++) {
				if( tr[v][op[i][j] - '0'] == -1)
					tr[v][op[i][j] - '0'] = ++tn;
				v = tr[v][op[i][j] - '0'];
			}
			ba[v] = 1;
		}
		queue<int> q;
		for(i = 0; i < 10; i++)
			if(tr[0][i] != -1)
				q.push(tr[0][i]), pr[tr[0][i]] = 0;
		while(!q.empty()) {
			int v = q.front(); q.pop();
			for(i = 0; i < 10; i++) {
				if(tr[v][i] == -1) continue;
				int &p = pr[tr[v][i]];
				p = pr[v];
				while(p && tr[p][i] == -1)
					p = pr[p];
				if(tr[p][i] != -1)
					p = tr[p][i];
				if(ba[p]) ba[tr[v][i]] = 1;
				q.push(tr[v][i]);
			}
		}
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%lld", &x);
			ll l = 0, r = 5000000000ll;
			while(l < r) {
				ll m = (l + r) / 2;
				memset(memo, -1, sizeof memo);
				sprintf(s, "%lld", m);
				if(solve(0, 0, true, true) - 1 >= x) r = m;
				else l = m + 1;
			}
			printf("%lld", l);
			if(i < n - 1) putchar(' ');
		}
		putchar('\n');
	}
}
