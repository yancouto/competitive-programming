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

int a[4];

int main () {
	int n = 4;
	while (scanf("%d", &a[0]) != EOF) {
		int sum = a[0];
		for (int i = 1; i < n; i++) {
			scanf("%d", &a[i]);
			sum += a[i];
		}

		int res = 1e8;
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++)
				res = min(res, abs(sum - 2*(a[i] + a[j])));
		
		printf("%d\n", res);
	}
}
