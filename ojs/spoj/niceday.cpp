#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

struct pt {
	int x, y, z;
	bool operator < (pt o) const { return z > o.z; }
} a[100009];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
			a[i].x = n + 1 - a[i].x;
			a[i].y = n + 1 - a[i].y;
			a[i].z = n + 1 - a[i].z;
		}
		sort(a, a + n);
		set<pii> s;
		s.insert(pii(0, -200000));
		s.insert(pii(200000,  0));
		int tot = 0;
		for(i = 0; i < n; i++) {
			if(-s.lower_bound(pii(a[i].x, -a[i].y))->y >= a[i].y)
				continue;
			tot++;
			auto it = s.insert(pii(a[i].x, -a[i].y)).first;
			while(-prev(it)->y <= a[i].y)
				s.erase(prev(it));
		}
		printf("%d\n", tot);
	}
}
