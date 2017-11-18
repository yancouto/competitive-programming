#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;
#define A first
#define B second
#define sa first
#define ct second

const int N = 112345;
int n;
pii tr[N << 2];
pii p[N];
int pp[N], ip[N];

void add(int i, int l, int r, int p, ll a) {
	tr[i].sa += a;
	tr[i].ct++;
	if(l == r) return;
	int m = (l + r) / 2;
	if(p <= m) add(2 * i, l, m, p, a);
	else add(2 * i + 1, m + 1, r, p, a);
}

int solve(int i, int l, int r, ll mn) {
	assert(tr[i].sa >= mn);
	if(mn == 0) return 0;
	if(l == r) return 1;
	int m = (l + r) / 2;
	if(tr[2 * i + 1].sa >= mn) return solve(2 * i + 1, m + 1, r, mn);
	return solve(2 * i, l, m, mn - tr[2 * i + 1].sa) + tr[2 * i + 1].ct;
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld", &p[i].A, &p[i].B), pp[i] = i;
		p[i].B += p[i].A;
	}
	sort(p, p + n, [](pii a, pii b) { return a.B < b.B; });
	sort(pp, pp + n, [](int i, int j) { return p[i] < p[j]; });
	for(i = 0; i < n; i++) ip[pp[i]] = i;
	ll sum = 0;
	int mn = INT_MAX;
	for(i = 0; i < n; i++) {
		sum += p[i].A;
		add(1, 0, n - 1, ip[i], p[i].A);
		if(sum < p[i].B) continue;
		mn = min(mn, solve(1, 0, n - 1, p[i].B));
	}
	if(mn == INT_MAX) mn = -1;
	printf("%d\n", mn);
}
