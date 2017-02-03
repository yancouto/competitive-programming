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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

const int N = 112345;
vector<int> ct[N];


struct pare {
	set<pii> s;
	bool big(pii x) {
		auto it = s.upper_bound(pii(x.fst, -x.snd));
		if(it == s.begin()) return false;
		--it;
		//printf("prev(%d, %d) = (%d, %d)\n", x.fst, x.snd, it->fst, -it->snd);
		if(it->fst < x.fst && -it->snd < x.snd) return true;
		return false;
	}
	void clear() {
		s.clear();
		s.insert(pii(1e9, 1e9));
		s.insert(pii(-1e9, -1e9));
	}
	void add(pii x) {
		auto it = s.lower_bound(pii(x.fst, -x.snd));
		while(it != s.end() && it->fst > x.fst && -it->snd > x.snd)
			it = s.erase(it);
		s.insert(pii(x.fst, -x.snd));
	}
} par[N];

int p[N];
pii pt[N];

vector<int> smaller() {
	int i; vector<int> dp(n);
	for(i = 0; i < n; i++) p[i] = i;
	sort(p, p + n, [](int i, int j) { return pt[i] < pt[j]; });
	int g = 0;
	for(i = 0; i < n; i++) {
		pii x = pt[p[i]];
		//printf(">%d (%d, %d)\n", p[i], x.fst, x.snd);
		//for(int j = 0; j < g; j++) printf("big %d = %d\n", j, par[j].big(x));
		if(g == 0 || par[g - 1].big(x)) {
			par[g].clear();
			par[g].add(x);
			dp[p[i]] = g++;
		} else if(!par[0].big(x)) {
			par[0].add(x);
			dp[p[i]] = 0;
		} else {
			int l = 0, r = g - 2;
			while(l < r) {
				int m = (l + r + 1) / 2;
				if(par[m].big(x)) l = m;
				else r = m - 1;
			}
			par[l + 1].add(x);
			dp[p[i]] = l + 1;
		}
	}
	return dp;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	rd(n);
	for(i = 0; i < n; i++)
		rd(pt[i].fst), rd(pt[i].snd);
	for(i = 0; i < n; i++) pt[i] = pii(-pt[i].fst, -pt[i].snd);
	vector<int> left = smaller();
	for(i = 0; i < n; i++) pt[i] = pii(-pt[i].fst, -pt[i].snd);
	vector<int> right = smaller();
	vector<int> A, B;
	int d = 1 + *max_element(left.begin(), left.end());
	for(i = 0; i < n; i++) {
		//printf("%d: %d %d | %d\n", i, left[i], right[i], d);
		if(left[i] + right[i] != d - 1) continue;
		A.pb(i + 1);
		ct[left[i]].pb(i + 1);
	}
	for(i = 0; i <= n; i++)
		if(ct[i].size() == 1)
			B.pb(ct[i].back());
	printf("%d", (int) A.size());
	sort(A.begin(), A.end());
	for(int x : A) printf(" %d", x);
	putchar('\n');
	printf("%d", (int) B.size());
	sort(B.begin(), B.end());
	for(int x : B) printf(" %d", x);
	putchar('\n');
}
