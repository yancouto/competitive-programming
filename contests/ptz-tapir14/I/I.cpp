#include <bits/stdc++.h>
#define cout if (0)

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood;
cood eps = 0;

inline ll sq (ll x)
{ return x*x; }
inline double sq (double x)
{ return x*x; }

struct vec {
	cood x, y;
	int i;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator << (ostream&os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	cood operator * (vec o)
	{ return x*o.x + y*o.y; }
	cood operator ^ (vec o)
	{ return x*o.y - y*o.x; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	bool operator < (const vec & o) const {
		if (x != o.x)
			return x < o.x;
		return y < o.y;
	}
};

struct rty {
	vec a, b;
	ll res;

	rty () {
		res = LLONG_MAX;
	}
	rty (vec _a, vec _b) {
		a = _a;
		b = _b;
		res = a.sq(b);
	}

	bool operator < (const rty & o) const {
		return res < o.res;
	}
};

const int N = 2e6+7;

int n;
vec v[N];
vec w[N];

rty go (int l, int r) {
	rty rs;
	if (l == r) {
		return rs;
	}
	int m = (l + r+1)/2;
	vec piv = v[m];
	rs = min(rs, go(l, m-1));
	rs = min(rs, go(m, r));

	vector<vec> lf, rg;
	for (int i = l; i < m; i++) {
		if (abs(v[i].x - piv.x) <= rs.res)
			lf.pb(v[i]);
	}
	for (int i = m; i <= r; i++) {
		if (abs(v[i].x - piv.x) <= rs.res)
			rg.pb(v[i]);
	}

	int b = 0;
	for (int i = 0; i < lf.size(); i++) {
		while (b < rg.size() && rg[b].y < lf[i].y)
			b++;
		
		for (int j = max(0, b-10); j <= b+10 && j < rg.size(); j++) {
			rs = min(rs, rty(lf[i],rg[j]));
		}
	}

	int s = 0;
	int a = l;
	b = m;
	while (a < m || b <= r) {
		if (b > r || (!(a == m) && v[a].y < v[b].y)) {
			w[s++] = v[a++];
		} else {
			w[s++] = v[b++];
		}
	}
	for (int i = l; i <= r; i++) {
		v[i] = w[i-l];
	}
	return rs;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("illegal.in", "r", stdin);
	freopen("illegal.out", "w", stdout);
#endif
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
		v[i].i = i;
	}

	sort(v, v+n);
	rty res = go(0, n-1);
	printf("%d %d\n", res.a.i+1, res.b.i+1);
}
