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
const int N = 412345;

int a[N][2];
int tr[N][4], b[N][4];

void upd(int i, int l, int r, int x) {
	if(l == r) {
		for(int j = 0; j < 4; j++)
			tr[x][j] = a[x][0] * ((j&2) - 1) + a[x][1] * (2*(j&1) - 1),
			b[i][j] = x;
		return;
	}
	int m = (l + r) / 2;
	if(x <= m) upd(2*i, l, m, x);
	else upd(2*i+1, m + 1, r, x);
	for(int j = 0; j < 4; j++) 
		if(tr[b[2*i][j]][j] >= tr[b[2*i+1][j]][j])
			b[i][j] = b[2*i][j];
		else b[i][j] = b[2*i+1][j];
}

int get(int i, int l, int r, int x, int ql, int qr) {
	if(l > qr || r < ql) return -1;
	if(l >= ql && r <= qr) return b[i][x];
	int m = (l + r) / 2;
	int L = get(2*i, l, m, x, ql, qr);
	int R = get(2*i+1, m+1, r, x, ql, qr);
	if(L == -1 || (R != -1 && tr[R][x] > tr[L][x])) L = R;
	return L;
}

int main() {
	int i, x, y, j, n, q; char op;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &a[i][0], &a[i][1]);
		upd(1, 0, n - 1, i);
	}
	scanf("%d", &q);
	while(q--) {
		scanf(" %c", &op);
		if(op == 'U') {
			scanf("%d", &i); scanf("%d %d", &a[i][0], &a[i][1]);
			upd(1, 0, n - 1, i);
		} else {
			scanf("%d %d", &x, &y);
			int g[4];
			for(i = 0; i < 4; i++)
				g[i] = get(1, 0, n - 1, i, x, y);
			ll mx = 0;
			for(i = 0; i < 4; i++)
				for(j = i + 1; j < 4; j++)
					mx = max(mx, ll(abs(a[g[i]][0] - a[g[j]][0])) + ll(abs(a[g[i]][1] - a[g[j]][1])));
			printf("%lld\n", mx);
		}
	}
}
