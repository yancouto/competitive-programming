#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#define temp template<typename num>
#define ptn point<num>
temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	num dist_sqr(ptn o) const { return ((*this - o) * (*this - o)); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x  && y < o.y); }
};
typedef point<ll> pti;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
temp double dist_seg_sqr(ptn a, ptn b, ptn c) {
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}
temp int sign(num x) { return (x > 0) - (x < 0); }
const int N = 112345;
pti a, b;

double func(pti p) {
	double d = sqrt(dist_seg_sqr(a, b, p));
	return d * sign(cross(a, b, p));
}

double func2(pti p) { return -func(p); }
pti p[N], st[N];

int bin(int l, int r, double (*f)(pti)) {
	//for(int i = l; i <= r; i++)
	//	printf("%d %.10f\n", i, f(p[i]));
	int L = l, R = r;
	while(l < r) {
		int m = (l + r) / 2;
		if(f(p[m]) < f(p[m+1])) l = m + 1;
		else r = m;
	}
	if(f(p[L]) < f(p[R])) swap(L, R);
	if(f(p[L]) > f(p[l])) l = L;
	//printf("best %.10f\n", f(p[l]));
	return l;
}


map<pii, int> mp;
int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	for(i = 0; i < n; i++)
		mp[pii(p[i].x, p[i].y)] = i + 1;
	sort(p, p + n);
	int sn = 0;
	for(i = 0; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], p[i]) > 0)
			sn--;
		st[sn++] = p[i];
	}
	int k = sn;
	for(i = n - 2; i >= 0; i--) {
		while(sn > k && cross(st[sn - 2], st[sn - 1], p[i]) > 0)
			sn--;
		st[sn++] = p[i];
	}
	sn--;
	for(i = 0; i < 2 * sn; i++)
		p[i] = st[i%sn];
	//for(i = 0; i < n; i++)
	//	printf("[%d] (%lld, %lld)\n", i, p[i].x, p[i].y);
	//printf("k = %d\n", k-1);
	for_tests(t, tt) {
		scanf("%lld %lld %lld %lld", &a.x, &a.y, &b.x, &b.y);
		if(n <= 1) { puts("0"); continue; }
		int a[4];
		a[0] = bin(0, k - 1, &func);
		a[1] = bin(0, k - 1, &func2);
		a[2] = bin(k - 1, sn, &func);
		a[3] = bin(k - 1, sn, &func2);
		//printf("val %.10f %.10f %.10f %.10f\n", func(p[amn]), func(p[amx]), func(p[bmn]), func(p[bmx]));
		int mx = 0;
		for(i = 1; i < 4; i++)
			if(func(p[a[i]]) > func(p[a[mx]]))
				mx = i;
		int mn = -1;
		for(i = 0; i < 4; i++)
			if(i != mx && (mn == -1 || func(p[a[i]]) < func(p[a[mn]])))
				mn = i;
		mx = a[mx]; mn = a[mn];
		if(sign(func(p[mx])) * sign(func(p[mn])) == -1) {
			printf("%d %d\n", mp[pii(p[mx].x, p[mx].y)], mp[pii(p[mn].x, p[mn].y)]);
		} else printf("0\n");
	}
}
