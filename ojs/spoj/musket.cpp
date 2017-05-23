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

const int N = 212;
char A[N][N];
int memo[N][N], n;
int ok(int l, int r) {
	if(r < l) return true;
	int &a = memo[l][r];
	if(a != -1) return a;
	for(int i = l; i <= r; i++)
		if((A[(l - 1) % n][i % n] == '1' || A[(r + 1) % n][i % n] == '1') && ok(l, i - 1) && ok(i + 1, r)) {
			return a = 1;
		}
	return a = 0;
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%s", A[i]);
		memset(memo, -1, sizeof memo);
		vector<int> v;
		for(i = 0; i < n; i++)
			if(ok(i + 1, i + n - 1))
				v.pb(i);
		printf("%d\n", (int) v.size());
		for(int x : v)
			printf("%d\n", x + 1);
	}
}
