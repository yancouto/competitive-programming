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
int nx[N][15];

int query(int l, int r) {
	int tot = 1;
	for(int i = 14; i >= 0; i--)
		if(nx[l][i] < r)
			tot += (1 << i),
			l = nx[l][i];
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
		int bs = 2 * n;
		for(j = 0; j < 15; j++) nx[2*n][j] = 2*n;
		set<pii> s; s.insert(pii(INT_MAX, -2*n));
		for(i = 2*n - 1; i >= 0; i--) {
			int bi = -s.upper_bound(pii(v[i].snd, INT_MAX))->snd;
			auto it = s.insert(pii(v[i].fst, -i)).fst;
			if(-next(it)->snd <= i) s.erase(it);
			else while(it != s.begin() && i <= -prev(it)->snd) s.erase(prev(it));
			nx[i][0] = bi;
			//printf("[%d, %d] -> [%d, %d]\n", v[i].fst, v[i].snd, v[bi].fst, v[bi].snd);
			for(j = 1; j < 15; j++)
				nx[i][j] = nx[nx[i][j - 1]][j - 1];
		}
		int ans = INT_MAX;
		for(i = 0; i < n; i++)
			ans = min(ans, query(i, i + n));
		printf("%d\n", ans);
	}
}
