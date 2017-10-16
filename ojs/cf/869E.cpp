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

int n;

const int M = 13000000;

int L[M], R[M], UD[M];
int tr[M], lz[2][M];
int en = 1;

void cr(int &i) {
	if(i == 0) {
		i = en++;
		tr[i] = 2500 * 2500;
		assert(en < M);
	}
}

void unlazeud(int &i, int l, int r) {
	if(!i) return;
	if(lz[0][i] != 0) {
		tr[i] = lz[0][i];
		printf("setting to %d\n", tr[i]);
		if(l != r) {
			cr(L[i]); cr(R[i]);
			lz[0][L[i]] = lz[0][i]; lz[1][L[i]] = 0;
			lz[0][R[i]] = lz[0][i]; lz[1][R[i]] = 0;
		}
		lz[0][i] = 0;
	}
	if(lz[1][i] != 0) {
		printf("<setting to %d\n", tr[i]);
		tr[i] = min(tr[i], lz[1][i]);
		printf(">setting to %d\n", tr[i]);
		if(l != r) {
			cr(L[i]); cr(R[i]);
			lz[1][L[i]] = lz[1][i];
			lz[1][R[i]] = lz[1][i];
		}
		lz[1][i] = 0;
	}
}

void unlaze(int &i, int l, int r) {
	return;
}

int getud(int &i, int l, int r, int p) {
	unlazeud(i, l, r);
	printf("%d: (%d, %d) %d\n", i, l, r, tr[i]);
	if(i == 0) return 2500 * 2500;
	if(l == r) return tr[i];
	int m = (l + r) / 2;
	if(p <= m) return getud(L[i], l, m, p);
	else return getud(R[i], m + 1, r, p);
}

int get(int &i, int l, int r, int pi, int pj) {
	unlaze(i, l, r);
	if(i == 0) return 2500 * 2500;
	if(l == r) return getud(UD[i], 1, 2500, pj);
	int m = (l + r) / 2;
	if(pi <= m) return get(L[i], l, m, pi, pj);
	else return get(R[i], m + 1, r, pi, pj);
}

void updud(int &i, int l, int r, int ql, int qr, int x, bool lo) {
	unlazeud(i, l, r);
	cr(i);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		printf("setting %d to %d\n", i, x);
		lz[lo][i] = x;
		unlazeud(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	updud(L[i], l, m, ql, qr, x, lo);
	updud(R[i], m + 1, r, ql, qr, x, lo);
}

void upd(int &i, int l, int r, int li, int ri, int lj, int rj, int x, bool lo) {
	unlaze(i, l, r);
	cr(i);
	if(l > ri || r < li) return;
	if(l >= li && r <= ri) printf("split at [%d, %d]\n", l, r);
	if(l >= li && r <= ri) return updud(UD[i], 1, 2500, lj, lj, x, lo);
	int m = (l + r) / 2;
	upd(L[i], l, m, li, ri, lj, rj, x, lo);
	upd(R[i], m + 1, r, li, ri, lj, rj, x, lo);
}

int main() {
	int i, j;
	int m, q, t, r1, c1, r2, c2;
	scanf("%d %d %d", &n, &m, &q);
	int root = 0;
	for(i = 0; i < q; i++) {
		scanf("%d %d %d %d %d", &t, &r1, &c1, &r2, &c2);
		if(t == 2) {
			int x = get(root, 1, 2500, r1 - 1, c1 - 1);
			upd(root, 1, 2500, r1, r2, c1, c2, x, false);
		} else if(t == 1) {
			upd(root, 1, 2500, r1, r2, c1, c2, (r2 - r1 + 1) * (c2 - c1 + 1), true);
		} else {
			printf("%d %d\n", get(root, 1, 2500, r1, c1), get(root, 1, 2500, r2, c2));
			if(get(root, 1, 2500, r1, c1) == get(root, 1, 2500, r2, c2))
				puts("Yes");
			else
				puts("No");
		}
	}
}
