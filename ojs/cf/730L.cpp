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
#define plus asja

template<class num> inline void read(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}
const int N = 412345;
char s[N];
int no[N], mt[N], en;
ll hs[N], p10[N];
vector<int> adj[N], plus[N], mult[N], ops[N];
vector<ll> sums[N], mults[N];
int st[N], sn;
void pre() {
	int i;
	st[sn++] = 0;
	for(i = 1; s[i]; i++) {
		if(s[i] == '(')
			adj[st[sn - 1]].pb(i), st[sn++] = i;
		if(isdigit(s[i]) && !isdigit(s[i - 1]))
			adj[st[sn - 1]].pb(i);
		if(s[i] == '+') plus[st[sn - 1]].pb(i);
		if(s[i] == '*') mult[st[sn - 1]].pb(i);
		if(s[i] == '+' || s[i] == '*') ops[st[sn - 1]].pb(i);
		no[i] = st[sn - 1];
		if(s[i] == '(' || s[i] == ')') no[i] = st[sn - 2];
		if(s[i] == ')') {
			mt[i] = st[sn - 1];
			mt[st[sn - 1]] = i;
			adj[st[sn - 1]].pb(i + 1);
			sn--;
		}
		hs[i] = mod(10ll * hs[i - 1] + (isdigit(s[i])? s[i] - '0' : 0));
	}
	adj[0].pb(i + 1);
	p10[0] = 1;
	for(i = 1; i < N; i++) p10[i] = mod(p10[i - 1] * 10ll);
}

ll vval[N];
inline ll val(int l, int r) {
	if(s[l] == '(') assert(mt[l] == r);
	if(s[l] == '(') return vval[l];
	return mod(hs[r] - mod(hs[l - 1] * p10[r - l + 1]) + modn);
}

typedef function<ll (ll, ll)> op;
ll sum(ll a, ll b) { return mod(a + b); }
ll mul(ll a, ll b) { return mod(a * b); }

const int M = 10 * N;
int L[M], R[M];
ll tr[M];
int build(vector<ll> &v, op o, int l, int r) {
	int i = en++;
	//printf("bu %d(%d, %d)\n", i, l, r);
	if(l == r) { tr[i] = v[l]; return i; }
	int m = (l + r) / 2;
	L[i] = build(v, o, l, m);
	R[i] = build(v, o, m + 1, r);
	tr[i] = o(tr[L[i]], tr[R[i]]);
	return i;
}

ll query(ll e, op o, int i, int l, int r, int ql, int qr) {
	if(qr < ql) return e;
	//printf("qu %d(%d, %d)\n", i, l, r);
	if(l > qr || r < ql) return e;
	//if(l >= ql && r <= qr) printf("ret %d[%d,%d] = %lld\n", i, l, r, tr[i]);
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return o(query(e, o, L[i], l, m, ql, qr), query(e, o, R[i], m + 1, r, ql, qr));
}

int sr[N], mr[N];
vector<int> cmul[N];
ll go(int u) {
	ll cur = 1, val = 0;
	for(int i = 0; i < adj[u].size() - 1; i++) {
		if(i && s[ops[u][i-1]] == '+') sums[u].pb(cur), val += cur, cur = 1;
		ll v;
		if(s[adj[u][i]] == '(') v = go(adj[u][i]);
		else v = ::val(adj[u][i], adj[u][i + 1] - 2);
		cur = mod(cur * v);
		mults[u].pb(v);
		//printf("mults[%d]->%lld\n", u, v);
	}
	for(int i = 0; i < mult[u].size(); i++) cmul[u].pb((lower_bound(ops[u].begin(), ops[u].end(), mult[u][i]) - ops[u].begin()) + 1);
	sums[u].pb(cur); val += cur;
	mr[u] = build(mults[u], mul, 0, mults[u].size() - 1);
	sr[u] = build(sums[u], sum, 0, sums[u].size() - 1);
	vval[u] = val;
	return val;
}

int solve(int l, int r) {
	if(no[l] != no[r]) return -1;
	if(s[l] == '+' || s[l] == '*' || s[l] == ')' || s[r] == '+' || s[r] == '*' || s[r] == '(') return -1;
	if(s[l] == '(' && mt[l] > r) return -1;
	if(s[r] == ')' && mt[r] < l) return -1;
	int u = no[l];
	auto sl = lower_bound(plus[u].begin(), plus[u].end(), l);
	auto sr = upper_bound(plus[u].begin(), plus[u].end(), r);
	if(sl == sr) {
		// caso sem somas
		auto ml = lower_bound(mult[u].begin(), mult[u].end(), l);
		auto mr = upper_bound(mult[u].begin(), mult[u].end(), r);
		if(ml == mr) return val(l, r);
		else return mod(mod(val(l, (*ml) - 1) * query(1, mul, ::mr[u], 0, mults[u].size() - 1, cmul[u][ml - mult[u].begin()], cmul[u][(mr - mult[u].begin()) - 1] - 1)) * val((*prev(mr)) + 1, r));
	} else {
		ll res = query(0, sum, ::sr[u], 0, sums[u].size() - 1, (sl - plus[u].begin()) + 1, (sr - plus[u].begin()) - 1);
		ll left, right;
		auto ml = lower_bound(mult[u].begin(), mult[u].end(), l);
		auto mr = upper_bound(mult[u].begin(), mult[u].end(), *sl);
		if(ml == mr) left = val(l, (*sl) - 1);
		else left = mod(val(l, (*ml) - 1) * query(1, mul, ::mr[u], 0, mults[u].size() - 1, cmul[u][ml - mult[u].begin()], cmul[u][(mr - mult[u].begin()) - 1]));
		ml = lower_bound(mult[u].begin(), mult[u].end(), *prev(sr));
		mr = upper_bound(mult[u].begin(), mult[u].end(), r);
		if(ml == mr) right = val((*prev(sr)) + 1, r);
		else {
			right = mod(val((*prev(mr)) + 1, r) * query(1, mul, ::mr[u], 0, mults[u].size() - 1, cmul[u][ml - mult[u].begin()] - 1, cmul[u][(mr - mult[u].begin()) - 1] - 1));
		}
		return mod(res + left + right);
	}
}


int main() {
	int n;
	int i, j, l, r;
	scanf("%s", s + 1);
	pre();
	go(0);
	read(n);
	while(n--) {
		read(l); read(r);
		printf("%d\n", solve(l, r));
	}
}
