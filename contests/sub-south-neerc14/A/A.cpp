#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
#define fst first
#define snd second

const int N = 1123;

int best = 0;
vector<int> ans;

int ch[N], fst[N];
int n;

struct pab {
	int id, t, a, b;
	bool fake;
	int val;
};
vector<pab> v[N];

void build() {
	set<pii> s;
	for(int c = 1; c <= n; c++) {
		if(ch[c] == 0) continue;
		s.insert(pii(ch[c], c));
	}
	ans.clear();
	int lst = -1;
	while(!s.empty()) {
		pii p = *s.rbegin();
		if(p.snd == lst) p = *next(s.rbegin());
		lst = p.snd;
		s.erase(p);
		int c = p.snd;
		ans.pb(v[c][p.fst - 1].id);
		if(p.fst == ch[c]) { // first
			for(int i = ch[c]; i < int(v[c].size()); i++)
				if(!v[c][i].fake)
					ans.pb(v[c][i].id);
		}
		if(p.fst - 1)
			s.insert(pii(p.fst - 1, c));
	}
}


void solve(int c, int sz) {
	int i;
	ch[c] = sz;
	int val = 0;
	for(int i = 0; i < sz; i++)
		val += v[c][i].val;
	vector<pab> vab;
	for(int d = 1; d <= n; d++) {
		if(d == c) continue;
		ch[d] = 0;
		for(int i = 0; i < min<int>(sz, v[d].size()); i++)
			vab.pb(v[d][i]);
	}
	sort(vab.begin(), vab.end(), [](pab x, pab y) { return x.val > y.val; });
	if(vab.size() < sz - 1) return;
	for(i = 0; i < sz - 1; i++) {
		val += vab[i].val;
		ch[vab[i].t]++;
	}
	for(i = sz - 1; i < int(vab.size()) && vab[i].val > 0; i++) {
		val += vab[i].val;
		ch[vab[i].t]++;
	}
	if(val > best) { best = val; build(); }
}

int main() {
	int i, j;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(i = 0; i < n; i++) {
		int t, a, b;
		cin >> t >> a >> b;
		swap(a, b);
		v[t].pb(pab{i + 1, t, a, max(0, b), b <= 0, a - max(0, b)});
	}
	for(i = 1; i <= n; i++) {
		sort(v[i].begin(), v[i].end(), [](pab x, pab y) { return x.val > y.val; });
		int sum = 0;
		for(pab p : v[i]) sum += p.b;
		if(!v[i].empty()) v[i].front().val += sum;
	}
	for(i = 1; i <= n; i++) {
		int sz = v[i].size();
		for(j = 1; j <= sz; j++)
			solve(i, j);
	}
	printf("%d %d\n", best, int(ans.size()));
	for(int x : ans)
		printf("%d ", x);
	putchar('\n');
}
