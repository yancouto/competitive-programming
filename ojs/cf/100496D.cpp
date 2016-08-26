#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;

int a[N], b[N], ls[N], I[N], P[N], p[N], ans[N];

int bit[N];
int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int main() {
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	int i, n, m;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	for(i = 0; i < n; i++)
		a[i] = lower_bound(b, b + bn, a[i]) - b;
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &I[i], &P[i]);
		p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return I[i] > I[j]; });
	int r = n;
	for(i = 0; i < m; i++) {
		int qi = I[p[i]], qp = P[p[i]];
		qi--;
		while(r > qi) {
			r--;
			if(ls[a[r]]) add(ls[a[r]], -1);
			add(r, 1);
			ls[a[r]] = r;
		}
		ans[p[i]] = get(ls[a[qi + qp - 1]]);
	}
	for(i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}
