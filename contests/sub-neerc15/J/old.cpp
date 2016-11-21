#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, int> pt;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

inline void read(int &x) {
	scanf("%d", &x);
}

int n;

pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii operator - (pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }

ll sqr(ll x) { return x * x; }
const int N = 11234;
int t[N]; pt w[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("joy.in", "r", stdin);
	freopen("joy.out", "w", stdout);
#endif
	int i, j, k, vm;
	pt s, f;
	read(s.x); read(s.y);
	read(f.x); read(f.y);
	read(n); read(k); read(vm);
	for(i = 0; i < n; i++) {
		read(t[i]); read(w[i].x); read(w[i].y);
	}
	j = 0;
	pt pos = s;
	for(i = 0; i < k; i++) {
		while(j < n && t[j + 1] <= i) j++;
		pos = pos + w[j];
	}
	pt dif = f - pos;
	if(sqr(dif.x) + sqr(dif.y) <= sqr(vm) * sqr(k)) {
		double x = s.x, y = s.y;
		double dx = (double(dif.x) / double(k));
		double dy = (double(dif.y) / double(k));
		assert(sqrt(dx * dx + dy * dy) <= vm + 1e-5);
		j = 0;
		puts("Yes");
		for(i = 0; i < k; i++) {
			while(j < n && t[j + 1] <= i) j++;
			x += w[j].x + dx;
			y += w[j].y + dy;
			printf("%.10f %.10f\n", x, y);
		}

	} else puts("No");
}
