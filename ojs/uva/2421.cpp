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
const int N = 4023456;
int p[N];
int dv[N];
ll t[N];

int main() {
	int i, j, n;
	for(i = 1; i < N; i++)
		p[i] = i;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i; j < N; j += i)
				p[j] = (p[j] / i) * (i - 1), dv[j] = 1;
	for(i = 1; i < N; i++)
		for(j = i; j < N; j += i)
			t[j] += ll(p[i]) * ll(j / i);
	for(i = 1; i < N; i++)
		t[i] += t[i - 1] - i;
	while(scanf("%d", &n) != EOF && n)
		printf("%lld\n", t[n]);
}
