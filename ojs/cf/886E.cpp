#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, k;

struct no {
	ll val, sum;
};

ll join(ll a, ll b, int szb) {

}

void set_(int i, int l, int r, int p, ll v) {
	if(l == r) return (void) (tr[i] = {v, v});
	int m = (l + r) / 2;
	if(p <= m) set_(2 * i, l, m, p, v);
	else set_(2 * i + 1, m + 1, r, p, v);
	tr[i] = join(tr[2 * i], tr[2 * i + 1], r - (m + 1) + 1);
}

int main() {
	int i, j;
	scanf("%d %d", &n, &k);

}
