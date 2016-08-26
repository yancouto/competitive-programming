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

unordered_map<int, int> mp;
int n, a[30];
void calc1(int i, int A, int B) {
	if(i == n / 2) return (void) (mp[A - B] = max(mp[A - B], B));
	calc1(i + 1, A, B);
	calc1(i + 1, A + a[i], B);
	calc1(i + 1, A, B + a[i]);
}

int best = 0;
void calc2(int i, int A, int B) {
	if(i == n) {
		if(mp.count(B - A))
			best = max(best, mp[B - A] + B);
		return;
	}
	calc2(i + 1, A, B);
	calc2(i + 1, A + a[i], B);
	calc2(i + 1, A, B + a[i]);
}

int main() {
	while(scanf("%d", &n) && n) {
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		best = 0; mp.clear();
		calc1(0, 0, 0);
		calc2(n/2, 0, 0);
		printf("%d\n", accumulate(a, a + n, 0) - 2 * best);
	}
}
