#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int white = 0;
const int red = 1;
ll memo[50][4]; int n;
ll solve(int i, int last) {
	if(i == n) return 1;	
	ll &r = memo[i][last];
	if(r != -1) return r;
	r = 0;
	if(last != white) r += solve(i + 1, white);
	if(last != red) r += solve(i + 1, red);
	if(i < n - 1 && last <= red) r += solve(i + 2, !last);
	return r;
}

int main() {
	scanf("%d", &n);
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, 2));
}
