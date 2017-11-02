#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;
typedef ll num;

num X[N], S[N];
int Y[N], sz[N], L[N], R[N], lz[N];

void calc (int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	S[u] = S[L[u]] + S[R[u]] + X[u] * X[u];
}

void unlaze (int u) {
	if (!u || !lz[u]) return;
	if (L[u]) lz[L[u]] = !lz[L[u]];
	if (R[u]) lz[R[u]] = !lz[R[u]];
	lz[u] = 0;
	swap(L[u],R[u]);
}

void split_sz (int u, int s, int &l, int &r) {
	unlaze(u);
	if (!u) return (void) (l = r = 0);
	if (sz[L[u]] < s) split_sz(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split_sz(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

int merge (int l, int r) {
	unlaze(l); unlaze(r);
	if (!l || !r) return l + r;
	int u;
	if (Y[l] > Y[r]) R[l] = merge(R[l], r), u = l;
	else L[r] = merge(l, L[r]), u = r;
	calc(u);
	return u;
}

void init (int n) {
	for (int i = 1; i <= n; i++) Y[i] = i, sz[i] = 1, L[i] = R[i] = 0;
	random_shuffle(Y+1, Y+n+1);
}

int n, q;

ll query (int & u) {
	return S[u];
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("dft.in", "r", stdin);
	freopen("dft.out", "w", stdout);
#endif
	srand(time(NULL)); rand(); rand();
	
	int u = 0;

	scanf("%d", &n);
	init(n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &X[i]);
		S[i] = X[i]*X[i];
		u = merge(u, i);
	}

	scanf("%d", &q);
	while (q--) {
		int a, b;
		scanf("%d %d", &a, &b);

		int bef, mid, aft, aux;
		split_sz(u, a-1, bef, aux);
		split_sz(aux, b-a+1, mid, aft);
		printf("%lld\n", query(mid));
		int first, most;
		split_sz(mid, 1, first, most);
		lz[most] = !lz[most];
		u = merge(merge(bef, first), merge(most, aft));
	}
}
