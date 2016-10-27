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

const int N = 1e5+7;

int n;
char str[N];
int to[2][N];
bool visi[N];
int curr;

int find (int x, int d) {
	if (!visi[x]) return x;
	return to[d][x] = find(to[d][x], d);
}

bool solve (int x) {
	for (int i = 0; i <= n+1; i++) {
		visi[i] = 0;
		to[0][i] = i-1;
		to[1][i] = i+1;
	}

	curr = 0;

	while (true) {
		if (x == 0) return 0;
		if (x == n+1) return 1;

		curr++;
		visi[x] = 1;
		x = find(x, (str[x] == '>'));
	}

	assert(false);
}

int main () {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf(" %c", &str[i]);

	int lo = 0;
	int hi = n+1;

	while (lo < hi) {
		int mid = (lo+hi+1)/2;

		if (solve(mid))
			hi = mid-1;
		else 
			lo = mid;
	}

	int res = 0;
	solve(lo);
	res = max(res, curr);
	solve(lo+1);
	res = max(res, curr);
	printf("%d\n", res);
}
