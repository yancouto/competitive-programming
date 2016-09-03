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

int a[11234], p[11234];
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int cur = 0;
	p[0] = 0;
	for(i = 1; i <= n; i++) {
		cur = (cur + a[i]) % n;
		if(p[cur] || !cur) {
			printf("%d\n", i - p[cur]);
			for(int j = p[cur] + 1; j <= i; j++)
				printf("%d\n", a[j]);
			return 0;
		}
		p[cur] = i;
	}
}
