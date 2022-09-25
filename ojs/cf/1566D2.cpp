#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, m;

int bit[303][400];
int get(int x, int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum = (sum + bit[x][i]);
	return sum;
}
int get(int x, int i, int j) { return get(x, j) - get(x, i - 1); }
void add(int x, int i, int v) {
	for(i += 2; i < m + 5; i += (i & -i))
		bit[x][i] = (bit[x][i] + v);
}

struct group {
	int first_idx;
	int size;
	int cur_row;
};

int a[112345];

ll solve() {
	scanf("%d %d", &n, &m);
	map<int, group> mp;
	for(int i = 0; i < n * m; i++) { scanf("%d", &a[i]); mp[a[i]].size++; }
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m + 5; j++)
			bit[i][j] = 0;
	int cur = 0;
	for(auto &x : mp) {
		x.snd.first_idx = cur;
		x.snd.cur_row = cur / m;
		cur += x.snd.size;
	}
	ll tot = 0;
	for(int i = 0; i < n * m; i++) {
		group& d = mp[a[i]];
		int& cur_row = d.cur_row;
		int idx = max(d.first_idx - cur_row * m, 0);
		debug("[%d] group (fst %d, sz %d, cur %d) idx %d\n", i, d.first_idx, d.size, d.cur_row, idx);
		add(cur_row, idx, 1);
		tot += get(cur_row, idx - 1);
		int oc = cur_row;
		if (cur_row == d.first_idx / m) {
			if (get(cur_row, idx, idx) == m - idx)
				cur_row++;
		} else if(get(cur_row, idx, idx) == m) cur_row++;
		if (oc != cur_row) debug("CHANGE LINE\n");
		assert(cur_row == mp[a[i]].cur_row);
	}
	return tot;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) printf("%lld\n", solve());
}
