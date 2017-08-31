#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const int N = 112345;

const int M = 3123456;

int L[M], R[M];
pii tr[M];

int en = 1;

inline void new_node(int &i) {
	i = en++;
	assert(i < M);
}

void set_(int &i, int l, int r, int p, pii x) {
	if(!i) new_node(i);
	if(l == r) return (void) (tr[i] = max(tr[i], x));
	int m = (l + r) / 2;
	if(p <= m) set_(L[i], l, m, p, x);
	else set_(R[i], m + 1, r, p, x);
	tr[i] = max(tr[L[i]], tr[R[i]]);
}

pii get(int i, int l, int r, int ql, int qr) {
	if(!i) return pii(0, 0);
	if(r < ql || l > qr) return pii(0, 0);
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(get(L[i], l, m, ql, qr), get(R[i], m + 1, r, ql, qr));
}

int n, a[N], k;
pii dp[N];

const int G = 1000000000;
int main() {
#ifdef ONLINE_JUDGE
	freopen("financial.in", "r", stdin);
	freopen("financial.out", "w", stdout);
#endif
	scanf("%d %d", &n, &k);
	int i;
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int best = -1, bi;
	int root = 0;
	for(i = n - 1; i >= 0; i--) {
		dp[i] = max(get(root, 1, G, 1, a[i] - k), get(root, 1, G, a[i] + k, G));
		dp[i].fst++;
		if(dp[i].fst > best) best = dp[i].fst, bi = i;
		set_(root, 1, G, a[i], pii(dp[i].fst, i));
	}
	printf("%d\n", best);
	while(best--) {
		printf("%d", a[bi]);
		if(best) putchar(' ');
		bi = dp[bi].snd;
	}
	putchar('\n');
}
