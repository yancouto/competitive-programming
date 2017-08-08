#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct ev {
	int t, i;
	bool operator < (ev o) const {
		if(t != o.t) return t < o.t;
		return i < o.i;
	}
};

const int N = 312345;

ld p[N], ans[N];
int t[N];
int seen[N];

int bit[N];
void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

int main() {
	int i, n, m;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(i = 0; i < n; i++)
		cin >> t[i] >> p[i];
	int cur = min(n, m);
	set<ev> evs;
	for(i = 0; i < min(m, n); i++) {
		evs.insert(ev{t[i], i});
	}
	ld d = 1;
	for(i = 0; i < n; i++) {
		ans[i] = d * (1. - p[i]);
		d *= p[i];
	}
	ld tot = 0;
	int lt = 0;
	while(!evs.empty()) {
		ev e = *evs.begin();
		lt = e.t;
		evs.erase(evs.begin());
		add(e.i, 1);
		for(i = e.i; i < n && !seen[i] && get(i) == i + 1; seen[i++] = 1) {
			tot += ans[i] * e.t;
		}
		if(cur < n)
			evs.insert(ev{e.t + t[cur], cur}), cur++;
	}
	tot += d * lt;
	printf("%.20f\n", (double) tot);
}
