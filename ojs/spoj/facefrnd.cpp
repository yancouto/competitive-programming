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

int f[112345], ff[112345];
int main() {
	int i, n, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &x); f[x] = 1;
		for_tests(q, qq) {
			scanf("%d", &x);
			ff[x] = 1;
		}
	}
	int ct = 0;
	for(i = 0; i < 112345; i++)
		if(ff[i] && !f[i])
			ct++;
	printf("%d\n", ct);
}
