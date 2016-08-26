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

const int N = 212345;

int en = 1, root = 0;
int Y[N], X[N], sz[N], L[N], R[N];

int mx(int u) { while(R[u]) u = R[u]; return u; }

void calc(int u) {
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
}

void split_val(int u, int x, int &l, int &r) {
	if(!u) return (void) (l = r = 0);
	if(X[u] <= x) split_val(R[u], x, l, r), R[u] = l, l = u;
	else split_val(L[u], x, l, r), L[u] = r, r = u;
	calc(u);
}

void split_sz(int u, int s, int &l, int &r) {
	if(!u) return (void) (l = r = 0);
	if(sz[L[u]] < s) split_sz(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split_sz(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

int merge(int l, int r) {
	if(!l || !r) return l + r;
	int u;
	if(Y[l] > Y[r]) R[l] = merge(R[l], r), u = l;
	else L[r] = merge(l, L[r]), u = r;
	calc(u);
	return u;
}

void init() {
	for(int i = 1; i < N; i++) Y[i] = i, sz[i] = 1;
	random_shuffle(Y, Y + N);
}

int main() {
	int i, x, p1, p2, p3; char op;
	init();
	for_tests(qn, qt) {
		scanf(" %c %d", &op, &x);
		assert(sz[0] == 0);
		if(op == 'I') {
			split_val(root, x, p1, p2);
			if(sz[p1] && X[mx(p1)] == x) { root = merge(p1, p2); continue; }
			X[en] = x; assert(sz[en] == 1);
			root = merge(merge(p1, en++), p2);
		} else if(op == 'D') {
			split_val(root, x-1, p1, p2);
			split_val(p2, x, p2, p3);
			root = merge(p1, p3);
		} else if(op == 'K') {
			assert(x > 0);
			if(x > sz[root]) { puts("invalid"); continue; }
			split_sz(root, x, p1, p2);
			printf("%d\n", X[mx(p1)]);
			root = merge(p1, p2);
		} else /*op == 'C'*/ {
			split_val(root, x - 1, p1, p2);
			printf("%d\n", sz[p1]);
			root = merge(p1, p2);
		}
	}
}
