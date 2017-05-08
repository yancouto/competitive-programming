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

const int N = 112345;
int a[N];
char v[N];
int c[N], mn[N], mx[N];
int r[N];

int main() {
	int i, n;
	scanf("%d", &n);
	int cur = 0;
	int mx = 0, mn = 0;
	for(i = 0; i < n - 1; i++) {
		scanf("%d", &a[i]);
		cur -= a[i];
		mx = max(mx, cur);
		mn = min(mn, cur);
		c[i + 1] = cur;
	}
	for(i = n - 2; i >= 0; i--) {
		if(a[i] == 0) r[i] = r[i + 1];
		else if(a[i] == 1) r[i] = 0;
		else r[i] = r[i + 1] + 1;
	}
	cur = 9 - r[0];
	for(i = 0; i < n; i++) {
		if(cur < 0 || cur > 9 || (i == 0 && cur == 0)) {
			puts("-1");
			return 0;
		}
		v[i] = cur + '0';
		if(a[i] == 1) {
			cur--;
			if(r[i + 1] > 0) cur = min(cur, 9 - r[i + 1]);
		} else if(a[i] == -1) cur = max(cur + 1, 9 - r[i + 1]);
	}
	puts(v);
}
