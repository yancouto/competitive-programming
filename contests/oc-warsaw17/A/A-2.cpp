#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

inline void rd(int &x) {
	char c;
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int d;

ll ans;

int S[812][5123], sz[812][5123];
int n;

#define get get_
int get[5123];

void build(int i, int l, int r) {
	for(int j = 0; j < n; j++)
		S[i][j] = j, sz[i][j] = 1;
	if(l == r) {
		get[l] = i;
		return;
	}
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

int find(int k, int i) {
	if(S[k][S[k][i]] != S[k][i]) S[k][i] = find(k, S[k][i]);
	return S[k][i];
}

void join(int k, int a, int b) {
	//printf("join(%d, %d, %d)\n", k, a, b);
	if((a = find(k, a)) == (b = find(k, b))) return;
	//puts("ok");
	if(sz[k][a] < sz[k][b]) swap(a, b);
	S[k][b] = a;
	if(k == 1) ans += 2ll * ll(sz[k][a]) * ll(sz[k][b]);
	sz[k][a] += sz[k][b];
}

int main() {
	srand(time(NULL));
	int i, j, m;
	rd(d); rd(n); rd(m);
	build(1, 1, d);
	ans = n;
	for(i = 0; i < m; i++) {
		int a, b, k;
		rd(a); rd(b); rd(k); a--; b--;
		int x = get[k];
		while(x >= 1) {
			join(x, a, b);
			if(x != 1 && find(x ^ 1, a) == find(x ^ 1, b))
				x /= 2;
			else break;
		}
		printf("%lld\n", ans);
	}
}
