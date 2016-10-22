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
typedef long double ld;
const int N = 100;
int t[N];
ld p[N];

int main() {
	int i, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %Lf", &t[i], &p[i]);
		ld tot = 0;
		for(i = n - 1; i >= 0; i--) {
			if(i < n - 1) p[i] *= p[i + 1];
			tot += t[i] / p[i];
		}
		printf("%.10Lf\n", tot);
	}
}
