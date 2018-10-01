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

const int N = 112345;

struct st {
	int a, b, c;
	bool operator < (st o) const {
		return a < o.a;
	}
} a[N];

int bit[N];
int get(int i) {
	int mn = N;
	for(i += 2; i; i -= (i & -i))
		mn = min(mn, bit[i]);
	return mn;
}

void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] = min(bit[i], x);
}

int main() {
	for_tests(tn, tt) {
		int i, n;
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d %d %d", &a[i].a, &a[i].b, &a[i].c);
		sort(a, a + n);
		for(i = 0; i < n + 100; i++) bit[i] = N;
		int ans = 0;
		for(i = 0; i < n; i++) {
			assert(a[i].a == i + 1);
			int g = get(a[i].b);
			if(g > a[i].c) ans++;
			add(a[i].b, a[i].c);
		}
		printf("%d\n", ans);
	}
}
