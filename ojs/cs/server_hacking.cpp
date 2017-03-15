#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int n, m, d;
const int N = 1002, M = 100002;
int solve(int i, int j, int t) {
	if(i < 0 || i >= n) return 0;
	if(j == m) return 1;
	int r = 0;
	if(seen[i][j][t]) return memo[i][j][t];
	seen[i][j][t] = 1;
	if(door[j]) {
		if(n == d) return memo[i][j][t] = 0;
		// check collide
		int et = t % (2 * (n - d));
		int p = top[j] + et * dir[j];
		if(p > n - d) p = n - d - (p - (n - d));
		if(p < 0) p = -p;
		if(i < p || i >= p + d) return memo[i][j][t] = 0;
	}
	r = solve(i, j + 1, t + 1) || solve(i + 1, j + 1, t + 1) || solve(i - 1, j + 1, t + 1);
	return memo[i][j][t] = r;
}

inline int gou(int i, int di) { return max(0, i - di); }
inline int god(int i, int di) { return min(n - 1, i + di); }

bitset<N> canu[M];
bitset<N> cand[M];


struct door {
	int i, j, dir;
	door(){}
	door(int j_) : j(j_) {}
	void read() {
		char s;
		scanf("%d %d %c", &i, &j, &s); i--; j--;
		dir = (s == '+'? 1 : -1);
	}
	bool operator < (door o) const { return j < o.j; }
} d[M];

int main() {
	int i, r, c, q; char s;
	scanf("%d %d %d", &n, &m, &d);
	scanf("%d", &k);
	for(i = 0; i < k; i++)
		d[i].read();
	sort(d, d + k);
	for(i = 0; i < 2 * (n - d); i++) {
		canu[k - 1][i] = 1;
		cand[k - 1][i] = 1;
	}
	for(i = k - 2; i >= 0; i--) {
		int d = d[i].dir;
		int x = d[i].i;
		for(j = 0; j < 2 * (n - d); j++) {
			x += d;
			if(x < 0 || x == n) { d = -d; x += 2 * d; }
		}

	}
	scanf("%d", &q);
	while(q--) {
		scanf("%d %d", &r, &c); r--; c--;
		i = lower_bound(d, d + k, door(c)) - d;
		if(i == k) { puts("1"); continue; }
		if(n == d) { puts("0"); continue; }
		printf("%d\n", solveu(i, gou(r, d[i].j - c)) || solved(i, god(r, d[i].j - c)));
	}
}
