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

struct no {
	int a, b, i;
	bool operator < (no o) const { return pii(a, b) < pii(o.a, o.b); }
	bool operator == (no o) const { return pii(a, b) == pii(o.a, o.b); }
} l[1009];
int p[1009][12], n;

int lcp(int i, int j) {
	int tot = 0;
	for(int k = 11; k >= 0; k--)
		if(p[i][k] == p[j][k] && i + (1 << k) <= n && j + (1 << k) <= n) {
			i += 1 << k;
			j += 1 << k;
			tot += 1 << k;
		}
	return tot;
}

char s[1009];
int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%s", s); n = strlen(s);
		for(i = 0; i < n; i++)
			p[i][0] = s[i];
		for(j = 1; j < 12; j++) {
			for(i = 0; i < n; i++)
				l[i] = no{p[i][j - 1], i + (1 << (j - 1)) < n? p[i + (1 << (j - 1))][j - 1] : -1, i};
			sort(l, l + n);
			for(i = 0; i < n; i++)
				p[l[i].i][j] = i && l[i-1] == l[i]? p[l[i-1].i][j] : i;
		}
		int r[1009], lc[1009];
		for(i = 0; i < n; i++)
			r[p[i][11]] = i;
		int tot = (n * (n + 1)) / 2;
		for(i = 0; i < n - 1; i++)
			tot -= lcp(r[i], r[i + 1]);
		printf("%d\n", tot);
	}
}
