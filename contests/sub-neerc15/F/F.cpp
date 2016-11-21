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

int n;
const int N = 112345;
int a[N], block[N], join[N], seg[N], b[N];
vector<int> oc[N];

void solve(int v) {
	if(oc[v].empty()) return;
	vector<int> all;
	for(int i : oc[v])
		if((!block[i] || seg[v] == 1) && a[i + 1] == a[i] + 1)
			all.pb(i);
	debug("val %d all.size() = %d\n", v, (int) all.size());
	if(all.empty()) solve(v + 1);
	else if(all.size() == 1) {
		join[all.back()] = 1;
		debug("join %d!\n", all.back());
		for(int j = all.back() + 1; j < n && a[j] == v + 1; j++) block[j] = 1;
		for(int j = all.back(); j >= 0 && a[j] == v; j--) block[j] = 1;
		solve(v + 1);
	} else {
		solve(v + 1);
		for(int i : all)
			if(!block[i + 1]) {
				block[i] = block[i + 1] = 1;
				for(int j = i; j >= 0 && a[j] == a[i]; j--) block[j] = 1;
				for(int j = i + 1; j < n && a[j] == a[i] + 1; j++) block[j] = 1;
				join[i] = 1;
				debug("join %d!!\n", i);
				break;
			}
	}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("fragmentation.in", "r", stdin);
	freopen("fragmentation.out", "w", stdout);
#endif
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]), b[i] = a[i];
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	for(i = 0; i < n; i++) a[i] = (lower_bound(b, b + bn, a[i]) - b);
	for(i = 0; i < n; i++) oc[a[i]].pb(i);
	a[n] = -1;
	for(i = 0; i < n; i++)
		if(a[i] != a[i + 1])
			seg[a[i]]++;
	solve(0);
	int tot = 1;
	for(i = 0; i < n - 1; i++) join[i] |= (a[i] == a[i + 1]);
	for(i = 0; i < n - 1; i++) tot += (!join[i]);
	printf("%d\n", tot);
	int ct = 0;
	for(i = 0; i < n; i++) { ct++; if(i < n - 1 && !join[i]) printf("%d ", ct), ct = 0; }
	printf("%d\n", ct);
}
