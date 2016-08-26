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

int d;
set<int> ap[100009];
int a[100009];
struct cmp {
	bool operator() (int i, int j) const { return *ap[i].upper_bound(d) > *ap[j].upper_bound(d); }
};

int main() {
	int c, n, m, i, x;
	while(scanf("%d %d %d", &c, &n, &m) != EOF) {
		int tot = 0, sure = -1;
		for(i = 0; i < n; i++) ap[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d", &a[i]);
			ap[a[i]].insert(i);
		}
		for(i = 0; i < n; i++) ap[i].insert(i + m);
		se<int, cmp> cur; d = -1;
		for(i = 0; i < m; i++) {
			if(cur.count(a[i])) cur.erase(a[i]), tot--;
			d++;
			if(cur.size() < c) { cur.insert(a[i]); tot++; continue; }
			cur.erase(cur.begin());
			cur.insert(a[i]);
			tot++;
		}
		printf("%d\n", tot);
	}
}
