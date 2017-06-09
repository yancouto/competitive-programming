#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

char s[1123];
ll memo[100];
ll solve(ll n, int i) {
	if(n == 0) return 0;
	ll &r = memo[i];
	if(r != -1) return r;
	if(s[i] == '0') return r = solve(n - 1, i + 1);
	else return r = (1ll << n) - 1ll - solve(n - 1, i + 1);
}

int main() {
	int n;
	scanf("%d %s", &n, s);
	memset(memo, -1, sizeof memo);
	ll p = solve(n, 0);
	scanf("%s", s);
	memset(memo, -1, sizeof memo);
	ll p2 = solve(n, 0);
	printf("%lld\n", abs(p - p2) - 1ll);
}
