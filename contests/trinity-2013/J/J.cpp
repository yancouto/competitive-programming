#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood;
cood eps = 0;

struct vec {
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood cross (vec a, vec b)
	{ return (b - a) ^ ((*this) - a); }
	int ccw (vec a, vec b)
	{ cood o = cross(a, b); return (eps < o) - (o < -eps); }

	inline bool halfplane ()
	{ return (x > eps || (abs(x) <= eps && y < eps)); }

	bool compare (vec a, vec b) {
		if ((a-(*this)).halfplane() != (b-(*this)).halfplane())
			return (b-(*this)).halfplane();
		return ccw(a,b) > 0;
	}
};

ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

const int N = 2e6 + 7;

vec v[N];
int n, q, es;
int uf[N], wf[N];
int to[N];
ll ar[N];
vector<int> adj[N];
map<pii, int> mp;
ll query[N][3];

int find (int u) {
	if (u == uf[u]) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) return;
	if (wf[u] < wf[v]) swap(u,v);
	wf[u] += wf[v];
	uf[v] = u;
	ll mn = min(ar[u], ar[v]);
	ar[u] += ar[v];
	if (mn == -1)
		ar[u] = -1;
}

int main () {
	scanf("%d", &n);
	int tp = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &v[i].x, &v[i].y);
		if (v[tp].y < v[i].y)
			tp = i;
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int a, b, t;
		scanf("%d %d %d", &t, &a, &b);

		int mr = 0;
		if (a > b) { 
			swap(a,b);
			mr = 1;
		}

		query[i][0] = t;
		if (t) {
			query[i][1] = mp[pii(a,b)] = es;
			adj[a].pb(es); to[es] = b; ar[es] = 0; uf[es] = es; wf[es] = 1; es++;
			adj[b].pb(es); to[es] = a; ar[es] = 0; uf[es] = es; wf[es] = 1; es++;
		} else {
			query[i][1] = (mp[pii(a,b)]^mr);
		}

	}

	for (int i = 0; i < n; i++) {
		sort(adj[i].begin(), adj[i].end(), [i] (int a, int b) {
			return v[i].compare(v[to[a]], v[to[b]]);
		});

		//cout << v[i] << endl;
		if (i == tp)
			ar[find(adj[i].back())] = -1;
		for (int j = 0; j < adj[i].size(); j++) {
			int a = adj[i][j], b = adj[i][(j+1)%adj[i].size()];
			join(a, b^1);
			//cout << v[to[a]] << " com " << v[to[b]];
			ll ca = abs(v[i].cross(v[to[a]], v[to[b]]));
			//printf("ca %lld ar[find(%d)] = %lld\n", ca, a, ar[find(a)]);
			if(ar[find(a)] != -1) ar[find(a)] = ca;
		}
		//cout << endl;
	}
	//for(int i = 0; i < n; i++)
	//	for(int e : adj[i])
	//		printf("%d->%d: ar %lld\n", i, to[e], ar[find(i)]);

	for (int i = q-1; i >= 0; i--) {
		if (query[i][0]) {
			join(query[i][1] ^ 1, query[i][1]);
		} else {
			query[i][2] = ar[find(query[i][1])];
		}
	}

	for (int i = 0; i < q; i++)
		if (!query[i][0])
			printf("%lld\n", query[i][2]);
}
