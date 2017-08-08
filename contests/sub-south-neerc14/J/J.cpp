#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 30;
const int M = 1e4+1;
const int inf = 1e7;

int n, m, w;
int s[N+1], c[N+1];
int x[N+1];
int ord[N+1];
bitset<M> vs;

vector<pii> rs;
int memo[N][N][M];

int pd (int i, int p, int t) {
	if (i == n || p == w) return 0;
	if (t < 0) return -inf;

	int & me = memo[i][p][t];
	if (me != -1)
		return me;

	me = pd(i+1,p,t);
	me = max(me, pd(i,p+1,t+x[p+1]-x[p]));
	if (t >= 1 + c[ord[i]])
		me = max(me, pd(i+1,p+1,t+x[p+1]-x[p]-c[ord[i]]-1) + s[ord[i]]);
	return me;
}

void build (int i, int p, int t) {
	if (i == n || p == w) return;

	int me = pd(i,p,t);
	
	if (me == pd(i+1,p,t))
		build(i+1,p,t);
	else if (me == pd(i,p+1,t+x[p+1]-x[p]))
		build(i,p+1,t+x[p+1]-x[p]);
	else {
		rs.pb(pii(ord[i]+1,x[p]));
		build(i+1,p+1,t+x[p+1]-x[p]-c[ord[i]]-1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	memset(memo, -1, sizeof memo);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> c[i];
		ord[i] = i;
	}

	sort(ord, ord+n, [] (int i, int j) {
		return c[i] < c[j];
	});

	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;

		for (int j = l; j < r; j++)
			vs[j] = 1;
	}

	
	for (int i = M-1; i >= 0 && w < n; i--)
		if (vs[i])
			x[w++] = i;
	
	for (int i = 0; i < w-i-1; i++)
		swap(x[i], x[w-i-1]);
	
	cout << pd(0,0,x[0]+1);
	build(0,0,x[0]+1);
	cout << " " << rs.size() << endl;

	for (pii att : rs) {
		cout << att.first << " " << att.second << endl;
	}
}
