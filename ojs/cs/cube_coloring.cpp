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

ll a2(ll x) { return x * (x - 1ll); }
ll a3(ll x) { return x * (x - 1ll) * (x - 2ll); }

ll ct[4][N];
int a[N];

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		a[i] = 2;
		scanf("%d", &a[i]);
		if(a[i] > 1) a[i] = 2;
	}
	sort(a, a + n);
	for(i = n - 1; i >= 0; i--) {
		ct[1][i] = ct[1][i + 1];
		ct[2][i] = ct[2][i + 1];
		ct[a[i]][i]++;
	}
	ull tot = 0;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n - 1; j++) {
			//1 double 2 double 3 double
			if(a[i] == 2 && a[j] == 2) tot += ct[2][j + 1];
			//1 double 2 double 3
			if(a[i] == 2 && a[j] == 2) tot += a2(ct[1][j + 1] + ct[2][j + 1]);
			//1 double 2        3 double
			if(a[i] == 2) tot += ll(ct[2][j + 1]) * ll(ct[1][j + 1] + ct[2][j + 1] - 1);
			//1 double 2        3
			if(a[i] == 2) tot += a3(ct[1][j + 1] + ct[2][j + 1]);
			//1        2 double 3 double
			if(a[j] == 2) tot += ll(ct[2][j + 1]) * ll(ct[1][i + 1] + ct[2][i + 1] - 2);
			//1        2 double 3
			if(a[j] == 2) tot += a2(ct[1][j + 1] + ct[2][j + 1]) * ll(ct[1][i + 1] + ct[2][i + 1] - 3);
			//1        2        3 double
			tot += ll(ct[2][j + 1]) * ll(ct[1][j + 1] + ct[2][j + 1] - 1) * ll(ct[1][i + 1] + ct[2][i + 1] - 3);
			//1        2        3
			tot += a3(ct[1][j + 1] + ct[2][j + 1]) * ll(ct[1][i + 1] + ct[2][i + 1] - 4);
		}
	printf("%llu\n", tot);
}
