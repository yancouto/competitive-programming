#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

vector<int> ans;

typedef char val; // type of flow
typedef short num; // type of cost
const int N = 4123 * 2, M = 4003 * 4003 + 4003; const num eps = 0;
struct mcmf {
	int es[N], to[M], nx[M], en = 2, pai[N], seen[N], tempo, qu[N];
	val fl[M], cp[M], flow; num cs[M], d[N], tot;
	val spfa(int s, int t) {
		tempo++; int a = 0, b = 0;
		for(int i = 0; i < N; i++) d[i] = numeric_limits<num>::max();
		d[s] = 0; qu[b++] = s; seen[s] = tempo;
		while(a != b) {
			int u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
			for(int e = es[u]; e; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
		}
		if(d[t] == numeric_limits<num>::max()) return false;
		val mx = numeric_limits<val>::max();
		for(int u = t; u != s; u = to[pai[u]])
			mx = min<int>(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
		tot += d[t] * val(mx);
		for(int u = t; u != s; u = to[pai[u]])
			fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
		return mx;
	}
	// public $
	num min_cost(int s, int t) {
		tot = 0; flow = 0;
		while(val a = spfa(s, t)) flow += a, printf("added %d\n", a);
		return tot;
	}
	void add_edge(int u, int v, val c, num s) {
		fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
		fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
	}

	void go(int u) {
		for(int e = es[u]; e; e = nx[e]) if(fl[e] > 0) {
			fl[e]--;
			if(cs[e] == -1) ans.pb(to[e] / 2);
			go(to[e]);
			return;
		}
	}
	void reset_flow() { memset(fl, 0, sizeof(val) * en); }
	void init(int n) { en = 2; memset(es, 0, sizeof(int) * n); } // XXX must be called
};

const string L = "ACM";
int rev[256];

string s[N];
vector<int> nx[3][N];

mcmf f;

char s_[112345];
void rd(string &s) {
	scanf("%s", s_);
	s = s_;
}

int main() {
	int i = 0, j, k;
	for(char c : L) rev[c] = i++;
	ios::sync_with_stdio(0);
	int n;
	scanf("%d", &n);
	rd(s[n]);
	for(i = 0; i < n; i++)
		rd(s[i]);
	sort(s, s + n, [](const string &a, const string &b) { return a.size() < b.size(); });
	for(i = 0; i < n - 2; i++)
		if(s[i].size() == s[i + 1].size() && s[i].size() == s[i + 2].size()) {
			printf("impossible\n");
			return 0;
		}
	printf("sort\n");
	for(i = 0; i <= n; i++) {
		for(j = 0; j < 3; j++) {
			int m = s[i].size();
			nx[j][i].resize(m);
			nx[j][i][m - 1] = L[j] == s[i][m - 1]? m - 1 : m;
			for(int k = m - 2; k >= 0; k--)
				nx[j][i][k] = (L[j] == s[i][k]? k : nx[j][i][k + 1]);
		}
	}
	printf("nx\n");
	int s = 2 * n + 2, t = 2 * n + 3;
	int aux = 2 * n + 4;
	f.add_edge(s, aux, 2, 0);
	for(i = 0; i <= n; i++) {
		for(j = i + 1; j <= n; j++) {
			int p = 0;
			bool bad = false;
			for(k = 0; k < ::s[i].size() && p < ::s[j].size(); k++) {
				p = nx[rev[::s[i][k]]][j][p] + 1;
				if(p == ::s[j].size() + 1 || (k + 1 < ::s[i].size() && p >= ::s[j].size())) bad = true;
			}
			if(!bad) f.add_edge(2 * i + 1, 2 * j, 1, 0);
		}
		if(i == n) f.add_edge(2 * i, t, 2, 0);
		else f.add_edge(2 * i, 2 * i + 1, 1, -1);
		f.add_edge(aux, 2 * i, 1, 0);
	}
	printf("es\n");
	if(f.min_cost(s, t) == -n) {
		f.go(s);
		vector<int> A = ans;
		ans.clear();
		f.go(s);
		vector<int> B = ans;
		printf("%d %d\n", int(A.size()), int(B.size()));
		for(int i : A)
			printf("%s\n", ::s[i].c_str());
		for(int i : B)
			printf("%s\n", ::s[i].c_str());
	} else printf("impossible\n");
}
