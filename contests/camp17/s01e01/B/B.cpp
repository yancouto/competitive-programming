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

int x;
set<int> s[2];
set<int>::iterator it;

int main () {
	int n, t;
	int d = 0;
	scanf("%d %d", &n, &t);

	for (int i = 0; i < n; i++) {
		int p;
		scanf("%d", &x);
		scanf("%d", &p);

		s[p].insert(x);
	}

	int r = 0;
	while (true) {
		if (d) {
			it = s[1].lower_bound(t);
			if (it == s[1].end()) break;
			d = 0;
			t = *it;
			s[1].erase(it);
		} else {
			it = s[0].lower_bound(t);
			if (it == s[0].begin()) {
				r++;
				d = 1;
				t = 0;
			} else {
				--it;
				d = 1;
				t = *it;
				s[0].erase(it);
			}
		}
	}

	if (!s[0].empty() || !s[1].empty())
		r = -1;
	printf("%d\n", r);
}
