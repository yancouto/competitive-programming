#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int memo[1000009], v[1000009], n;
int solve(int i) {
	if(i >= n) return 0;
	int &r = memo[i];
	if(r) return r;
	return r = max(solve(i + 1), v[i] + solve(i + 3));
}

int sum[3];
int main() {
	int i, x;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	printf("%d\n", solve(0));
	return 0;
}
