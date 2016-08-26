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

map<string, string> mp;

bool bad(const string &a, const string &b) {
	if(a.size() != b.size()) return true;
	int d = 0;
	for(int i = 0; i < a.size(); i++)
		if(a[i] != b[i])
			d++;
	return d > 1;
}

char s1[100], s2[100];

int main() {
	int i, n, m;
	while(true) {
		mp.clear();
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%s %s", s1, s2);
			mp[s1] = s2;
		}
		scanf("%d", &m); int tot = 0;
		for(i = 0; i < m; i++) {
			scanf("%s %s", s1, s2);
			if(bad(s2, mp[s1])) tot++;
		}
		printf("%d\n", tot);
	}
}
