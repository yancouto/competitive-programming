// TLE
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

char s[105];
int seen[103][100000], tempo;
ll memo[103][100000]; int n;
ll solve(int i, int c) {
	if(c >= 'z' + 27 * n) return 0;
	if(c <= 'a' - 27 * n) return 0;
	if(i >= n - 1) return c >= 'a' && c <= 'z';
	ll &r = memo[i][50000 + c];
	if(seen[i][50000 + c] == tempo) return r;
	seen[i][50000 + c] = tempo;
	r = 0;
	for(int j = 'a'; j <= 'z'; j++)
		r += solve(i + 1, s[i + 1] + c - j);
	return r = mod(r);
}

int main() {
	for_tests(t, tt) {
		scanf("%s", s);
		n = strlen(s);
		tempo++;
		printf("%d\n", (int) mod(solve(0, s[0]) - 1 + modn));
	}
}
