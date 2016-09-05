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

char s[11234];
ll dp[11234];
int main() {
	int i;
	while(scanf("%s", s) != EOF && s[0] != '0') {
		dp[strlen(s)] = 1;
		for(i = strlen(s) - 1; i >= 0; i--)
			if(s[i] == '0') dp[i] = 0;
			else {
				dp[i] = dp[i + 1];
				if(s[i + 1] && (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6'))) dp[i] += dp[i + 2];
			}
		printf("%lld\n", dp[0]);
	}
}
