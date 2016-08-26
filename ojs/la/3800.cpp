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

int n;
void prn(int i) { if(i < 0 || i >= n) putchar('*'); else printf("%d", i + 1); }

int l[100009], r[100009];
int main() {
	int i, m, a, b;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < n; i++)
			l[i] = i - 1, r[i] = i + 1;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			prn(l[a]); putchar(' '); prn(r[b]); putchar('\n');
			if(l[a] >= 0) r[l[a]] = r[b];
			if(r[b] < n) l[r[b]] = l[a];
		}
		puts("-");
	}
}
