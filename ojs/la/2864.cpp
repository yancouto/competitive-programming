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
const int N = 1123;

int k[N], a[N], b[N], p[N], g[N];


int main() {
	int i, n, A, B;
	while(scanf("%d %d %d", &n, &A, &B) != EOF && n) {
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &k[i], &a[i], &b[i]);
			p[i] = i; g[i] = 0;
		}
		int K = accumulate(k, k + n, 0);
		sort(p, p + n, [](int i, int j) { return a[i] - b[i] < a[j] - b[j]; });
		int G = 0;
		i = 0;
		while(G < K - B) {
			if(G + k[p[i]] <= K - B) { G += k[p[i]]; g[p[i]] = k[p[i++]]; continue; }
			g[p[i]] += (K - B) - G;
			G = K - B;
		}
		while(G < A && i < n && a[p[i]] < b[p[i]]) {
			if(G + k[p[i]] - g[p[i]] <= A) { G += k[p[i]] - g[p[i]]; g[p[i]] = k[p[i++]]; continue; }
			g[p[i]] += A - G;
			G = A;
		}
		int tot = 0;
		for(i = 0; i < n; i++)
			tot += g[i] * a[i] + (k[i] - g[i]) * b[i];
		printf("%d\n", tot);
	}
}
