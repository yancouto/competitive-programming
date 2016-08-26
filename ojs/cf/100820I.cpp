#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 5123;
struct pt {
	double x, y;
	pt() {}
	pt(double a, double b) : x(a), y(b) {}
	double dists(pt o) { return (x - o.x) * (x - o.x) + (y - o.y) * (y - o.y); }
	pt operator + (pt o) { return pt(x + o.x, y + o.y); }
	pt operator - (pt o) { return pt(x - o.x, y - o.y); }
	pt operator * (double d) { return pt(x * d, y * d); }
	pt operator / (double d) { return pt(x / d, y / d); }
} p[N];
const double eps = 1e-8;

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

map<pii, vector<int>> mp;
vector<int> col(pt c) {
	vector<int> v;
	for(int dx = -5; dx <= 5; dx++)
		for(int dy = -5; dy <= 5; dy++)
			if(mp.count(pii(round(c.x)+dx, round(c.y)+dy)))
				for(int i : mp[pii(round(c.x)+dx, round(c.y)+dy)])
					if(p[i].dists(c) <= 4. + eps)
						v.pb(i);
	return v;
}

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
	for(i = 0; i < n; i++) mp[pii(round(p[i].x), round(p[i].y))].pb(i);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(p[i].dists(p[j]) <= 4. + eps)
				join(i, j);
	vector<pt> pos;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			if(find(i) == find(j)) continue;
			if(p[i].dists(p[j]) > 16. + eps) continue;
			pt mid = (p[i] + p[j]) / 2.;
			pt norm = p[j] - p[i];
			norm = pt(-norm.y, norm.x);
			norm = norm / sqrt(norm.dists(pt(0, 0)));
			double dist = sqrt(abs(4. - p[i].dists(mid)));
			pos.pb(mid + (norm * dist));
			assert(p[i].dists(pos.back()) <= 4. + eps);
			assert(p[j].dists(pos.back()) <= 4. + eps);
			pos.pb(mid - (norm * dist));
			assert(p[i].dists(pos.back()) <= 4. + eps);
			assert(p[j].dists(pos.back()) <= 4. + eps);
		}
	int best = 0;
	for(i = 0; i < n; i++) best = max(best, sz[find(i)] + 1);
	for(pt c : pos) {
		vector<int> v = col(c);
		set<int> s;
		for(int x : v) s.insert(find(x));
		int ans = 1;
		for(int x : s) ans += sz[x];
		best = max(best, ans);
	}
	printf("%d\n", best);
}
