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
const int N = 2123;

int w, h;
pii v[N];

void proc(int i) {
	int x, y; char d;
	scanf("%d %d %c", &x, &y, &d);
	int &a = v[i].fst, &b = v[i].snd;
	if(d == 'W') {
		if(y < x) a = 2 * h + 2 * w - (x - y);
		else a = y - x;
		if(x < h - y) b = y + x;
		else b = h + x - (h - y);
	} else if(d == 'E') {
		if(h - y < w - x) a = h + x + (h - y);
		else a = w + h + (h - y - (w - x));
		if(w - x < y) b = w + 2 * h - y + (w - x);
		else b = w + 2 * h + (w - x) - y;
	} else if(d == 'S') {
		if(w - x < y) a = w + 2 * h - y + (w - x);
		else a = w + 2 * h + (w - x) - y;
		if(y < x) b = 2 * h + 2 * w - (x - y);
		else b = y - x;
	} else {
		if(x < h - y) a = y + x;
		else a = h + x - (h - y);
		if(h - y < w - x) b = h + x + (h - y);
		else b = w + h + (h - y - (w - x));
	}
}

inline int conv(int x, int b) {
	if(x >= b) return x - b;
	return 2*w + 2*h - b + x;
}

int n;
int solve(pii p[]) {
	int mx = INT_MIN, tot = 0;
	for(int i = 0; i < n; i++)
		if(p[i].fst > mx) mx = p[i].snd, tot++;
	return tot;
}

int main() {
	int i, j;
	while(scanf("%d %d %d", &n, &w, &h) != EOF) {
		for(i = 0; i < n; i++)
			proc(i);
		sort(v, v + n, [](pii a, pii b) { return a.snd < b.snd; });
		for(i = 0; i < n; i++)
			if(v[i].snd < v[i].fst)
				v[i].fst -= 2 * w + 2 * h;
		for(i = n; i < 2 * n; i++)
			v[i] = pii(v[i-n].fst + 2 * w + 2 * h, v[i-n].snd + 2 * w + 2 * h);
		int ans = INT_MAX;
		for(i = 0; i < n; i++)
			ans = min(ans, solve(v + i));
		printf("%d\n", ans);
	}
}
