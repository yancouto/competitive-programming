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
int a[102], b[102], e[102];
vector<pii> ev;
struct cmp {
	bool operator()(int i, int j) {
		if(b[i] != b[j]) return b[i] < b[j];
		if(e[i] != e[j]) return e[i] < e[j];
		return i < j;
	}
};
int n;
bool pos(int x) {
	int i, c = 0;
	for(i = 0; i < n; i++)
		e[i] = 0;
	set<int, cmp> cur;
	for(i = 0; i < 10000; i++) {
		while(i >= ev[c].fst) {
			int k = ev[c++].snd;
			if(k > 0) cur.insert(k - 1);
			else cur.erase(-k - 1);
		}
		if(cur.empty()) continue;
		int k = *cur.begin();
		cur.erase(k);
		e[k]++;
		if(e[k] < x) cur.insert(k);
	}
	for(i = 0; i < n; i++)
		if(e[i] != x)
			return false;
	return true;
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &a[i], &b[i]);
		ev.pb(pii(a[i], i + 1));
		ev.pb(pii(b[i], -i - 1));
	}
	ev.pb(pii(20000, 0));
	sort(ev.begin(), ev.end());
	int l = 0, r = 10000;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(pos(m)) l = m;
		else r = m - 1;
	}
	printf("%d\n", l * n);
}
