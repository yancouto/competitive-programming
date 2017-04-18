#include <bits/stdc++.h>
#define n1 first
#define n2 second

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

const int N = 1123456;
ll fat[N], invf[N];
int x[N], y[N], n;
map<pii, pii> mp;
ll ans[N];

inline ll comb(int n, int p) {
	return mod(fat[n] * mod(invf[p] * invf[n - p]));
}

int main () {
	int i, j, k;
	fat[0] = 1;
	for(i = 1; i < N; i++)
		fat[i] = mod(fat[i - 1] * ll(i));
	invf[N - 1] = fexp(fat[N - 1], modn - 2);
	for(i = N - 2; i >= 0; i--)
		invf[i] = mod(invf[i + 1] * ll(i + 1));
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	for(i = 0; i < n; i++)
		mp[pii(x[i] * 2, y[i] * 2)].n1++;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			mp[pii(x[i] + x[j], y[i] + y[j])].n2++;
	for(auto &e : mp) {
		pii p = e.second;
		if(p.n1) {
			for(k = 1; k <= n; k++)
				for(i = 0; i <= p.n1 && i <= k; i++)
					if(((k - i) & 1) == 0 && (k - i) / 2 <= p.n2)
						ans[k] = mod(ans[k] + mod(comb(p.n1, i) * comb(p.n2, (k - i) / 2)));
		} else
			for(i = 1; i <= p.n2; i++)
				ans[i * 2] = mod(ans[i * 2] + comb(p.n2, i));
	}
	for(i = 1; i <= n; i++)
		printf("%d%c", (int) mod(ans[i]), " \n"[i == n]);
}
