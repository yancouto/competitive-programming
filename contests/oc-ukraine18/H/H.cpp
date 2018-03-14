#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 212345;
int a[N], c[N];

int main() {
	int n, m, k, d, i;
	scanf("%d %d %d %d", &n, &m, &k, &d);
	for(i = 0; i < m; i++)
		scanf("%d", &c[i]);
	for(i = 0; i < k; i++)
		scanf("%d", &a[i]);
	sort(a, a + k);
	int l = 0, r = m;
	while(l < r) {
		//printf("[%d, %d]\n", l, r);
		int M = (l + r + 1) / 2;
		bool good = (a[M - 1] - 1 <= d);
		for(int i = 0; i < k; i++) {
			if(i + M < k) good = good && (a[i + M] - a[i] <= d);
			else good = good && (n - a[i] <= d);
		}
		//printf("[%d] good %d\n", M, good);
		if(good) l = M;
		else r = M - 1;
	}
	sort(c, c + m, greater<int>());
	if(l == 0) {
		ll ans = (a[0] - 1 > d);
		for(i = 1; i < k; i++)
			ans += (a[i] - a[i - 1] > d);
		ans += (n - a[k - 1] > d);
		printf("%lld\n", ans * c[m - 1] + accumulate(c, c + m - 1, 0ll));
	} else
		printf("%lld\n", accumulate(c + l, c + m, 0ll));
}
