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

const int NS = 10;
const int N = 1123456 * 2;

int cn, cd, ns, en = 1, lst;
int si = -1;
char S[NS][112345];

const int E = 27;
struct node {
	int l, r, si;
	int p, suf;
	unordered_map<char, int> adj;
	inline int len() { return r - l + 1; }
	inline char operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en].l = L; t[en].r = R;
	t[en].si = S; t[en].p = P;
	return en++;
}

int mrk[N];
void add_string(int m, int n) {
	char* s = S[si];
	cn = cd = 0;
	int i = 0;
	for(int j = 0; j < n; j++)
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn](s[j]))
				cn = t[cn](s[j]), cd = 0;
			if(cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if(j < n - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) {
						mrk[cn] |= m;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				mrk[en] |= m;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				mrk[en] |= m;
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

int full;
int mx;
int dfs(int u, int h) {
	bool any = false;
	for(auto e : t[u].adj)
		mrk[u] |= dfs(e.snd, h + t[e.snd].len()), any = true;
	//for(int i = 0; i < E; i++)
	//	if(t[u].adj[i])
	//		mrk[u] |= dfs(t[u].adj[i], h + t[t[u].adj[i]].len()), any = true;
	if(mrk[u] == full) mx = max(mx, h - !any);
	return mrk[u];
}

char s[112345];
int main() {
	t[0].r = -1;
	int i = 0, j;
	while(scanf("%s", S[i]) != EOF) {
		si++;
		for(j = 0; S[i][j]; j++);
		S[i][j] = '}';
		add_string(1 << i, j + 1); i++;
	}
	full = (1 << i) - 1;
	dfs(0, 0);
	printf("%d\n", mx);
}
