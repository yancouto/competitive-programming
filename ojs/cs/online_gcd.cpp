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
const int N = 112345;

int mdc(int a, int b) { return b? mdc(b, a % b) : a; }

int ps[100], pn;
multiset<int> C[100];
int cc[N][12];
int a[N];

int main() {
	int i, n, m, j, k;
	scanf("%d %d", &n, &m);
	int g = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		g = mdc(a[i], g);
	}
	int x = g;
	for(i = 2; i * i <= x; i++) {
		if(x % i) continue;
		while(!(x % i)) x /= i;
		ps[pn++] = i;
	}
	if(x != 1) ps[pn++] = x;
	for(i = 0; i < n; i++)
		for(j = 0; j < pn; j++) {
			int ct = 0;
			while(!(a[i] % ps[j])) a[i] /= ps[j], ct++;
			C[j].insert(ct);
			cc[i][j] = ct;
		}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &k, &x); k--;
		for(j = 0; j < pn; j++)
			while(!(x % ps[j])) {
				if(*C[j].begin() == cc[k][j]) g /= ps[j];
				C[j].erase(C[j].find(cc[k][j]));
				C[j].insert(--cc[k][j]);
				x /= ps[j];
			}
		printf("%d\n", g);
	}
}
