#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<long double, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

string form[] = {
	"x^y^z",
	"x^z^y",
	"(x^y)^z",
	"(x^y)^z",
	"y^x^z",
	"y^z^x",
	"(y^x)^z",
	"(y^x)^z",
	"z^x^y",
	"z^y^x",
	"(z^x)^y",
	"(z^x)^y"
};


typedef long double ld;
ld lg(ld x) {
	if(abs(x) <= 1e-9) return ld(-1/0.);
	return log(x);
}
pii p[12];
inline ld& V(int i) { return p[i].fst; }
int main() {
	ld x, y, z; int i;
	double xx, yy, zz;
	scanf("%lf %lf %lf", &xx, &yy, &zz);
	x = xx; y = yy; z = zz;
	for(i = 0; i < 12; i++) p[i].snd = -i;
	V(0) = z*lg(y) + lg(lg(x));
	V(1) = y*lg(z) + lg(lg(x));
	V(2) = lg(z*y) + lg(lg(x));
	V(3) = lg(z*y) + lg(lg(x));
	V(4) = z*lg(x) + lg(lg(y));
	V(5) = x*lg(z) + lg(lg(y));
	V(6) = lg(z*x) + lg(lg(y));
	V(7) = lg(z*x) + lg(lg(y));
	V(8) = y*lg(x) + lg(lg(z));
	V(9) = x*lg(y) + lg(lg(z));
	V(10) = lg(y*x) + lg(lg(z));
	V(11) = lg(y*x) + lg(lg(z));
	sort(p, p + 12);
	reverse(p, p + 12);
	puts(form[-p[0].snd].c_str());
}
