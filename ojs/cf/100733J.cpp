#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 1009;

const int M = 2*1000009;
int n, m;
vector<int> ev[M];
int mx[M], mn[M];
struct qd {
	int x, w, mn, mx;
	qd() {}
	qd(int a, int b, int c, int d) : x(a), w(b), mn(c), mx(d) {}
} qs[MAX];
struct sp {
	int x, y;
	sp() {}
	sp(int a, int b) : x(a), y(b) {}
	bool operator < (sp o) const { return (x == o.x)? y < o.y : x < o.x; }
} ss[MAX];
int k;
int calc(int d) {
	int ct = 0;
	for(int i = 0; i < k; i++) {
		int a = lower_bound(ss, ss + n, sp(qs[i].x + d, INT_MIN)) - ss;
		int b = upper_bound(ss, ss + n, sp(qs[i].x + d + qs[i].w, INT_MAX)) - ss;
		for(; a < b; a++)
			if(ss[a].y >= qs[i].mn && ss[a].y <= qs[i].mx)
				ct++;
	}
	return ct;
}

int main() {
	int i, j, a, b, p;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &ss[i].y, &ss[i].x);
		ss[i].y++;
	}
	sort(ss, ss + n);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &p, &a, &b); p++;
		ev[a].pb(p); ev[b+1].pb(-p);
	}
	multiset<int> cur;
	for(i = 0; i < M; i++) {
		for(int p : ev[i])
			if(p > 0)
				cur.insert(p);
			else
				cur.erase(cur.find(-p));
		if(cur.size() <= 1) mx[i] = mn[i] = 0;
		else {
			mx[i] = *cur.rbegin();
			mn[i] = *cur.begin();
		}
	}
	k = 0;
	for(i = 0; i < M; ) {
		while(i < M && mx[i] == 0) i++;
		if(i == M) break;
		for(j = i + 1; j < M && mx[j] == mx[i] && mn[j] == mn[i]; j++);
		qs[k++] = qd(i, j - i - 1, mn[i], mx[i]);
		i = j;
	}
	for(i = 0; i < k; i++)
		qs[i].x -= qs[k-1].x + qs[k-1].w + 2;
	int d = 0; int val = 0;
	while(true) {
		val = max(val, calc(d));
		int jmp = INT_MAX;
		for(i = 0; i < k; i++) {
			int p = upper_bound(ss, ss + n, sp(qs[i].x + d + qs[i].w, INT_MAX)) - ss;
			if(p == n) continue;
			jmp = min(jmp, ss[p].x - (qs[i].x + d + qs[i].w));
		}
		if(jmp == INT_MAX) break;
		d += jmp;
	}
	printf("%d\n", val);
	return 0;
}
