#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 112345;
#define tm first
#define nv second
int p[N], h[N], d[N], nv[N];
int ans[N];

typedef pair<int, int> pii;
set<pii> pa[N];

void ins(set<pii> &s, pii p) {
	set<pii>::iterator it = s.insert(p).first;
	if(it != s.begin() && -prev(it)->nv >= -p.nv) {
		s.erase(p);
		return;
	}
	while(next(it) != s.end() && -p.nv >= -next(it)->nv)
		s.erase(next(it));
}

int get(set<pii> &s, int x) {
	auto it = s.upper_bound(pii(x, INT_MAX));
	if(it != s.begin()) return -prev(it)->nv;
	assert(0);
}

int main() {
	int i, t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d %d", &p[i], &h[i], &d[i]);
		for(i = 1; i < n; i++)
			nv[i] = 1 + nv[p[i]];
		for(i = n - 1; i >= 0; i--) {
			ins(pa[i], pii(h[i], -nv[i]));
			ans[i] = get(pa[i], d[i]) - nv[i];
			if(i == 0) break;
			if(pa[i].size() > pa[p[i]].size())
				pa[i].swap(pa[p[i]]);
			for(pii p : pa[i])
				ins(pa[::p[i]], p);
			pa[i].clear();
		}
		pa[0].clear();
		for(i = 0; i < n; i++)
			printf("%d%c", ans[i], " \n"[i == n - 1]);
	}
}
