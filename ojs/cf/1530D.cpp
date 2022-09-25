#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

const int N = 212345;
int sel[N];
int a[N], b[N];
int mrk = 0;
int vis[N];
vector<int> buf;

bool dfs(int i) {
	debug("dfs %d\n", i + 1);
	if (vis[i] == mrk)
		return true;
	buf.pb(i);
	vis[i] = mrk;
	if (a[i] != -1)
		return dfs(a[i]);
	return false;
}

int go() {
	scanf("%d", &n);
	mrk++;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = --a[i];
		debug("sel[%d] = %d/%d\n", a[i] + 1, sel[a[i]], mrk);
		if(sel[a[i]] < mrk) {
			sel[a[i]] = mrk;
			debug("sel[%d] = %d/%d\n", a[i] + 1, sel[a[i]], mrk);
		} else
			a[i] = -1;

		debug("%d -> %d\n", i + 1, a[i] + 1);
	}
	vector<pair<int, int>> all;
	int count = 0;
	for(int i = 0; i < n; i++) {
		if (vis[i] == mrk) continue;
		buf.clear();
		bool cyc = dfs(i);
		debug("i %d sz %d cyc %d\n", i + 1, (int) buf.size(), cyc);
		if (!cyc) {
			count += buf.size();
			all.pb(pii(buf[0], *buf.rbegin()));
		}
	}
	if (count == 0) return n;
	if (count == 1) {
		int x = all[0].fst;
		a[x] = b[x];
		for(int i = 0; i < n; i++)
			if (i != x && a[i] == a[x])
				a[i] = x;
		return n - 1;
	}
	for(int i = 0; i < all.size(); i++) {
		int j = (i + 1) % all.size();
		a[all[i].snd] = all[j].fst;
	}
	return n - all.size();
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		printf("%d\n", go());
		for(int i = 0; i < n; i++)
			printf("%d%c", a[i] + 1, " \n"[i == n - 1]);
	}
}
