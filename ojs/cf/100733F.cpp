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
const int MAX = 100009;
ll d[MAX], v[MAX], t[MAX]; ll s[MAX];

struct cmp_t {
	bool operator() (int i, int j) {
		return t[i] > t[j];
	}
};
struct cmp_s {
	bool operator() (int i, int j) {
		return s[i] > s[j];
	}
};

inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }
ll tree[(MAX * 2) << 2];
ll query_tree(int i, int from, int to, int ql, int qr) {
	if(from > qr || to < ql) return INT_MIN;
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return max(query_tree(l(i), from, mid, ql, qr), query_tree(r(i), mid + 1, to, ql, qr));
}

void set_tree(int i, int from, int to, int x, ll val) {
	if(from == to) {
		if(val > tree[i]) tree[i] = val;
		return;
	}
	int mid = (from + to) / 2;
	if(x <= mid) set_tree(l(i), from, mid, x, val);
	else set_tree(r(i), mid + 1, to, x, val);
	tree[i] = max(tree[l(i)], tree[r(i)]);
}

int main() {
	int i, n;
	scanf("%d", &n);
	map<ll, int> mp;
	for(i = 0; i < n; i++) {
		scanf("%I64d %I64d %I64d", &d[i], &v[i], &t[i]);
		t[i] = d[i] - t[i];
		mp[d[i]] = 0; mp[t[i]] = 0;
	}
	i = 0;
	for(auto &e : mp)
		e.snd = i++;
	for(i = 0; i < n; i++) {
		s[i] = v[i] + query_tree(1, 0, mp.size() - 1, mp[t[i]], mp[d[i]]);
		set_tree(1, 0, mp.size() - 1, mp[d[i]], s[i]);
	}
	printf("%I64d\n", *max_element(s, s + n));
	return 0;
}
