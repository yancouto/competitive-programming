#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 9123456, mx = 1000000000;

int L[N], R[N], tr[N];
int en = 1, root = 0;
int a(int &i) {
	if(!i) i = en++;
	return i;
}

void add(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) return (void) (tr[i]++);
	int m = (l + r) / 2;
	add(a(L[i]), l, m, ql, qr);
	add(a(R[i]), m + 1, r, ql, qr);
}

int get(int i, int l, int r, int x, int val) {
	val += tr[i];
	if(l == r) return val;
	int m = (l + r) / 2;
	if(x <= m) return get(a(L[i]), l, m, x, val);
	else return get(a(R[i]), m + 1, r, x, val);
}


int main() {
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
	freopen("environment.in", "r", stdin);
	freopen("environment.out", "w", stdout);
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif
	int i, j, n, d = 0, t, l, r;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d %d", &l, &r); l += d; r += d;
			add(a(root), 0, mx, l, r);
		} else {
			scanf("%d", &l);
			printf("%d\n", d = get(a(root), 0, mx, l, 0));
		}
	}

}
