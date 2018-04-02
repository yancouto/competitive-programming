#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 512;
ll A[N][N];
ll mn[N][N];

struct qmin {
	deque<ll> dq;
	inline void push(ll x) {
		while(!dq.empty() && dq.back() > x)
			dq.pop_back();
		dq.push_back(x);
	}
	inline void pop(ll x) {
		if(dq.front() == x)
			dq.pop_front();
	}
	inline ll mn() {
		return dq.front();
	}
};
int n, m;

inline ll conta(ll g, int a, int b) {
//	ll ans = ll(-1 + ll((g * ll(n * m) + ll(n * m - a * b - 1)) / ll(n * m - a * b))) * ll(a * b);
//	printf("conta(%lld, %d, %d) = %lld\n", g, a, b, ans);
	return ll(-1 + ll((g * ll(n * m) + ll(n * m - a * b - 1)) / ll(n * m - a * b))) * ll(a * b);
}

ll best;

int pr[N], nx[N];
int st[N], sn;

inline void go(int a, int b) {
	int i, j;
	for(j = 0; j < m; j++) {
		qmin q;
		for(i = 0; i < n; i++) {
			q.push(A[i][j]);
			if(i >= a) q.pop(A[i - a][j]);
			mn[i][j] = q.mn();
		}
	}
	for(i = a - 1; i < n; i++) {
		sn = 0;
		for(j = 0; j < m; j++) {
			while(sn && mn[i][st[sn - 1]] >= mn[i][j]) sn--;
			if(sn) pr[j] = st[sn - 1] + 1;
			else pr[j] = 0;
			st[sn++] = j;
		}
		sn = 0;
		for(j = m - 1; j >= 0; j--) {
			while(sn && mn[i][st[sn - 1]] >= mn[i][j]) sn--;
			if(sn) nx[j] = st[sn - 1] - 1;
			else nx[j] = m - 1;
			//printf("nx[%d] = %d\n", j, nx[j]);
			st[sn++] = j;
		}
		for(j = 0; j < m; j++) {
			//printf("a = %d i = %d j = %d inter [%d, %d]\n", a, i, j, pr[j], nx[j]);
			best = max(best, conta(mn[i][j], a, min(b, nx[j] - pr[j] + 1)));
		}
	}
}

int main() {
	int a, b;
	scanf("%d %d %d %d", &a, &b, &n, &m);
	if(a < b) swap(a, b);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf("%lld", &A[i][j]);
	for(int aa = 1; aa <= a && aa <= n; aa++) {
		if(aa <= b)
			go(aa, a);
		else
			go(aa, b);
	}
	printf("%lld\n", best);
}
