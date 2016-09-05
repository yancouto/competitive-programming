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

int n;
ull memo[52][52][52];
int seen[52][52][52];
ull solve(int i, int A, int B) {
	if(i == n) return 1;
	ull &r = memo[i][A][B];
	if(seen[i][A][B]) return r;
	seen[i][A][B] = 1;
	for(int a = 0; a <= A; a++)
		for(int b = 0; b <= B; b++)
			r += solve(i + 1, A - a, B - b);
	return r;
}

int main() {
	int a, b;
	scanf("%d %d %d", &n, &a, &b);
	printf("%llu\n", solve(0, a, b));
}
