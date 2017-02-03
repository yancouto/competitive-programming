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
#define deb fprintf(stderr, ":%d\n", __LINE__)

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

const int N = 3e3+7;
const double eps = 1e-9;

template<typename cood> struct tvect {
	cood x, y;

	tvect<cood> () : x(0), y(0) {}
	tvect<cood> (cood a, cood b) : x(a), y(b) {}
		
	inline tvect operator - (tvect<cood> ot) const
	{ return tvect(x-ot.x,y-ot.y); }
	inline cood operator ^ (tvect<cood> ot) const
	{ return x * ot.y - y * ot.x; }
	inline cood operator * (tvect<cood> ot) const
	{ return x * ot.x + y * ot.y; }
	inline cood ar (tvect<cood> a, tvect<cood> b) const 
	{ return (a-(*this))^(b-(*this)); }
	inline int left (tvect<cood> a, tvect<cood> b, cood eps = 0) const
	{ cood o = ar(a,b); return (o > eps) - (o < -eps); }
};

typedef tvect<ll> vect;
typedef tvect<double> dvect;

struct gate {
	int a, b;
	ll t;

	bool operator < (const gate & ot) const {
		if (t != ot.t) return t < ot.t;
		if (a != ot.a) return a < ot.a;
		return b < ot.b;
	}
};

struct evt {
	vect ps;
	int idx;
	int ty;

	evt (vect a, int b, int c) : ps(a), idx(b), ty(c) {}

	bool operator < (const evt & ot) const {
		if (ps.y != ot.ps.y) return ps.y < ot.ps.y;
		return idx < ot.idx;
	}
};

int n, o;
ll w;
gate v[N];
double res[N][2];
int to[N][2][2];

bool isfree (evt e, set<evt> & s) {
	if (s.size() && s.begin()->ps.y < e.ps.y)
		return 0;
	return 1;
}

bool cango (vect a, vect b) {
	ll ds = abs(a.x - b.x);
	ll dt = b.y - a.y;
	assert(dt > 0);

	if (ds <= w * dt)
		return 1;
	return 0;
}

bool between_seg (dvect a, dvect b, dvect c) {
	return (a.left(b,c,eps) == 0) && ((b-c) * (a-c) <= eps);
}
bool inter (dvect a, dvect b, dvect c, dvect d) {
//	if (between_seg(a,b,c) || between_seg(a,b,d) || between_seg(c,d,a) || between_seg(c,d,b)) return 1;
	if ((a.left(b,c,eps) * a.left(b,d,eps) == -1) && (c.left(d,a,eps) * c.left(d,b,eps) == -1)) return 1;
	return 0;
}

double tim (vect a, vect b) {
	return double(abs(a.x - b.x))/double(w);
}

bool rem (evt e, set<evt> & s) {
	evt f(e.ps, e.idx, !e.ty);
	if (f.ty)
		f.ps.x = v[f.idx].a;
	else
		f.ps.x = v[f.idx].b;

	if (s.find(f) != s.end()) {
		s.erase(f);
		return 1;
	}
	return 0;
}

void add (evt e, set<evt> & s) {
	s.insert(e);
}

vect getref (int i, int k) {
	vect aux(v[i].a, v[i].t);
	if (!k)
		aux.x = v[i].b;
	return aux;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld %d %d", &w, &o, &n);
	n++;

	v[0].a = v[0].b = v[0].t = 0;
	for (int i = 1; i < n; i++)
		scanf("%d %d %d", &v[i].a, &v[i].b, &v[i].t);
	sort(v, v+n);

	res[n][0] = res[n][1] = 0.;
	for (int i = n-1; i >= 0; i--) {
		for (int k = 0; k < 2; k++) {
			//deb;
			res[i][k] = 1./0.;
			to[i][k][0] = -1;
			vector<evt> ad;
			set<evt> st;
			vect ref;
			ref.y = v[i].t;

			if (k)
				ref.x = v[i].a;
			else
				ref.x = v[i].b;
			
			double objt = double(abs(ref.x - o))/double(w);
			//printf("at %d side %d\n", i, k);
			//printf("(%lld, %lld) -> (%lld, %.5f)\n", ref.x, ref.y, o, ref.y + objt);

			bool ok = 1;
			for (int j = i+1; j < n; j++) {
				if (v[i].t == v[j].t) continue;
				ad.push_back(evt(vect(v[j].a,v[j].t),j,1));
				ad.push_back(evt(vect(v[j].b,v[j].t),j,0));

				if (inter(dvect(ref.x,ref.y), dvect(o, ref.y + objt), dvect(v[j].a,v[j].t), dvect(v[j].b,v[j].t)))
					ok = 0;
			}
			//printf("ok %d\n", ok);

			if (ok) {
				res[i][k] = min(res[i][k], objt);
				to[i][k][0] = n;
				to[i][k][1] = 0;
			}

			sort(ad.begin(), ad.end(), [ref] (evt s, evt t) {
				return (ref.left(s.ps,t.ps) == -1);
			});
			
			for (int ii = 0; ii < ad.size();) {
				//deb;
				int l = 0;
				while (ii+l < ad.size() && ref.left(ad[ii].ps,ad[ii+l].ps) == 0) l++;

				vector<evt> toad;

				for (int j = ii; j < ii+l; j++)
					if (!rem(ad[j], st))
						toad.push_back(ad[j]);

				for (int j = ii; j < ii+l; j++) {
					if (isfree(ad[j],st) && cango(ref,ad[j].ps)) {
						//res[i][k] = min(res[i][k], res[ad[j].idx][ad[j].ty] + tim(ref,ad[j].ps));
						double loc = res[ad[j].idx][ad[j].ty] + tim(ref,ad[j].ps);
						if (loc < res[i][k]) {
							res[i][k] = loc;
							to[i][k][0] = ad[j].idx;
							to[i][k][1] = ad[j].ty;
						}
					}
				}

				for (evt e : toad)
					add(e, st);

				ii += l;
			}
		}
	}

	int i = 0;
	int k = 0;

	if (to[0][0][0] == -1) {
		printf("-1\n");
		return 0;
	}

	vector<pair<double,double> > rr;
	while (i != n) {
		int j = to[i][k][0];
		int x = to[i][k][1];

		vect a = getref(i,k);
		double dx, dt;
		if (j == n) {
			dx = o - a.x;
			dt = res[i][k];
		} else {
			vect b = getref(j,x);
			dx = b.x - a.x;
			dt = abs(b.y - a.y);
		}

		if (dt > eps)
			rr.push_back(pair<double, double>(dx/dt, dt));
		i = j;
		k = x;
	}

	printf("%d\n", int(rr.size()));
	for (int i = 0; i < rr.size(); i++)
		printf("%.20f %.20f\n", rr[i].first, rr[i].second);
}
