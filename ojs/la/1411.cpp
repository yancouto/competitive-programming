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

int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};
int g[52][52], f[52][52];
int n;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }
void sim(int i, int j, int d) {
	while(true) {
		if(!valid(i, j)) {
			printf("%d %d\n", i + 1, j + 1);
			return;
		}
		if(f[i][j] & (1 << d)) { puts("0 0"); return; }
		f[i][j] |= (1 << d);
		if(g[i][j]) d = (d + 1) % 4;
		i += di[d];
		j += dj[d];
	}
}

int main() {
	int r, i, j, a, b;
	for_tests(t, tt) {
		scanf("%d %d", &n, &r);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				g[i][j] = f[i][j] = 0;
		for(i = 0; i < r; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			g[a][b] = 1;
		}
		scanf("%d %d", &a, &b);
		int d = 0;
		if(a == 0) d = 2;
		else if(a == n + 1) d = 0;
		else if(b == 0) d = 1;
		else d = 3;
		a = a - 1 + di[d];
		b = b - 1 + dj[d];
		sim(a, b, d);
	}
}
