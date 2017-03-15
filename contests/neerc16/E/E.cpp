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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, q;
const int N = 512345;

struct aaa {
	vector<int> sons;
	int id, p;
	ll sz, tim;
	aaa() : p(-1), tim(0) {}
	void add(int, int);

} v[N];

void aaa::add(int self, int son) {
	v[son].p = self;
	v[son].id = sons.size();
	sons.pb(son);
}

int t[N], k[N];
int en = 1;
vector<int> imp;

ll go(int x, ll sz) {
	if(sz < v[x].sz) {
		imp.pb(x);
		v[x].sz -= sz;
		return v[x].tim * sz;
	} else {
		ll tot = v[x].tim * v[x].sz;
		for(int y : v[x].sons)
			tot += go(y, sz - v[x].sz);
		return tot;
	}
}

int p[N], b[N]; ll ans[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("expect.in", "r", stdin);
	freopen("expect.out", "w", stdout);
#endif
	int i, j; char op;
	imp.pb(0);
	v[0].sz = 0; v[0].tim = 0;
	vector<int> st;
	st.pb(0);
	scanf("%d %d", &n, &q);
	int cur = 0;
	ll tot = 0;
	for(i = 0; i < n; i++) {
		scanf(" %c %d %d", &op, &t[i], &k[i]);
		if(op == '+') {
			if(cur < 0) {
				int kk = min(k[i], -cur);
				while(kk > 0 && st.size() > 1) {
					if(kk < v[st.back()].sz) {
						int g = en++, f = st.back();
						v[g].p = v[f].p; v[g].id = v[f].id;
						v[v[g].p].sons[v[g].id] = g;
						v[g].add(g, f);
						v[g].tim = v[f].tim;
						v[g].sz = v[f].sz - kk;
						v[f].sz = kk;
						v[f].tim = t[i] - v[f].tim;
						tot += v[f].tim * v[f].sz;
						st.pop_back();
						st.push_back(g);
						kk = 0;
					} else {
						int f = st.back();
						v[f].tim = t[i] - v[f].tim;
						tot += v[f].tim * v[f].sz;
						st.pop_back();
						kk -= v[f].sz;
					}
				}
			}
			cur += k[i];
		} else {
			if(cur > 0) {
				int x = min(cur, k[i]);
				k[i] -= x;
				cur -= x;
			}
			if(k[i] == 0) continue;
			int g = en++;
			if(!st.empty())
				v[st.back()].add(st.back(), g);
			else
				imp.push_back(g);
			v[g].sz = k[i];
			v[g].tim = t[i];
			st.pb(g);
			cur -= k[i];
		}
	}

	while(!st.empty()) {
		v[st.back()].tim = 0;
		st.pop_back();
	}

	for(i = 0; i < q; i++)
		scanf("%d", &b[i]), p[i] = i;
	sort(p, p + q, [](int i, int j) { return b[i] < b[j]; });
	ll prev = 0;
	for(i = 0; i < q; i++) {
		ll dif = b[p[i]] - prev;
		prev = b[p[i]];
		vector<int> imp2; imp.swap(imp2);
		for(int x : imp2)
			tot -= go(x, dif);
		if(cur < 0 && -cur > b[p[i]]) ans[p[i]] = -1;
		else ans[p[i]] = tot;
	}
	for(i = 0; i < q; i++)
		if(ans[i] == -1)
			puts("INFINITY");
		else
			printf("%lld\n", ans[i]);
}
