#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 212345;
char s[N];
int F[N];

void build(int n) {
	F[1] = 0;
	for(int i = 2; i <= n; i++) {
		F[i] = F[i - 1];
		while(F[i] && s[F[i] + 1] != s[i])
			F[i] = F[F[i]];
		if(s[F[i] + 1] == s[i])
			F[i]++;
	}
}

int memo[N][30];

int fst[N];
int go[N][20];

int solve(int, int);

inline bool ok(int n, int k, int b) {
	if(!b) return false;
	if(3 * b < n) {
		if(k == 2) { return true; }
	} else {
		if(k == 2) { return true; }
		else if(solve(n - b, k - 1) <= b) {
			return true;
		}
	}
	return false;
}

int solve(int n, int k) {
	int &r = memo[n][k];
	if(r != -1) return r;
	if(k == 1) return r = n;
	r = INT_MAX;
	if(fst[n] == 0) return r;
	//vector<int> F;
	//F.resize(n + 1);
	//build(n, F);
	
	if(ok(n, k, fst[n])) r = n - fst[n];
	else {
		int b = fst[n];
		for(int j = 17; j >= 0; j--)
			if(!ok(n, k, go[b][j]))
				b = go[b][j];
		if(ok(n, k, b))
			r = n - b;
	}

	//for(int b = fst[n]; b; b = F[b]) {
	//	//printf("at [%d] found b = %d\n", n, b);
	//}
	//printf("solve(%d, %d) = %d\n", n, k, r);
	return r;
}

int mn[N];
int mni[N];

const int M = N * 60;
int tr[M], L[M], R[M];
int en;

int build(int l, int r) {
	int i = en++;
	tr[i] = INT_MAX;
	if(l == r) { return i; }
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

int set_(int oi, int l, int r, int p, int x) {
	int i = en++;
	L[i] = L[oi]; R[i] = R[oi];
	if(l == r) {  tr[i] = min(tr[oi], x); return i; }
	int m = (l + r) / 2;
	if(p <= m) L[i] = set_(L[i], l, m, p, x);
	else R[i] = set_(R[i], m + 1, r, p, x);
	tr[i] = min(tr[L[i]], tr[R[i]]);
	return i;
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return INT_MAX;
	if(l >= ql && r <= qr) {  return tr[i]; }
	int m = (l + r) / 2;
	return min(get(L[i], l, m, ql, qr), get(R[i], m + 1, r, ql, qr));
}

int root[2][N];

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	build(n);
	for(int i = 1; i <= n; i++) {
		go[i][0] = F[i];
		for(int j = 1; j < 18; j++)
			go[i][j] = go[go[i][j - 1]][j - 1];
	}
	for(int i = 1; i <= n; i++) {
		fst[i] = i;
		for(int j = 17; j >= 0; j--)
			if(2 * go[fst[i]][j] > i)
				fst[i] = go[fst[i]][j];
		fst[i] = F[fst[i]];
	}
	en = 0;
	root[1&1][0] = build(1, 2 * n);
	for(int i = 1; i <= n; i++) {
		memo[i][1] = i;
			printf("[%d] %d set_(%d, %d)\n", F[i], 1, i + i, i);
		root[1&1][i] = set_(root[1&1][F[i]], 1, 2 * n, memo[i][1] + i, i);
	}
	for(int k = 2; k <= 26; k++) {
		root[k&1][0] = build(1, 2 * n);
		for(int i = 1; i <= n; i++) {
			int &r = memo[i][k];
			r = INT_MAX;
			if(fst[i] != 0) {
				int v = get(root[!(k&1)][fst[i]], 1, 2 * n, 1, i);
				printf("[%d] %d get(<=%d) = %d\n", k - 1, fst[i], i, v);
				r = v;
			}
			printf("memo[%d][%d] = %d\n", i, k, memo[i][k]);
			if(r != INT_MAX) {
				printf("[%d]set_(%d, %d)\n", k, r + i, i);
				root[k&1][i] = set_(root[k&1][F[i]], 1, 2 * n, r + i, i);
			} else
				root[k&1][i] = root[k&1][F[i]];
		}
	}
	for(int i = 26; i >= 0; i--)
		if(memo[n][i] != INT_MAX) {
			printf("%d\n", i);
			return 0;
		}
}
