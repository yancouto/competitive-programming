#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 512;
int A[N][N];
int mn[10][N][N];

struct qmin {
	deque<int> dq;
	inline void push(int x) {
		while(!dq.empty() && dq.back() > x)
			dq.pop_back();
		dq.push_back(x);
	}
	inline void pop(int x) {
		if(dq.front() == x)
			dq.pop_front();
	}
	inline int mn() {
		return dq.front();
	}
};
int n, m;

inline int get_mn(int i, int j, int a, int b) {
	int e = 31 - __builtin_clz(b);
	return min(mn[e][i + a - 1][j + b - 1], mn[e][i + a - 1][j + (1 << e) - 1]);
}

inline ll conta(int i, int j, int a, int b) {
	ll g = get_mn(i, j, a, b);
	return ll(-1 + ll((g * ll(n * m) + ll(n * m - a * b - 1)) / ll(n * m - a * b))) * ll(a * b);
}

ll best;

inline void go(int a, int b) {
	int i, j;
	for(j = 0; j < m; j++) {
		qmin q;
		for(i = 0; i < n; i++) {
			q.push(A[i][j]);
			if(i >= a) q.pop(A[i - a][j]);
			mn[0][i][j] = q.mn();
			for(int k = 1; k < 10; k++)
				if(j - (1 << k) >= 0)
					mn[k][i][j] = min(mn[k - 1][i][j], mn[k - 1][i][j - (1 << (k - 1))]);
		}
	}
	for(i = 0; i < n - a + 1; i++)
		for(j = 0; j < m - a + 1; j++) {
			int l = j, r = min(m - 1, j + b - 1);
			while(l < r) {
				int mj = (l + r) / 2;
				if(conta(i, j, a, mj - j + 1) < conta(i, j, a, mj - j + 2))
					l = mj + 1;
				else
					r = mj;
			}
			best = max(best, conta(i, j, a, l - j + 1));
		}
}

int main() {
	int a, b;
	scanf("%d %d %d %d", &a, &b, &n, &m);
	if(a < b) swap(a, b);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf("%d", &A[i][j]);
	for(int aa = 1; aa <= a && aa <= n; aa++) {
		if(aa <= b)
			go(aa, a);
		else
			go(aa, b);
	}
	printf("%lld\n", best);
}
