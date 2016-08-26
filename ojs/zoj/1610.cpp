#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int MAX = 8009;
int n;
int tree[MAX << 2];
int lazy[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }
void unlaze(int i, int from, int to) {
	if(lazy[i] == -1) return;
	tree[i] = lazy[i];
	if(from != to){ 
		lazy[l(i)] = lazy[i];
		lazy[r(i)] = lazy[i];
	}
	lazy[i] = -1;
}
void update_tree(int ind, int from, int to, int ul, int ur, int x) {
	unlaze(ind, from, to);
	if(ur < from || ul > to) return;
	if(from >= ul && to <= ur) {
		tree[ind] = x;
		if(from != to)
			lazy[l(ind)] = lazy[r(ind)] = x;
		return;
	}
	int mid = (from + to) / 2;
	update_tree(l(ind), from, mid, ul, ur, x);
	update_tree(r(ind), mid + 1, to, ul, ur, x);
}

int query_tree(int ind, int from, int to, int i) {
	unlaze(ind, from, to);
	if(from == to) return tree[ind];
	int mid = (from + to) / 2;
	if(i <= mid) return query_tree(l(ind), from, mid, i);
	else return query_tree(r(ind), mid + 1, to, i);
}

int main() {
	int i, x, y, c;
	while(scanf("%d", &n) != EOF) {
		memset(tree, -1, sizeof(tree));
		memset(lazy, -1, sizeof(lazy));
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &x, &y, &c);
			update_tree(1, 0, MAX - 1, x, y - 1, c);
		}
		map<int, int> mp;
		int prev = -1;
		for(i = 0; i < MAX - 1; i++) {
			x = query_tree(1, 0, MAX - 1, i);
			// if(x >= 0) printf("%d -> %d\n", i, x);
			if(x != -1 && x != prev) mp[x]++;
			prev = x;
		}
		for(auto &it : mp)
			printf("%d %d\n", it.first, it.second);
		puts("");
	}
	return 0;
}