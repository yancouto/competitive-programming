#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int NS = 1;
const int N = 112345 * 2;

int cn, cd, ns, en = 1, lst;
vector<int> S[NS]; int si = -1;
/* sufn[si][i] no do sufixo S[si][i...] */
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	map<int, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(int c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L, R, S, P);
	return en++;
}

void add_string(vector<int> s) {
	//s.push_back(112345);
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int i = 0; const int n = s.size();
	for(int j = 0; j < n; j++)
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn].adj.count(s[j]))
				cn = t[cn](s[j]), cd = 0;
			if(cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if(j < s.size() - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j, n - 1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn? j - cd : i + 1;
				cn = t[cn].suf;
				while(g < j && g + t[t[cn](S[si][g])].len() <= j)
					cn = t[cn](S[si][g]), g += t[cn].len();
				if(g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]), cd = j - g;
			}
		}
}

void go(int, int, int, int);

int ans[112345];

void deb(int u) {
	return;
	printf("%d: [%d, %d]\n", u, t[u].l, t[u].r);
}

int m;

void go_edge(int u, int l, int r, int k) {
	//printf("go_edge(%d, %d, %d, %d)\n", u, l, r, k);
	deb(u);
	if(l > r) return;
	if(t[u].len() >= k) {
		for(int i = l; i <= r; i++) {
			//printf("ans[%d] = (t[%d][%d] = %d - %d + %d) %% %d\n", (m - i) % m, u, k - 1, t[u][k - 1], i, m, m);
			ans[(m - i) % m] = (t[u][k - 1] - i + m) % m;
		}
		return;
	}
	go(u, l, r, k - t[u].len());
}

void go(int u, int l, int r, int k) {
	//printf("go(%d, %d, %d, %d)\n", u, l, r, k);
	deb(u);
	if(l > r) return;
	//for(auto e : t[u].adj) printf("%d-(%d)>%d [%d,%d]\n", u, e.first, e.second, t[e.second].l, t[e.second].r);
	int lst = t[u].adj.rbegin()->first;
	for(auto e : t[u].adj) {
		int from = lst + 1, to = e.first;
		//printf("%d->%d: from %d to %d\n", u, e.second, from, to);
		if(from <= to) {
			go_edge(e.second, max(l, from), min(r, to), k);
		} else {
			go_edge(e.second, max(l, from), r, k);
			go_edge(e.second, l, min(r, to), k);
		}
		lst = e.first;
	}
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("cyclic.in", "r", stdin);
	freopen("cyclic.out", "w", stdout);
#endif

	int n, k, i;
	scanf("%d %d %d", &n, &m, &k);
	vector<int> a(2 * n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = n; i < 2 * n; i++)
		a[i] = a[i - n];
	add_string(a);
	go(0, 0, m - 1, k);
	for(i = 0; i < m; i++) printf("%d\n", ans[i]);
}

