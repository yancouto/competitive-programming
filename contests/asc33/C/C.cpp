#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

const int N = 142;

struct vect {
	ll x, y;

	vect (ll a = 0, ll b = 0) : x(a), y(b) {}

	inline vect operator - (vect ot) 
	{ return vect(x-ot.x, y-ot.y); }
	inline vect operator + (vect ot)
	{ return vect(x+ot.x, y+ot.y); }

	inline ll operator ^ (vect ot)
	{ return x * ot.y - y * ot.x; }
	inline ll operator * (vect ot)
	{ return x * ot.x + y * ot.y; }

	inline ll ar (vect a, vect b)
	{ return ((a-(*this))^(b-(*this))); }
	inline int left (vect a, vect b) 
	{ ll o = ar(a,b); return -1 + (o <= 0) + (o < 0); }
};

ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

struct ctr {
	ll p, q;

	ctr (ll a = 0, ll b = 0) {
		if(!b) { q = 0; return; }
		if (a == 0)
			b = 1;
		if (b < 0) {
			a = -a;
			b = -b;
		}

		ll c = gcd(abs(a),abs(b));
		p = a/c; q = b/c;
	}

	bool operator < (const ctr & ot) const {
		if (q != ot.q)
			return q < ot.q;
		return p < ot.p;
	}
};

typedef pair<ctr,ctr> pp;

struct lin {
	vect s, t;

	lin (vect a, vect b) : s(a), t(b) {}

	inline ll a ()
	{ return t.y - s.y; }
	inline ll b ()
	{ return s.x - t.x; }
	inline ll c ()
	{ return a()*s.x + b()*s.y; }

	inline pp inter (lin o) {
		ll d = a() * o.b() - o.a() * b();
		pp tm(ctr(o.b() * c() - b() * o.c(), d), ctr(a() * o.c() - o.a() * c(), d));

		return tm;
	}
};

map<pp, int> s;
map<pp, int>::iterator it;
int qt[N*N*N];
int is[N*N*N];
int q;
pp rep[N*N*N];

void insere (pp x) {
	if (x.first.q == 0 || x.second.q == 0) return;

	it = s.find(x);
	int cur = 0;
	if (it == s.end()) {
		cur = q;
		rep[q] = x;
		s[x] = q++;
	} else {
		cur = it->second;
}

	qt[cur]++;
}

int n;
vect v[N];
int mat[N][N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("center.in", "r", stdin);
	freopen("center.out", "w", stdout);
#endif

	scanf("%d", &n);
	n += n;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
	}

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (i == k || j == k) continue;
				if (v[k].left(v[i], v[j]) == 0)
					mat[i][j] = 1;
			}
		}
	}

	int cnt = 0;
	int ls = 0;
	q = 0;
	for (int k = 1; k < n; k++) {
		if (mat[0][k]) continue;
		for (int i = 1; i < n; i++) {
			if (i == k) continue;
			for (int j = i+1; j < n; j++) {
				if (j == k) continue;
				if (mat[i][j]) continue;
				insere(lin(v[0],v[k]).inter(lin(v[i],v[j])));
			}
		}

		for (int k = 0; k < q; k++) {
			if (qt[k] == (n-2)/2) {
				double x = double(rep[k].first.p)/double(rep[k].first.q);
				double y = double(rep[k].second.p)/double(rep[k].second.q);
				is[k] = 1;
			}
			qt[k] = 0;
		}
	}
	
	for (int i = 0; i < q; i++) {
		if (is[i]) {
			cnt++;
			ls = i;
		}
	}

	if (cnt == 0)
		printf("Impossible\n");
	else if (cnt > 1)
		printf("Ambiguity\n");
	else {
		double x = double(rep[ls].first.p)/double(rep[ls].first.q);
		double y = double(rep[ls].second.p)/double(rep[ls].second.q);

		printf("Center of the universe found at (%.20f, %.20f)\n", x, y);
	}
}
