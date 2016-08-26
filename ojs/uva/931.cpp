#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fst first
#define snd second

int w, d[32], v[32], n;
pii memo[32][1009];
pii solve(int i, int left) {
	if(i == n) return pii(0, 0);
	pii &r = memo[i][left];
	if(r.fst != -1) return r;
	r = solve(i + 1, left);
	if(3 * w * d[i] <= left) {
		pii q = solve(i + 1, left - 3 * w * d[i]);
		q.fst += v[i];
		q.snd++;
		r = max(r, q);
	}
	return r;
}

void build(int i, int left) {
	if(i == n) return;
	if(solve(i, left) == solve(i + 1, left))
		build(i + 1, left);
	else {
		printf("%d %d\n", d[i], v[i]);
		build(i + 1, left - 3 * w * d[i]);
	}
}

int main() {
	int i, t;
	bool f = true;
	while(scanf("%d %d", &t, &w) != EOF) {
		if(!f) putchar('\n');
		f = false;
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &d[i], &v[i]);
		memset(memo, -1, sizeof memo);
		pii p = solve(0, t);
		printf("%d\n%d\n", p.fst, p.snd);
		build(0, t);
	}
}
