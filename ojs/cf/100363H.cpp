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

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

typedef ll cood;
cood eps = 0;

const double pi = acos(-1.);

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// divide the plane relative to anc
	// 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
	bool halfplane (vec anc = vec(1,0)) {
		int l = sd(vec(), anc);
		if (l == 0)
			return (x < -eps);
		return (l == 1);
	}

	// ordering (ccw angle from anc, distance to origin)
	// is this < o?
	// PRECISION : ok with double if norm in [-1e4,1e3]
	bool compare (vec o, vec anc = vec(1,0)) {
		bool s[2] = {halfplane(anc), o.halfplane(anc)};
		if (s[0] != s[1])
			return s[0] < s[1];

		int l = sd(o, vec());
		if (l == 0)
			return sq() - o.sq() < -eps;
		return (l == -1);
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// tests TODO
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	// parallel to this through p
	lin parll (vec p) { return lin(a, b, a * p.x + b * p.y); }

	// line intersection
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (d < eps && -eps < d) throw 0; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
};

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

// tests TODO
// brd = do points on the border belong to convex?
// computes convex hull of given vector (inplace)
// returns size of convex hull
int graham (vec v[], int n, int brd) {
    for (int i = 1; i < n; i++) {
        if (v[i].x < v[0].x || (v[i].x == v[0].x && v[i].y < v[0].y))
            swap(v[0], v[i]);
    }

    sort(v+1, v+n, [v] (vec a, vec b) {
        int o = b.sd(v[0], a);
        if (o) return (o == -1);
        return v[0].sq(a) < v[0].sq(b);
    });

    if (brd) {
        int s = n-1;
        while (s > 1 && v[s].sd(v[s-1],v[0]) == 0)
            s--;
        for (int i = s; i < n - 1 - (i - s); i++)
            swap(v[i], v[n-1-(i-s)]);
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        while (s >= 2 && v[s-1].sd(v[s-2],v[i]) <= -brd)
            s--;
        v[s++] = v[i];
    }

    return s;
}

const int N = 4123;

vec v[N];

const int B = 1123456;
int bit[B];

void add(int i, int x) {
	for(i += 2; i < B; i += (i & -i))
		bit[i] += x;
}

int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

bool lex(int ia, int ib) {
	vec a = v[ia], b = v[ib];
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

#define left yyyy
#define right xxxx

ll right[N][N];
ll under[N][N];
int n;
int p[N];
double ang[N];

ll n3 = (n * (n - 1) * (n - 2)) / 6;

ll triangles() {
	int i;
	for(i = 0; i < n; i++) p[i] = i;
	iter_swap(p, min_element(p, p + n, lex));
	for(int i_ = 0; i_ < n; i_++) {
		i = p[i_];
		sort(p + i_ + 1, p + n, [i](int a, int b) { return (v[a] - v[i]).compare(v[b] - v[i], vec(0, -1)); });
		printf("At %d\n", i);
		for(int j_ = i_ + 1; j_ < n; j_++) {
			int j = p[j_];
			under[j][i] = under[i][j] = get(v[j].x) + 2;
			printf("will %d (==%lld)\n", j, under[i][j]);
			add(v[j].x, 1);
		}
		for(int j_ = i_ + 1; j_ < n; j_++)
			add(v[p[j_]].x, -1);
		iter_swap(p + i_ + 1, min_element(p + i_ + 1, p + n, lex));
	}
	ll tot = 0;
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			tot += (right[i][j] - n + 2 + right[i][j]) * under[i][j];
	tot -= n3;
	return tot;
}

const double E = 1e-9;

double ga(int j) {
	return ang[p[j]] + int(j / (n - 1)) * 2. * pi;
}

ll choose2(ll x) {
	return (x * (x - 1ll)) / 2ll;
}

int main() {
	int i, j;
	scanf("%d", &n);
	n3 = (n * (n - 1) * (n - 2)) / 6;
	for(i = 0; i < n; i++) scanf("%lld %lld", &v[i].x, &v[i].y);
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) p[j] = j, ang[j] = atan2(v[j].y - v[i].y, v[j].x - v[i].x);
		swap(p[i], p[n - 1]);
		sort(p, p + n - 1, [](int i, int j) { return ang[i] < ang[j]; });
		for(int j = n - 1; j < 2 * (n - 1); j++) p[j] = p[j - (n - 1)];
		//for(int j = 0; j < 2 * (n - 1); j++) printf("%d[%d]: %.2f\n", j, p[j], ga(j));
		int k_ = 0;
		for(int j_ = 0; j_ < n - 1; j_++) {
			j = p[j_];
			k_ = max(k_, j_);
			while(k_ + 1 < 2* (n - 1) && ga(k_ + 1) - ga(j_) <= pi + E) k_++;
			right[j][i] = right[i][j] = n - 2 - (k_ - j_);
			//printf("%d(%d) -- %d(%d)\n", j_, j, k_, p[k_]);
			//printf("right[%d][%d] = %lld\n", i, j, right[i][j]);
		}
	}
	ll tot = -3ll * n3;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			tot += choose2(right[i][j]) + choose2(n - 2 - right[i][j]);
	printf("tot %lld - triangles()=%lld\n", tot, triangles());
	printf("%.20f\n", double((tot - triangles()) / 2) / n3);
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			printf("under[%d][%d] = %lld\nright[%d][%d] = %lld\n\n", i, j, under[i][j], i, j, right[i][j]);
}
