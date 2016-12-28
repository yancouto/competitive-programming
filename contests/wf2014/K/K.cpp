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

const int N = 2000009, L = 23;

int all[N], nx[L][N], best[N];

int main() {
	int i, j, a, b, n, k;
	scanf("%d %d", &n, &k);
	vector<pii> v;
	for(i = 0; i < k; i++) {
		scanf("%d %d", &a, &b);
		if(a <= b) {
			all[a]++;
			all[b + 1]--;
			v.pb(pii(a, b));
			v.pb(pii(a + n, b + n)); // necessary?
		} else {
			all[1]++;
			all[b + 1]--;
			all[a]++;
			all[n + 1]--;
			v.pb(pii(a, b + n));
			v.pb(pii(a + n, b + 2 * n));
		}
	}
	for(i = 1; i <= n; i++) {
		all[i] += all[i - 1];
		if(!all[i]) {
			puts("impossible");
			return 0;
		}
	}
	auto cmp = [](pii a, pii b) { return a.fst < b.fst; };
	sort(v.begin(), v.end(), cmp);
	for(i = 1; i < v.size(); i++) {
		if(v[i].snd > v[best[i - 1]].snd) best[i] = i;
		else best[i] = best[i - 1];
	}
	for(i = 0; i < v.size(); i++) {
		int p = (upper_bound(v.begin(), v.end(), pii(v[i].snd + 1, 0), cmp) - v.begin()) - 1;
		assert(p >= 0);
		nx[0][i] = best[p];
		assert(v[best[p]].snd >= v[i].snd);
		if(v[best[p]].snd == v[i].snd) nx[0][i] = -1;
	}
	for(j = 1; j < L; j++)
		for(i = 0; i < v.size(); i++)
			nx[j][i] = (nx[j - 1][i] == -1? -1 : nx[j - 1][nx[j - 1][i]]);
	int best = INT_MAX;
	for(i = 0; i < v.size(); i++) {
		a = v[i].fst;
		if(v[i].snd >= a + n - 1) {
			best = min(best, 1);
			continue;
		}
		int cur = i;
		int ans = 1;
		for(j = L - 1; j >= 0; j--)
			if(nx[j][cur] != -1 && v[nx[j][cur]].snd < a + n - 1)
				ans += (1 << j), cur = nx[j][cur];
		if(nx[0][cur] != -1) {
			ans++;
			cur = nx[0][cur];
			assert(v[cur].snd >= a + n - 1);
			best = min(best, ans);
		}
	}
	printf("%d\n", best);
}
