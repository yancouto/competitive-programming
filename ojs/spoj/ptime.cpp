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

const int N = 10001;
int p[N];
int main() {
	int i, n;
	scanf("%d", &n);
	for(; n > 1; n--) {
		int x = n;
		for(i = 2; i * i <= n; i++)
			while(!(x % i))
				p[i]++, x /= i;
		if(x > 1) p[x]++;
	}
	bool any = false;
	for(i = 2; i < N; i++)
		if(p[i] > 0) {
			if(any) printf(" * ");
			any = true;
			printf("%d^%d", i, p[i]);
		}
	putchar('\n');
}
