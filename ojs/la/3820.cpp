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

int v[1009];
int solve(int *vv, int n, int x) {
	int mn = INT_MAX;
	for(int i = 0; i < n; i++) {
		int cur = 0, rest = 0, cost = 0;
		memcpy(v, vv, sizeof v);
		for(int j = 0; j < n; j++) {
			int k = (i + j) % n;
			cost += rest + cur;
			v[k] += rest;
			rest = 0;
			int sub = min(v[k], cur);
			v[k] -= sub; cur -= sub;
			if(v[k] < x) cur += x - v[k];
			if(v[k] > x) rest = v[k] - x;
		}
		mn = min(mn, cost);
	}
	return mn;
}

int row[1009], col[1009];
int main() {
	int i, j, n, m; char c;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		memset(row, 0, sizeof row);
		memset(col, 0, sizeof col);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				if(c == '1') row[i]++, col[j]++;
			}
		int rn = accumulate(row, row + n, 0) / n;
		int cn = accumulate(col, col + m, 0) / m;
		bool r_ok = rn * n == accumulate(row, row + n, 0);
		bool c_ok = cn * m == accumulate(col, col + m, 0);
		int mv = 0;
		if(r_ok) mv += solve(row, n, rn);
		if(c_ok) mv += solve(col, m, cn);
		printf("Case %d: ", tt);
		if(r_ok && c_ok) printf("both ");
		else if(r_ok) printf("row ");
		else if(c_ok) printf("column ");
		else puts("impossible");
		if(r_ok || c_ok) printf("%d\n", mv);
	}
}
