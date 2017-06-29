#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

typedef ll cood;
const double pi = acos(-1.);
const cood = 0;

const int N = 2e5+7;

struct vec {
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }

	vec operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	vec operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b)
	{ cood o = ar(a,b); return (o < -eps) - (o > eps); }
};

int n, k, s;
vec v[N];
vec p[N];

int main () {
	cin >> n >> k;
	
	for (int i = 0; i < n; i++)
		cin >> v[i].x >> v[i].y;

	sort(v, v+k, [] (int i, int j) {
		if (v[i].x == v[j].x) return v[i].y < v[j].y;
		return v[i].x < v[j].x;
	});

	sort(v+1, v+k, [] (int i, int j) {
		return (v[j].sd(v[0], v[i]) == -1);
	
	});

	s = 2;
	for (int i = 2; i < k; i++) {
		while (s >= 2 && v[i].sd(v[s-2], v[s-1]) != -1)
			s--;
		swap(v[s], v[i]);
		s++;
	}

	for (int i = 0; i < s; i++)
		p[i+s] = p[i] = v[i];

	for (int i = k; i < n; i++) {

	}
}
