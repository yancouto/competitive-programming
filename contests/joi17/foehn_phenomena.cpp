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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n, q;

const int N = 212345;
ll bit[N];

void add(int i, ll x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

ll get(int i) {
	ll x = 0;
	for(i += 2; i; i -= (i & -i))
		x += bit[i];
	return x;
}

ll s, t; ll x;
ll val[N], cur;
void mk_val(int i) {
	ll a = get(i), b = get(i + 1);
	if(a < b) val[i] = -(b - a) * s;
	else val[i] =  (a - b) * t;
	cur += val[i];
}

int main() {
	int i;
	rd(n); rd(q); rd(s); rd(t);
	for(i = 0; i <= n; i++) {
		rd(x);
		add(i, x);
		add(i + 1, -x);
	}
	for(i = 0; i < n; i++) mk_val(i);
	for(i = 0; i < q; i++) {
		int l, r;
		rd(l); rd(r); rd(x);
		add(l, x);
		add(r + 1, -x);
		cur -= val[l - 1];
		mk_val(l - 1);
		if(r < n) {
			cur -= val[r];
			mk_val(r);
		}
		printf("%lld\n", cur);
	}
	
}
