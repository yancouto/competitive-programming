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

int n;
const int N = 112345;
const int M = 4 * N;

int A[N];
ll bit[N];
void add_b(int i, int x) {
	debug(">>>>>>>>>>>>>>pos[%d] +=  %d\n", i, x);
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

ll get_b(int i) {
	ll sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
ll get_b(int l, int r) { return get_b(r) - get_b(l - 1); }

void build() {
	int i;
	for(i = 0; i < N; i++) bit[i] = 0;
}

int nx[N];
int pr[N];
set<int> all[N];

int val[N];
inline void rm(int i, int x) {
	debug("rm(%d, %d)\n", i, x);
	all[x].erase(i);
	if(nx[x] == i) {
		add_b(i, -val[i]);
		nx[x] = n + 1;
		if(!all[x].empty()) {
			nx[x] = *all[x].begin();
			add_b(nx[x], val[nx[x]]);
		}
	}
}

inline void add(int i, int x) {
	debug("add(%d, %d)\n", i, x);
	if(nx[x] > i) {
		if(nx[x] <= n)
			add_b(nx[x], -val[nx[x]]);
		nx[x] = i;
		add_b(i, val[i]);
	}
	all[x].insert(i);
}

vector<int> ql[N];

int m;

int t[N], B[N], a[N], b[N];
ll ans[N];

void go() {
	int i, j, k;
	int sq = ceil(sqrt(m));
	for(i = 0; i < m; i += sq) {
		debug("=======\n\nstarting at [%d]\n", i);
		build();
		for(k = 1; k <= n; k++) nx[k] = n + 1, ql[k].clear(), all[k].clear();
		vector<int> mod;
		for(j = 0; j < sq && i + j < m; j++) {
			if(t[i + j] == 1) mod.pb(i + j);
			else ql[a[i + j]].pb(i + j);
		}
		for(int l = n; l >= 1; l--) {
			debug("answering %d+\n", l);
			add(l, A[l]);
			for(int q : ql[l]) {
				debug("query %d (%d, %d)\n", q, a[q], b[q]);
				deque<int> undo;
				for(int m : mod) {
					if(m > q) break;
					if(a[m] < l) continue;
					pr[m] = A[a[m]];
					rm(a[m], pr[m]);
					add(a[m], b[m]);
					A[a[m]] = b[m];
					undo.push_front(m);
				}
				debug("ans %d = %lld\n", q, get_b(a[q], b[q]));
				ans[q] = get_b(a[q], b[q]);
				for(int m : undo) {
					if(a[m] < l) continue;
					rm(a[m], b[m]);
					add(a[m], pr[m]);
					A[a[m]] = pr[m];
				}
			}
		}
		for(j = 0; j < sq && i + j < m; j++)
			if(t[i + j] == 1)
				A[a[i + j]] = b[i + j];
	}
}

ll ans2[N];

int main() {
	int i, j;
	rd(n); rd(m);
	for(i = 1; i <= n; i++) rd(A[i]), B[i] = A[i];
	for(i = 0; i < m; i++) rd(t[i]), rd(a[i]), rd(b[i]);
	for(i = 1; i <= n; i++) val[i] = -i;
	go();
	for(i = 0; i < m; i++) ans2[i] = ans[i];
	for(i = 1; i <= n; i++) A[i] = B[i], val[i] = n + 1 - i;
	reverse(A + 1, A + 1 + n);
	for(i = 0; i < m; i++) {
		a[i] = n + 1 - a[i];
		if(t[i] == 2) b[i] = n + 1 - b[i], swap(a[i], b[i]);
		debug("%d %d %d\n", t[i], a[i], b[i]);
	}
	go();
	// reverse and go()
	for(i = 0; i < m; i++)
		if(t[i] == 2)
			debug("2: %lld + %lld\n", ans[i], ans2[i]);
	for(i = 0; i < m; i++)
		if(t[i] == 2)
			printf("%lld\n", ans[i] + ans2[i]);

}
