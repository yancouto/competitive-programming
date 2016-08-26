#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 612345;

int S[N], sz[N], ct;
int st[N], sn;

inline int find(int i) {
	while(S[i] != i) i = S[i];
	return i;
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	ct--;
	if(sz[a] < sz[b]) swap(a, b);
	st[sn++] = b;
	sz[a] += sz[b];
	S[b] = a;
}

inline void rollback() {
	ct++;
	int a = st[--sn];
	sz[S[a]] -= sz[a];
	S[a] = a;
}

int a[N], b[N], ans[N], o[N];
char op[N];

void rec(int l, int r) {
	if(l == r) return (void) (ans[l] = ct);
	int m = (l + r) / 2;
	int C = sn;
	for(int i = m + 1; i <= r; i++)
		if(op[i] == '-' && o[i] < l)
			join(a[i], b[i]);
	rec(l, m);
	while(sn > C) rollback();
	for(int i = l; i <= m; i++)
		if(op[i] == '+' && o[i] > r)
			join(a[i], b[i]);
	rec(m + 1, r);
	while(sn > C) rollback();
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("connect.in", "r", stdin);
	freopen("connect.out", "w", stdout);
#endif
	int i, j, n, k;
	scanf("%d %d", &n, &k);
	if(k == 0) return 0;
	map<pii, int> s;
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < k; i++) {
		scanf(" %c", &op[i]);
		if(op[i] != '?') scanf("%d %d", &a[i], &b[i]); a[i]--; b[i]--;
		if(a[i] > b[i]) swap(a[i], b[i]);
		pii p(a[i], b[i]);
		if(op[i] == '+') s[p] = i;
		else if(op[i] == '-') o[i] = s[p], o[s[p]] = i, s.erase(p);
	}
	while(!s.empty()) {
		pii p = s.begin()->fst;
		o[i] = s[p];
		o[s[p]] = i;
		op[i] = '-'; a[i] = p.fst; b[i] = p.snd;
		s.erase(p); i++;
	}
	ct = n;
	rec(0, i - 1);
	for(j = 0; j < i; j++)
		if(op[j] == '?')
			printf("%d\n", ans[j]);
}
