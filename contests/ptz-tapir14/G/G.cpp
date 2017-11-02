#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back

const int T = 315;

const int N = 212345;
int mrk[N];
vector<int> A[N], B[N];

inline void rd(int &x) {
	char c;
	while(isspace(c = getchar()));
	x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("guests.in", "r", stdin);
	freopen("guests.out", "w", stdout);
#endif
	int i, n, m, k, j;
	rd(n); rd(m); rd(k);
	for(i = 0; i < k; i++) {
		int a, b;
		rd(a); rd(b); a--; b--;
		A[a].pb(b);
		B[b].pb(a);
	}
	memset(mrk, -1, sizeof mrk);
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(int(A[i].size()) < T) continue;
		for(int x : A[i]) mrk[x] = i;
		for(j = 0; j < n; j++) {
			if(A[j].size() > A[i].size() || (A[i].size() == A[j].size() && j >= i)) continue;
			int ct = 0;
			for(int x : A[j])
				ct += (mrk[x] == i);
			tot += (ll(ct) * ll(ct - 1)) / 2ll;
		}
	}
	map<ll, int> mp;
	for(i = 0; i < n; i++) {
		if(int(A[i].size()) >= T) continue;
		for(int x : A[i])
			for(int y : A[i]) {
				if(x >= y) continue;
				tot += mp[ll(x) * 100001ll + ll(y)]++;
			}
	}
	printf("%lld\n", tot);
}
