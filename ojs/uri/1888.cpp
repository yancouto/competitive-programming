#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char s1[3009], s2[3009];
double memo[3003][3003];
double mn[3003][3003];
int n, m, k;
inline void upd(int i, int j) {
	mn[i][j] = memo[i][j];
	if(j < m) mn[i][j] += mn[i][j + 1] - ((i < n)? mn[i + 1][j + 1] : 0);
	if(i < n) mn[i][j] += mn[i + 1][j];
}

int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &m, &k);
		scanf(" %s %s", s1, s2);
		memo[n][m] = 0;
		mn[n][m] = 0;
		for(i = n; i >= 0; i--)
			for(j = m; j >= 0; j--) {
				if(i == n && j == m) continue;
				double &r = memo[i][j];
				if(s1[i] == s2[j]) {
					r = memo[i+1][j+1];
				} else if(i == n) {
					r = min(1 + memo[i][j + 1], k + mn[i][j + 1] / (m - j));
				} else if(j == m) {
					r = min(1 + memo[i + 1][j], k + mn[i + 1][j] / (n - i));
				} else {
					r = 1 + min(memo[i + 1][j], memo[i][j + 1]);
					r = min(r, k + mn[i + 1][j + 1] / (double(m - j) * (n - i)));
				}
				upd(i, j);
			}
		printf("%.3f\n", memo[0][0]);
	}
}
