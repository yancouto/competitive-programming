#include <cstdio>
#include <algorithm>
#include <unordered_map>
#define debug(args...) fprintf(stderr, "%3d: ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
using namespace std;
typedef long long ull;

const int MAX = 100009;
int n, q;
int a[MAX];
int ql[MAX], qr[MAX];
int qs[MAX];
int mp[MAX];
bool cmp_r(int i, int j) { return qr[i] < qr[j]; }

ull tree[MAX << 2];
ull lazy[MAX << 2];
ull best[MAX << 2], bestlazy[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }
void unlaze(int i, int from, int to) {
	if(!lazy[i] && !bestlazy[i]) return;
	best[i] = max(best[i], tree[i] + bestlazy[i]);
	tree[i] += lazy[i];
	if(from != to) {
		for(int j = l(i); j <= r(i); j++) {
			bestlazy[j] = max(bestlazy[j], lazy[j] + bestlazy[i]);
			lazy[j] += lazy[i];
		}
	}
	lazy[i] = bestlazy[i] = 0;
}
void update_tree(int i, int from, int to, int ul, int ur, int x) {
	unlaze(i, from, to);
	if(ur < from || ul > to) return;
	if(from >= ul && to <= ur) {
		tree[i] += x;
		best[i] = max(best[i], tree[i]);
		if(from != to) {
			for(int j = l(i); j <= r(i); j++) {
				lazy[j] += x;
				bestlazy[j] = max(bestlazy[j], lazy[j]);
			}
		}
		return;
	}
	int mid = (from + to) / 2;
	update_tree(l(i), from, mid, ul, ur, x);
	update_tree(r(i), mid + 1, to, ul, ur, x);
	tree[i] = max(tree[l(i)], tree[r(i)]);
	best[i] = max(best[i], tree[i]);
}
ull query_tree(int i, int from, int to, int left, int right) {
	unlaze(i, from, to);
	if(right < from || left > to) return 0ull;
	if(from >= left && to <= right) return best[i];
	int mid = (from + to) / 2;
	return max(query_tree(l(i), from, mid, left, right), query_tree(r(i), mid + 1, to, left, right));
}
int last[MAX];
ull resp[MAX];
int main() {
	int i, j, k;
	scanf("%d", &n);
	unordered_map<int, int> in; j = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		last[i] = -1;
		if(in.count(a[i])) a[i] = in[a[i]];
		else { mp[j] = a[i]; in[a[i]] = j; a[i] = j++; }
	}

	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &ql[i], &qr[i]);
		qs[i] = i; ql[i]--; qr[i]--;
	}
	sort(qs, qs + q, cmp_r);
	int r = -1;
	for(i = 0; i < q; i++) {
		while(r < qr[qs[i]]) {
			update_tree(1, 0, n - 1, last[a[r + 1]] + 1, r + 1, mp[a[r + 1]]);
			last[a[r + 1]] = r + 1; r++;
		}
		resp[qs[i]] = query_tree(1, 0, n - 1, ql[qs[i]], r);
	}


	for(i = 0; i < q; i++)
		printf("%llu\n", resp[i]);
	return 0;
}