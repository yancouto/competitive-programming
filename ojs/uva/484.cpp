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
const int N = 1123456;
int dv[N];

int main() {
	int i, j, n;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i + i; j < N; j += i)
				dv[j] = 1;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 3; 2*i <= n; i++)
			if(!dv[i] && !dv[n - i]) {
				printf("%d = %d + %d\n", n, i, n - i);
				break;
			}
		assert(2*i<=n);
	}
}
