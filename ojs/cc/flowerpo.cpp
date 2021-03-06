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

vector<vector<ll>> *memo;

const int N = 4123;

typedef long double ld;
struct lin {
	ll a, b;
};

inline ld inter_x(lin l, lin m) {
	return ld(ld(m.b) - l.b) / (ld(l.a) - m.a);
}

deque<lin> st;

void add(lin l) {
	//printf("adding (%lldx + %llu)\n", l.a, l.b);
	while(st.size() > 1 && inter_x(st[0], st[1]) < inter_x(l, st[1]))
		st.pop_front();
	st.push_front(l);
}

ld query(ll x) {
	//printf("query(%lld)\n", x);
	while(st.size() > 1 && ld(x) <= inter_x(st.back(), st[st.size() - 2]))
		st.pop_back();
	return st.back().a * x + st.back().b;
}

inline ll sq(ll x) { return x * x; }

vector<vector<ll>> prefix(vector<ll> v, int b) {
	int n = v.size();
	vector<vector<ll>> dp(n);
	for(int i = 0; i < n; i++)
		dp[i].resize(b + 1, 1e18);
	dp[0][0] = 0;
	for(int i = 0; i < n; i++) {
		dp[i][1] = sq(v[i] - v[0]);
		//printf("dp[%d][%d] = %lld\n", i, 1, dp[i][1]);
	}
	for(int k = 2; k <= b; k++) {
		for(int i = 0; i < n; i++) {
			add(lin{v[i], sq(v[i]) + dp[i][k - 1]});
			dp[i][k] = sq(v[i]) + query(0 - v[i] - v[i]);
			//printf("dp[%d][%d] = %lld\n", i, k, dp[i][k]);
		}
		st.clear();
	}
	return move(dp);
}

vector<vector<ll>> suffix(vector<ll> v, int b) {
	reverse(v.begin(), v.end());
	for(ll &x : v) x = 1.1e8 - x;
	vector<vector<ll>> dp = prefix(v, b);
	reverse(dp.begin(), dp.end());
	return move(dp);
}

ll a[N];
int n;

int get_mx(ll x) {
	int l = 0, r = n - 1;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(x >= a[m]) l = m;
		else r = m - 1;
	}
	return l;
}

int get_mn(ll x) {
	int l = 0, r = n - 1;
	while(l < r) {
		int m = (l + r) / 2;
		if(x <= a[m]) r = m;
		else l = m + 1;
	}
	return l;
}

#define debug(args...) ((void) 0)

int b, c;


int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &b, &c); c--;
		for(i = 0; i < n; i++) scanf("%lld", &a[i]);
		//for(i = 0; i < n; i++) printf("%lld\n", a[i]);
		if(n == 1) { puts("0"); continue; }
		vector<ll> A(a, a + n);
		vector<vector<ll>> dl = prefix(A, b);
		vector<vector<ll>> dr = suffix(A, b);
		if(c == 0) { printf("%lld\n", dr[0][b]); continue; }
		if(c == n - 1) { printf("%lld\n", dl[n - 1][b]); continue; }
		ll ans = LLONG_MAX;
		for(i = 0; i < c; i++)
			if(get_mx(a[c] + (a[c] - a[i])) > c) {
				//printf("%lld + %lld + %lld\n", sq(a[c] - a[i]), dl[i][b - 1], dr[get_mx(a[c] + (a[c] - a[i]))][b - 1]);
				ans = min(ans, sq(a[c] - a[i]) + dl[i][b - 1] + dr[get_mx(a[c] + (a[c] - a[i]))][b - 1]);
				//printf("[%d] ans %lld\n", i, ans);
			}
		for(i = c + 1; i < n; i++)
			if(get_mn(a[c] - (a[i] - a[c])) < c) {
				ans = min(ans, sq(a[i] - a[c]) + dl[get_mn(a[c] - (a[i] - a[c]))][b - 1] + dr[i][b - 1]);
				//printf("[%d] ans %lld\n", i, ans);
			}

		//printf("ans %lld\n", ans);

		vector<ll> lcv(a, a + c + 1);
		vector<vector<ll>> lc = suffix(lcv, b);

		for(i = 1; i < c; i++) {
			for(int L = 0; L < i; L++) {
				int d = a[i] - a[L];
				int R = get_mx(a[i] + d);
				if(R <= c) continue;
#define gol(j) (sq(d) + dl[L][b - j - 1] + lc[i][j] + dr[R][b - j - 1])
				for(j = 0; j <= b - 1; j++)
					ans = min(ans, gol(j));
			}
		}

		for(i = 1; i < c; i++)
			for(int R = c + 1; R < n; R++) {
				int d = a[R] - a[i];
				int L = get_mn(a[i] - d);
				if(L >= i) continue;
				for(j = 0; j <= b - 1; j++)
					ans = min(ans, gol(j));
			}

		vector<ll> rcv(a + c, a + n);
		vector<vector<ll>> rc = prefix(rcv, b);

		for(i = c + 1; i < n - 1; i++) {
			for(int R = i + 1; R < n; R++) {
				int d = a[R] - a[i];
				int L = get_mn(a[i] - d);
				if(L >= c) continue;
#define gor(j) (sq(d) + dr[R][b - j - 1] + rc[i - c][j] + dl[L][b - j - 1])
				for(j = 0; j <= b - 1; j++)
					ans = min(ans, gor(j));
			}
		}

		for(i = c + 1; i < n - 1; i++)
			for(int L = 0; L < c; L++) {
				int d = a[i] - a[L];
				int R = get_mx(a[i] + d);
				if(R <= i) continue;
				for(j = 0; j <= b - 1; j++)
					ans = min(ans, gor(j));
			}

		printf("%lld\n", ans);
	}
}
