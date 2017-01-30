#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

const int N = 1123;
pii a[N];
int qt[N], nois[N];
ll memo[2][N][N];
int cur, k;
ll solve(int i, int p, int x) {
	if(i == 2 * n) return p + x == n && p - x == k;
	if(i > cur) return memo[i & 1][p][x];
	ll &r = memo[i & 1][p][x]; r = 0;
	if(qt[i] - p - x < 0 || nois[i] - p - x < 0) return r = 0;
	if(a[i].snd) {
		r = mod(solve(i + 1, p + 1, x) * ll(qt[i] - p - x) + solve(i + 1, p, x));
	} else {
		r = mod(solve(i + 1, p, x + 1) * ll(nois[i] - p - x) + solve(i + 1, p, x));
	}
	return r;
}
#define left alskjdalsdj
void go(int i, int p, int x, vector<pii> ans, vector<int> wait, vector<int> left) {
	printf("recon(%d, %d, %d)\n", i, p, x);
	if(i == 2 * n && p - x == k && p + x == n) {
		for(pii p : ans) printf("%d-%d\n", p.fst, p.snd);
		puts("===================\n\n\n");
		return;
	}
	//printf("recon(%d, %d, %d)\n", i, p, x);
	if(memo[i][p][x] == 0) return;
	if(a[i].snd) {
		vector<int> w2 = wait; w2.pb(a[i].fst);
		go(i + 1, p, x, ans, w2, left);
		for(int X : left) {
			vector<int> l2;
			for(int y : left) if(X != y) l2.pb(y);
			vector<pii> a2 = ans;
			a2.pb(pii(a[i].fst, X));
			go(i + 1, p + 1, x, a2, wait, l2);
		}
	} else {
		vector<int> l2 = left; l2.pb(a[i].fst);
		go(i + 1, p, x, ans, wait, l2);
		for(int X : wait) {
			vector<int> w2;
			for(int y : wait) if(X != y) w2.pb(y);
			vector<pii> a2 = ans;
			a2.pb(pii(X, a[i].fst));
			go(i + 1, p, x + 1, a2, w2, left);
		}
	}
}

int main() {
	int i, j, p, x;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++) scanf("%d", &a[i].fst), a[i].snd = 1;
	for(i = 0; i < n; i++) scanf("%d", &a[i + n].fst), a[i + n].snd = 0;
	sort(a, a + 2 * n);
	for(i = 0; i < 2 * n; i++)
		nois[i] = (i? nois[i - 1] : 0) + a[i].snd,
		qt[i] = (i? qt[i - 1] : 0) + !a[i].snd;
	for(i = 2 * n - 1; i >= 0; i--)
		for(p = 0; p <= i / 2; p++)
			for(x = 0; x <= i / 2 - p; x++) {
				cur = i;
				solve(i, p, x);
				//if(memo[i & 1][p][x] > 0) printf("(%d, %d, %d) = %lld\n", i, p, x, memo[i & 1][p][x]);
			}
	printf("%lld\n", solve(0, 0, 0));
}
