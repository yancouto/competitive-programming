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
const int N = 312;

int l[N], n[N][N], h[N][N], f[N], ok[N], good[N];
vector<int> v[N][N]; vector<pii> nx[N];
int p, r;
bool is_dead(int t) {
	int i, j;
	for(i = 0; i < r; i++) f[i] = l[i], nx[i].clear();;
	int tot = 0;
	for(i = 0; i < p; i++) {
		ok[i] = true;
		good[i] = 0;
		for(j = 0; j < r; j++) {
			h[i][j] = upper_bound(v[i][j].begin(), v[i][j].end(), t) - v[i][j].begin();
			ok[i] &= (h[i][j] == n[i][j]);
			f[j] -= h[i][j];
		}
		if(ok[i])
			for(j = 0; j < r; j++)
				f[j] += h[i][j];
		tot += ok[i];
	}
	for(i = 0; i < p; i++)
		for(j = 0; j < r; j++)
			if(h[i][j] + f[j] >= n[i][j])
				good[i]++;
			else
				nx[j].pb(pii(n[i][j] - h[i][j], i));
	for(i = 0; i < r; i++) sort(nx[i].begin(), nx[i].end(), greater<pii>());
	for(; tot < p; tot++) {
		for(i = 0; i < p && (ok[i] || good[i] < r); i++);
		if(i == p) return true;
		ok[i] = true;
		for(j = 0; j < r; j++) {
			f[j] += h[i][j];
			while(!nx[j].empty() && nx[j].back().fst <= f[j])
				good[nx[j].back().snd]++, nx[j].pop_back();
		}
	}
	return false;
}

int main() {
	int i, j, t, P, R;
	while(scanf("%d %d %d", &p, &r, &t) != EOF) {
		for(i = 0; i < r; i++) scanf("%d", &l[i]);
		for(i = 0; i < p; i++)
			for(j = 0; j < r; j++)
				scanf("%d", &n[i][j]), v[i][j].clear();
		for(i = 0; i < t; i++) {
			scanf("%d %d", &P, &R); P--; R--;
			v[P][R].pb(i);
		}
		if(!is_dead(t - 1)) { puts("-1"); continue; }
		int l = 0, r = t - 1;
		while(l < r) {
			int m = (l + r) / 2;
			if(is_dead(m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l + 1);
	}
}
