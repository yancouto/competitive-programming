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

int n;

inline void prn(const vector<int> &v) {
	for(int x : v) printf(" %d", x);
	putchar('\n');
}

ll solve(const vector<int> &turn_on, const vector<int> &turn_off, const vector<int> &always_on) {
	//printf("turn_on:"); prn(turn_on);
	//printf("turn_off:"); prn(turn_off);
	//printf("always_on:"); prn(always_on);
	ll sum_aon = accumulate(always_on.begin(), always_on.end(), 0ll);
	ll sum_toff = accumulate(turn_off.begin(), turn_off.end(), 0ll);
	ll ans = 0;
	for(ll x : turn_off) {
		sum_toff -= x;
		ans += sum_aon + sum_toff;
	}
	ll sum_ton = 0;
	for(ll x : turn_on) {
		sum_ton += x;
		ans += sum_aon + sum_ton;
	}
	//printf("ans = %lld\n", ans);
	return ans;
}

const int N = 11234;
int c[N];
char bef[N], aft[N];

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &c[i]);

	scanf("%s %s", bef, aft);
	vector<int> turn_on, turn_off, always_on;
	for(i = 0; i < n; i++) {
		if(bef[i] == '0' && aft[i] == '1') turn_on.pb(c[i]);
		if(bef[i] == '1' && aft[i] == '0') turn_off.pb(c[i]);
		if(bef[i] == '1' && aft[i] == '1') always_on.pb(c[i]);
	}
	sort(turn_on.begin(), turn_on.end());
	sort(turn_off.begin(), turn_off.end(), greater<int>());
	sort(always_on.begin(), always_on.end());
	ll best = solve(turn_on, turn_off, always_on);
	while(!always_on.empty()) {
		int x = always_on.back(); always_on.pop_back();
		turn_on.pb(x);
		for(int i = int(turn_on.size()) - 1; i > 0 && turn_on[i - 1] > turn_on[i]; i--) swap(turn_on[i], turn_on[i - 1]);
		turn_off.pb(x);
		for(int i = int(turn_off.size()) - 1; i > 0 && turn_off[i - 1] < turn_off[i]; i--) swap(turn_off[i], turn_off[i - 1]);
		best = min(best, solve(turn_on, turn_off, always_on));
	}
	printf("%lld\n", best);
}
