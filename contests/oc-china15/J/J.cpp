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

const int N = 212345;
int a[N], n, m;

int solve(int bm) {
	int x = 0, ct = 0;
	for(int i = 0; i < n - 1; i++) {
		x ^= a[i];
		if((x & bm) == 0) x = 0, ct++;
	}
	x ^= a[n - 1];
	if(x & bm) return 0;
	return ct + 1;
}

int main() {
	int i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int cur = 0, num = 0;
	for(i = 30; i >= 0; i--) {
		int ne = cur | (1 << i);
		//printf("solve(%s) = %d\n", bitset<32>(ne).to_string().c_str(), solve(ne));
		if(solve(ne) >= m) cur = ne, num = num * 2;
		else num = num * 2 + 1;
	}
	printf("%d\n", num);
}
