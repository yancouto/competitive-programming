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

const int N = 1123456, M = 112345;

int a[N], b[N], lst[M], o[N], op[N], ans[N], cmp;
int S[M], sz[M], st[M], sn;
inline int find(int i) {
	while(S[i] != i) i = S[i];
	return i;
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	cmp--;
	if(sz[a] < sz[b]) swap(a, b);
	st[sn++] = b;
	sz[a] += sz[b];
	S[b] = a;
}

inline void rollback() {
	cmp++;
	int a = st[--sn];
	sz[S[a]] -= sz[a];
	S[a] = a;
}

void rec(int l, int r) {
	if(l == r) return (void) (ans[l] = cmp);
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


int e[10];
int main() {
#ifdef ONLINE_JUDGE
	freopen("disconnected.in", "r", stdin);
	freopen("disconnected.out", "w", stdout);
#endif
	int i, j, n, m, k, c, on = 0;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	cmp = n;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a[i], &b[i]); a[i]--; b[i]--;
		lst[i] = i;
		op[on++] = '+';
	}
	scanf("%d", &k);
	for(i = 0; i < k; i++) {
		scanf("%d", &c);
		for(j = 0; j < c; j++) {
			scanf("%d", &e[j]); e[j]--;
			o[on] = lst[e[j]]; a[on] = a[e[j]]; b[on] = b[e[j]];
			o[lst[e[j]]] = on;
			op[on++] = '-';
		}
		on++;
		for(j = 0; j < c; j++) {
			lst[e[j]] = on;
			a[on] = a[e[j]]; b[on] = b[e[j]];
			op[on++] = '+';
		}
	}
	for(i = 0; i < m; i++) {
		o[on] = lst[i];
		o[lst[i]] = on;
		a[on] = a[i]; b[on] = b[i];
		op[on++] = '-';
	}
	rec(0, on - 1);
	for(i = 0; i < on; i++)
		if(!op[i])
			puts(ans[i] == 1? "Connected" : "Disconnected");
}
