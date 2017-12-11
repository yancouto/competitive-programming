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

int T;
const int N = 112345;

short mp[320][1 << 20];
int apply[500];
int a[N], act[N];

int main() {
	int i, n, q, op;
	scanf("%d %d", &n, &q);
	T = sqrt(n);
	int x, cur = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		cur ^= x;
		a[i] = cur;
		act[i] = x;
		mp[i / T][cur]++;
	}
	while(q--) {
		scanf("%d %d %d", &op, &i, &x); i--;
		int t = i / T;
		if(op == 1) {
			x ^= act[i];
			act[i] ^= x;
			for(int tt = t + 1; tt <= int((n - 1) / T); tt++)
				apply[tt] ^= x;
			for(; i < n && int(i / T) == t; i++) {
				mp[t][a[i]]--;
				a[i] ^= x;
				mp[t][a[i]]++;
			}
		} else {
			int ct = 0;
			for(int tt = 0; tt < t; tt++)
				ct += int(mp[tt][x ^ apply[tt]]);
			for(; i >= 0 && int(i / T) == t; i--)
				if((a[i] ^ apply[t]) == x)
					ct++;
			printf("%d\n", ct);
		}
	}
}
