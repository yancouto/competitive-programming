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

const int N = 112345;
int a[N], b[N];

map<int, vector<int>> posA;
map<int, vector<int>> posB;
map<pii, vector<int>> mp;
int neqA[N], neqB[N];

int best, bestc;
inline void reg(int x) {
	if(x > best) best = x, bestc = 0;
	if(x == best) bestc++;
}
int s;

inline int get(vector<int> &v, int l, int r) {
	return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
}

int try_(int i, int A, int B) {
	int l = i, r = s - 1;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(get(posA[A], i, m) + get(posB[B], i, m) - get(mp[pii(A, B)], i, m) == m - i + 1) l = m;
		else r = m - 1;
	}
	return l - i + 1;
}

int main() {
	for_tests(tn, tt) {
		posA.clear(); posB.clear(); mp.clear();
		int i;
		scanf("%d", &s);
		for(i = 0; i < s; i++) {
			int d;
			scanf("%d %d %d", &d, &a[i], &b[i]);
			a[i] = d + a[i];
			posA[a[i]].pb(i);
			b[i] = d - b[i];
			posB[b[i]].pb(i);
			mp[pii(a[i], b[i])].pb(i);
		}
		a[s] = b[s] = 1e9;
		for(i = s - 1; i >= 0; i--) {
			if(a[i] != a[i + 1]) neqA[i] = i + 1;
			else neqA[i] = neqA[i + 1];
			if(b[i] != b[i + 1]) neqB[i] = i + 1;
			else neqB[i] = neqB[i + 1];
		}
		best = bestc = 0;
		for(i = 0; i < s; i++) {
			if(neqA[i] == s || neqB[i] == s) { reg(s - i); continue; }
			int x = max(try_(i, a[i], b[neqA[i]]), try_(i, a[neqB[i]], b[i]));
			reg(x);
		}
		printf("Case #%d: %d %d\n", tt, best, bestc);
	}
}
