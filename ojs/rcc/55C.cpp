#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

vector<pii> ans;

void go2(int n, int x, int y) {
	while(n > 0) {
		y -= n;
		ans.pb(pii(x, y));
		if(--n == 0) return;
		x -= n;
		ans.pb(pii(x, y));
		if(--n == 0) return;
		y += n;
		ans.pb(pii(x, y));
		if(--n == 0) return;
		x += n;
		ans.pb(pii(x, y));
		n--;
	}
}

void go(int n, int k) {
	int step = 10000;
	int mid = 1e9 / 2;
	int i = 0;
	ans.pb(pii(0, mid));
	ans.pb(pii(mid - 1, mid)); n -= 2;
	int cur = 0;
	for(i = 1; n > 0; i++) {
		if(cur > k) {
			int y = mid + (i - 1 - k - 1) * step + 1;
			ans.pb(pii(mid - i, y));
			if(--n == 0) return;
			mid -= 2000;
			ans.pb(pii(mid - i, y));
			if(--n == 0) return;
			y += 2000;
			ans.pb(pii(mid - i, y));
			if(--n == 0) return;
			ans.pb(pii(mid - i + 1900, y));
			return go2(n - 1, mid - i + 1900, y);
		} else k -= cur;
		ans.pb(pii(mid - i, mid - i * step));
		cur++;
		if(--n == 0) break;
		ans.pb(pii(i, mid - i * step));
		if(--n == 0) break;
		if(cur > k) {
			int y = mid + (-i + k) * step + 2000;
			k = 0;
			ans.pb(pii(i, y));
			if(--n == 0) return;
			ans.pb(pii(i + 2000, y));
			return go2(n - 1, i + 2000, y);
		} else k -= cur;
		ans.pb(pii(i, mid + i * step));
		if(--n == 0) break;
		ans.pb(pii(mid - i - 1, mid + i * step));
		cur++; n--;
	}
	assert(k == 0);
}

int st[3123], sn;
int main() {
	int i, n, k;
	for_tests(t, tt) {
		ans.clear();
		scanf("%d %d", &n, &k); n++;
		if(n <= 4) {
			puts("10 10");
			if(n >= 2) puts("11 10");
			if(n >= 3) puts("11 9");
			if(n >= 4) puts("10 9");
			continue;
		}
		go(n, k);
		for(i = 0; i < n; i++)
			st[2*i] = ans[i].x, st[2*i+1] = ans[i].y;
		sort(st, st + 2*n);
		sn = unique(st, st + 2*n) - st;
		assert(ans.size() == n);
		for(i = 0; i < n; i++)
			ans[i].x = int(lower_bound(st, st + sn, ans[i].x) - st) + 1,
			ans[i].y = int(lower_bound(st, st + sn, ans[i].y) - st) + 1;
		for(i = 0; i < n; i++) printf("%d %d\n", ans[i].x, ans[i].y);
	}
}
