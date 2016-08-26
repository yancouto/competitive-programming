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
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const int MAX = 10009;
int n, a[MAX];
int tree[2][MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }

void build_tree(int ind, int i, int from, int to) {
	tree[ind][i] = 0;
	if(from == to) 
		return;	
	int mid = (from + to) / 2;
	build_tree(ind, l(i), from, mid);
	build_tree(ind, r(i), mid + 1, to);
}

void set_tree(int ind, int i, int from, int to, int pos, int x) {
	if(from == to) {
		tree[ind][i] = x;
		return;
	}
	int mid = (from + to) / 2;
	if(pos <= mid) set_tree(ind, l(i), from, mid, pos, x);
	else set_tree(ind, r(i), mid + 1, to, pos, x);
	tree[ind][i] = max(tree[ind][l(i)], tree[ind][r(i)]);
}

int query_tree(int ind, int i, int from, int to, int ql, int qr) {
	if(qr < from || ql > to) return 0;
	if(from >= ql && to <= qr) return tree[ind][i];
	int mid = (from + to) / 2;
	return max(query_tree(ind, l(i), from, mid, ql, qr), query_tree(ind, r(i), mid + 1, to, ql, qr));
}

int memo[MAX];
int memo2[MAX];

int main() {
	int i, j;
	while(scanf(" %d", &n) != EOF) {
		map<int, int> s;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			s[a[i]] = 1;
		}
		i = 0;
		for(auto &it : s)
			it.snd = i++;
		for(i = 0; i < n; i++)
			a[i] = s[a[i]];
		build_tree(0, 1, 0, s.size() - 1);
		build_tree(1, 1, 0, s.size() - 1);

		for(i = n - 1; i >= 0; i--) {
			memo[i] = 1 + query_tree(0, 1, 0, s.size() - 1, 0, a[i] - 1);
			set_tree(0, 1, 0, s.size() - 1, a[i], memo[i]);
		}
		for(i = 0; i < n; i++) {
			memo2[i] = 1 + query_tree(1, 1, 0, s.size() - 1, 0, a[i] - 1);
			set_tree(1, 1, 0, s.size() - 1, a[i], memo2[i]);
		}
		int mw = 1;
		for(i = 0; i < n; i++)
			mw = max(mw, 2*min(memo2[i], memo[i]) - 1);
		printf("%d\n", mw);
	}
	return 0;
}
