#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define fst first
#define snd second

template<class T> inline void rd(T &x) {
	char c;
	while(isspace(c = getchar()));
	if(!isdigit(c)) {
		x = -1;
		return;
	}
	x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + (c - '0');
}
ll p;
inline ll mod(ll x) { return x % p; }

inline ll fexp(ll x, ll e) {
	ll r = 1;
	for(; e; e >>= 1) {
		if(e & 1) r = mod(r * x);
		x = mod(x * x);
	}
	return r;
}
inline ll inv(ll x) { return fexp(x, p - 2); }

const int N = 123;
ll A[N][N];

ll a[N][N];
int n;
ll det() {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			a[i][j] = A[i][j];
	ll ans = 1;
	for(int i = 0; i < n; i++) {
		int mx = i;
		if(a[i][i] == 0)
			for(int j = i + 1; j < n; j++)
				if(a[j][i] != 0) {
					mx = j;
					break;
				}
		if(mx != i) swap_ranges(a[i], a[i] + n, a[mx]), ans = mod(p - ans);
		if(a[i][i] == 0) return 0;
		ll aii = inv(a[i][i]);
		for(int j = i + 1; j < n; j++) {
			ll ajiaii = mod(a[j][i] * aii);
			for(int k = i + 1; k < n; k++)
				a[j][k] = mod(a[j][k] - mod(ajiaii * a[i][k]) + p);
			a[j][i] = 0;
		}
		ans = mod(ans * a[i][i]);
	}
	return ans;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("finals.in", "r", stdin);
	freopen("finals.out", "w", stdout);
#endif
	srand(time(NULL));
	int i, j; ll c;
	rd(n); rd(p); rd(c);
	vector<pii> mt;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			rd(A[i][j]);
			if(A[i][j] == -1) mt.push_back(pii(i, j));
		}
	while(clock() <= .8 * CLOCKS_PER_SEC) {
		vector<int> rp;
		for(pii p : mt)
			rp.push_back(A[p.fst][p.snd] = (rand() % ::p));
		ll d = det();
		for(int k = 0; k < int(rp.size()); k++) {
			ll &v = A[mt[k].fst][mt[k].snd];
			v = (v + 1) % p;
			ll d2 = det();
			v = (v + p - 1) % p;
			if(d != d2) {
				puts("Yes");
				ll x = mod(((c - d) + p) * inv(mod(d2 - d + p)));
				v = (v + x) % p;
				for(i = 0; i < n; i++)
					for(j = 0; j < n; j++)
						printf("%lld%c", A[i][j], " \n"[j == n - 1]);
				return 0;
			}
		}
	}
	puts("No");
}
