#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

inline void rd(int &x) {
	char c;
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

vector<int> cmp[212][5123];
int p[212][5123];
ll val[212][5123];

ll id[5123];

int d;

ll ans;

map<ll, int> ct;

void change(ll a, ll b) {
	ans -= --ct[a] * 2ll;
	ans += ct[b]++ * 2ll;
	if(ct[a] == 0) ct.erase(a);
}

inline void join(int k, int a, int b) {
	if((a = p[k][a]) == (b = p[k][b])) return;
	if(cmp[k][a].size() < cmp[k][b].size()) swap(a, b);
	for(int x : cmp[k][b]) {
		//printf("[%d] %d change to comp %d->%d\n", k, x, b, a);
		//printf("%lld -> %lld\n\n", id[x], id[x] ^ val[k][a] ^ val[k][b]);
		cmp[k][a].pb(x);
		change(id[x], id[x] ^ val[k][a] ^ val[k][b]);
		p[k][x] = a;
		id[x] = id[x] ^ val[k][a] ^ val[k][b];
	}
	cmp[k][b].clear();
}

ll rnd() {
	return (ll(rand()) << 20) ^ ll(rand()) ^ (ll(rand()) << 32);
}

int main() {
	srand(time(NULL));
	int i, j, n, m;
	rd(d); rd(n); rd(m);
	for(i = 1; i <= d; i++) {
		for(j = 0; j < n; j++) {
			p[i][j] = j;
			cmp[i][j].pb(j);
			val[i][j] = rnd();
			//printf("val[%d][%d] = %lld\n", i, j, val[i][j]);
			id[j] ^= val[i][j];
		}
	}
	for(i = 0; i < n; i++) {
		//printf("id[%d] = %lld\n", i, id[i]);
		assert(ct[id[i]] == 0);
		ct[id[i]]++;
	}
	ans = n;
	for(i = 0; i < m; i++) {
		int a, b, k;
		rd(a); rd(b); rd(k); a--; b--;
		join(k, a, b);
		printf("%lld\n", ans);
	}
}
