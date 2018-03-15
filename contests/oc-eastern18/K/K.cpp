#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;
const int K = 52;

int n, d, m;
ll v[N][3];
int qr[N][2];
ll rr[N];
ll dp[N][K];

inline void _max (ll & a, ll b) { a = max(a,b); }

void go (int l, int r, vector<int> & iq) {
	if (l == r) return;
	int md = (l+r)/2;

	for (int k = l; k <= r; k++) for (int s = 0; s < d; s++) dp[k][s] = -1;
	for (int i = md; i >= l; i--) {
		for (int k = 0; k < 3; k++) {
			if (i == md)
				_max(dp[i][v[i][k]%d], v[i][k]);
			else for (int s = 0; s < d; s++) if (dp[i+1][s] >= 0)
				_max(dp[i][(v[i][k]+s)%d], dp[i+1][s] + v[i][k]);
		}
	}
	for (int i = md+1; i <= r; i++) {
		for (int k = 0; k < 3; k++) {
			if (i == md+1)
				_max(dp[i][v[i][k]%d], v[i][k]);
			else for (int s = 0; s < d; s++) if (dp[i-1][s] >= 0)
				_max(dp[i][(v[i][k]+s)%d], dp[i-1][s] + v[i][k]);
		}
	}
	vector<int> il, ir;
	for (int i : iq) {
		if (qr[i][1] <= md) il.pb(i);
		else if (qr[i][0] > md) ir.pb(i);
		else {
			for (int s = 0; s < d; s++) {
				ll a = dp[qr[i][0]][s];
				ll b = dp[qr[i][1]][(d-s)%d];
				if (a != -1 && b != -1) _max(rr[i], a + b);
			}
		}
	}
	go(l,md,il);
	go(md+1,r,ir);
}

int main () {
	scanf("%d %d", &n, &d);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 3; k++)
			scanf("%lld", &v[i][k]);
	}
	scanf("%d", &m);

	vector<int> iq; iq.reserve(m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &qr[i][0], &qr[i][1]);
		qr[i][0]--; qr[i][1]--;
		rr[i] = -1;
		if (qr[i][0] == qr[i][1]) {
			int j = qr[i][0];
			for (int k = 0; k < 3; k++) if (v[j][k]%d == 0) rr[i] = max(rr[i], v[j][k]);
		} else {
			iq.pb(i);
		}
	}

	go(0,n-1,iq);
	for (int i = 0; i < m; i++) {
		printf("%lld\n", rr[i]);
	}
}
