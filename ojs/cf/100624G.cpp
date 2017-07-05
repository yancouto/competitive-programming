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

const int N = 212345;
int bit[N];
void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

struct node {
	int x, y, c;
} p[N];
set<int> s[N];

int v[N];

int main() {
	int i, n, k;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].c), v[i] = p[i].x, p[i].c--;
		sort(p, p + n, [](node i, node j) { return i.y < j.y; });
		sort(v, v + n);
		int vn = unique(v, v + n) - v;
		for(i = 0; i < vn + 10; i++) bit[i] = 0;
		for(i = 0; i < n; i++) p[i].x = lower_bound(v, v + vn, p[i].x) - v;
		for(i = 0; i < k; i++) {
			s[i].clear();
			s[i].insert(-1);
			s[i].insert(vn);
		}
		int mx = 0;
		for(i = 0; i < n;) {
			int j = i;
			for(; i < n && p[i].y == p[j].y; i++) {
				if(s[p[i].c].count(p[i].x)) continue;
				auto it = s[p[i].c].lower_bound(p[i].x);
				int nx = *it, pr = *prev(it);
				if(nx > pr + 1)
					mx = max(mx, get(nx - 1) - get(pr));
			}
			for(i = j; i < n && p[i].y == p[j].y; i++)
				s[p[i].c].insert(p[i].x),
				add(p[i].x, 1);
		}
		for(i = 0; i < k; i++) {
			auto it = s[i].begin();
			while(next(it) != s[i].end()) {
				auto nx = next(it);
				mx = max(mx, get(*nx - 1) - get(*it));
				it = nx;
			}
		}
		printf("%d\n", mx);
	}
}
