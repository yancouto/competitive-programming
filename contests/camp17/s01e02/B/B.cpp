#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

template<typename cood> struct vect {
	cood x, y;

	vect<cood> () {}
	vect<cood> (cood a, cood b) : x(a), y(b) {}
	vect<cood> (cood a) : x(a), y(a) {}

	inline vect<cood> operator - (const vect<cood> & ot) const
	{ return vect<cood>(x - ot.x, y - ot.y); }
	inline vect<cood> operator + (const vect<cood> & ot) const
	{ return vect<cood>(x + ot.x, y + ot.y); }
	inline vect<cood> operator * (cood a) const
	{ return vect<cood>(x*a, y*a); }

	inline cood operator * (const vect<cood> & ot) const
	{ return x * ot.x + y * ot.y; }
	inline cood operator ^ (const vect<cood> & ot) const
	{ return y * ot.x - x * ot.y; }

	inline cood area (const vect<cood> & a, const vect<cood> & b) const
	{ return (a-(*this))^(b-(*this)); }
	int clockwise (const vect<cood> & a, const vect<cood> & b) const
	{ cood o = area(a,b); return (o > 0) - (o < 0); }

	bool halfplane () const {
		if (y != 0)
			return y < 0;
		return x > 0;
	}

	bool compare (const vect<cood> & ia, const vect<cood> & ib) const {
		vect<cood> a = (ia - (*this));
		vect<cood> b = (ib - (*this));

		int s[2] = {a.halfplane(), b.halfplane()};
		if (s[0] != s[1]) return s[0] < s[1];
		return (clockwise(ia,ib) == 1);
	}
};

const int N = 1e5 + 7;
int n;
vect<ll> v[N];
int uf[N], wf[N];

int find (int i) {
	if (i == uf[i]) return i;
	return uf[i] = find(uf[i]);
}

void join (int i, int j) {
	if ((i = find(i)) == (j = find(j))) return;
	if (wf[i] < wf[j]) swap(i,j);
	wf[i] += wf[j];
	uf[j] = i;
}

int main () {
	scanf("%d", &n);
	n--;
	for (int i = 0; i <= n; i++) {
		uf[i] = i;
		wf[i] = 1;
		scanf("%d %d", &v[i].x, &v[i].y);
	}

	sort(v+1, v+n+1, [] (const vect<ll> & a, const vect<ll> & b) {
		return v[0].compare(a,b);
	});
	
	for (int i = 1; i <= n; i++) {
		if (v[0].clockwise(v[i], v[(i)%n + 1]) == 0) {
			join(i, (i)%n + 1);
		}
	}

	int t[2] = {1,1};
	for (int i = 1; i <= n; i++) {
		if (v[i].y > v[0].y) {
			t[0]++; t[1]++;
		} else if (v[i].y == v[0].y) {
			t[1]++;
		}
	}
	
	int s[2] = {1,1};
	for (int i = 1; i <= n; i++) {
		if (v[i].x > v[0].x) {
			s[0]++; s[1]++;
		} else if (v[i].x == v[0].x) {
			s[1]++;
		}
	}
	int r[2];
	r[0] = min(t[0], s[0]);
	r[1] = max(t[1], s[1]);

	int j = 1;
	for (int i = 1; i <= n; i++) {
		if (i < n && v[0].clockwise(v[i], v[i+1]) == 0) continue;
		if (!((v[i]-v[0]).x <= 0 && (v[i]-v[0]).y >= 0)) break;

		j = max(i+1,j);
		while (j <= n && (v[0].clockwise(v[i], v[j]) > 0)) j++;

		r[0] = min(r[0], j-i-1);
		r[1] = max(r[1], j-i-1 + wf[find(i)]);
	}

	printf("%d %d\n", r[0], r[1]);
}

