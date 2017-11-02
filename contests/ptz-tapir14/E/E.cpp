#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define fst first
#define snd second

const int NS = 1;
const int N = 212345 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l+i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L,R,S,P);
	return en++;
}

void add_string(string s) {
	s += '$';
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int i = 0; const int n = s.size();
	for (int j = 0; j < n; j++)
		for (; i <= j; i++) {
			if (cd == t[cn].len() && t[cn](s[j]))
				cn = t[cn](s[j]), cd = 0;
			if (cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if (j < s.size() - 1) break;
				else {
					if (i) t[lst].suf = cn;
					for (; i <= j; i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if (cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n-1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if (ns) t[ns].suf = mid;
				if (i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j, n-1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn ? j - cd : i + 1;
				cn = t[cn].suf;
				while (g < j && g + t[t[cn](S[si][g])].len() <= j)
					cn = t[cn](S[si][g]), g += t[cn].len();
				if (g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]), cd = j - g;
			}
		}
}

char s[N];
int h[N];
int n;

ll tot = 0;

deque<pii> dq[N];
ll len[N];

void deb(int u) {
	return;
	printf("[%d] len %d ", u, len[u]);
	for(pii p : dq[u])
		printf("(%d, %d) ", p.fst, p.snd);
	putchar('\n');
}

void go(int u, int hh) {
	h[u] = hh - (t[u].adj.empty());
	//printf("[%d] height %d(%d)\n", u, h[u], hh);
	ll l = t[u].len() - t[u].adj.empty();
	tot += (ll(l) * ll(l - 1)) / 2ll;
	//printf("tot += %lld\n", (ll(l) * ll(l - 1)) / 2ll);
	if(t[u].adj.empty()) {
		dq[u].pb(pii(hh - t[u].len() + 1, h[u]));
		len[u] = l;
		deb(u);
		//printf("%d fin\n\n", u);
		return;
	}
	vector<int> A;
	for(pii e : t[u].adj) {
		//printf("%d -- (%c) --> %d\n", u, e.fst, e.snd);
		go(e.snd, hh + t[e.snd].len());
		A.pb(e.snd);
	}
	sort(A.begin(), A.end(), [](int a, int b) { return dq[a].back().snd > dq[b].back().snd; });
	assert(A.size() > 1);
	while(len[A[0]] && dq[A[0]].front().fst <= dq[A[1]].back().snd) {
		pii x = dq[A[0]].front(); dq[A[0]].pop_front();
		len[A[0]] -= x.snd - x.fst + 1;
		if(dq[A[1]].back().snd < x.snd) {
			dq[A[0]].push_front(pii(dq[A[1]].back().snd + 1, x.snd));
			len[A[0]] += dq[A[0]].front().snd - dq[A[0]].front().fst + 1;
		}
	}
	tot += l * len[A[0]];
	dq[A[0]].swap(dq[u]);
	swap(len[A[0]], len[u]);
	dq[u].push_front(pii(hh - t[u].len() + 1, h[u]));
	len[u] += l;
	deb(u);
	//printf("fin %d\n\n", u);
}

ll brut();

int main (int argn, char **args) {
#ifdef ONLINE_JUDGE
	freopen("estimations.in", "r", stdin);
	freopen("estimations.out", "w", stdout);
#endif
	//scanf("%d", &n);
	//n = 6;
	//srand(atoi(args[1]));
	//for(int i = 0; i < n; i++) s[i] = (rand() % 26) + 'a';
	//puts(s);
	scanf("%d %s", &n, s);
	add_string(s);
	go(0, 0);
	printf("%lld\n", tot);
}
