#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1123456;

#define a first
#define b second
#define c first
#define d second
pii A[N], B[N];

ll ans[N];
void solve(int al, int ar, int bl, int br) {
	if(al > ar) return;
	int am = (al + ar) / 2;
	ans[am] = -1; int ai = -1;
	for(int i = bl; i <= br; i++) {
		if(B[i].c <= A[am].a && B[i].d <= A[am].b && (A[am].a - B[i].c) * (A[am].b - B[i].d) >= ans[am]) {
			ans[am] = (A[am].a - B[i].c) * (A[am].b - B[i].d);
			ai = i;
		}
	}
	assert(ai != -1);
	solve(al, am - 1, bl, ai);
	solve(am + 1, ar, ai, br);
}

int main() {
	int n, m, i;
	scanf("%d %d", &m, &n);
	for(i = 0; i < m; i++)
		scanf("%lld %lld", &B[i].c, &B[i].d);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &A[i].a, &A[i].b);
	sort(B, B + m);
	int bn = 0;
	for(i = 0; i < m; i++) {
		if(bn && B[i].d >= B[bn - 1].d)
			continue;
		B[bn++] = B[i];
	}
	sort(A, A + n);
	int an = 0;
	for(i = 0; i < n; i++) {
		while(an && A[i].b >= A[an - 1].b)
			an--;
		int j = (upper_bound(B, B + bn, pii(A[i].a, LLONG_MAX)) - B) - 1;
		if(j != -1 && B[j].d <= A[i].b)
			A[an++] = A[i];
	}

	solve(0, an - 1, 0, bn - 1);
	printf("%lld\n", max(0ll,  *max_element(ans, ans + an)));
}
