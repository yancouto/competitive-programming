#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;
const int M = 21234500;

int l[N], r[N], tr[N][26], T[M][2], ct[M], t, en;
int n;

struct trip {
	int x, y, z;
	trip() {}
	trip(int a, int b, int c) : x(a), y(b), z(c) {}
	bool operator < (trip o) {
		if(z != o.z) return z < o.z;
		return pii(x, y) < pii(o.x, o.y);
	}
	bool operator == (trip o) {
		return z == o.z && y == o.y && z == o.z;
	}
};

void dfs(int u) {
	l[u] = t++;
	for(int i = 0; i < 26; i++)
		if(tr[u][i])
			dfs(tr[u][i]);
	r[u] = t-1;
	printf("l[%d] = %d -- ", u, l[u]);
	printf("r[%d] = %d\n", u, r[u]);
}

void add(int v, int x) {
	printf("add[%d] %d\n", v, x);
	ct[v]++;
	for(int i = 18; i >= 0; i--) {
		int b = (x >> i) & 1;
		if(!T[v][b]) T[v][b] = en++;
		v = T[v][b];
		ct[v]++;
	}
}

void add(int i, int l, int r, trip t) {
	if(l == r) {
		add(i, t.y);
		return;
	}
	int m = (l + r) / 2;
	if(t.x <= m) add(2 * i, l, m, t);
	else add(2 * i + 1, m + 1, r, t);
}

void add(trip t) {
	add(1, 0, n, t);
}

int query(int v, int r) {
	if(r < 0) return 0;
	int tot = 0;
	for(int i = 18; i >= 0; i--) {
		int b = (r >> i) & 1;
		if(b && T[v][0]) tot += ct[T[v][0]];
		if(!T[v][b]) return tot;
		v = T[v][b];
	}
	return tot + ct[v];
}

int query(int v, int l, int r) {
	return query(v, r) - query(v, l - 1);
}

int query(int i, int L, int R, trip t) {
	if(L > r[t.x] || R < l[t.x]) return 0;
	if(L >= l[t.x] && R <= r[t.x]) return query(i, l[t.y], r[t.y]);
	int m = (L + R) / 2;
	return query(i, L, m, t) + query(i, m + 1, R, t);
}

int query(trip t) {
	query(1, 0, n, t);
}

trip que[N], qs[N], pt[N]; int sz, ans[N], pai[N], id[N][3], p[N];
char s[N];

int get(trip t) {
	int i = lower_bound(que, que + sz, t) - que;
	return ans[i];
}

int main() {
	int i, j, g, k, q; char op, c;
	scanf("%d %d", &n, &k);
	en = 5;
	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++) {
			if(j < k) scanf("%s", s);
			else s[0] = 0;
			int v = j;
			for(g = 0; s[g]; g++) {
				if(!tr[v][s[g]-'a']) tr[v][s[g]-'a'] = en++;
				pai[tr[v][s[g] - 'a']] = v;
				v = tr[v][s[g]-'a'];
			}
			//id[v].pb(i);
			id[i][j] = v;
		}
	t = 0; dfs(0); t = 0; dfs(1); t = 0; dfs(2);
	int u[3] = {0, 1, 2};
	scanf("%d", &q);
	for(j = 0; j < q; j++) {
		scanf("%d %c", &i, &op); i--;
		if(op == '+') {
			scanf(" %c", &c);
			u[i] = tr[u[i]][c - 'a'];
		} else {
			u[i] = pai[u[i]];
		}
		qs[j] = trip(u[0], u[1], u[2]);
		printf("(%d,%d) (%d,%d) (%d,%d)\n", l[u[0]], r[u[0]], l[u[1]], r[u[1]], l[u[2]], r[u[2]]);
		p[j] = j;
	}
	en = 4 * (n + 2);

	for(i = 0; i < q; i++)
		que[2*i] = trip(qs[i].x, qs[i].y, r[qs[i].z]),
			que[2*i+1] = trip(qs[i].x, qs[i].y, l[qs[i].z]-1);
	sort(que, que + 2 * i);
	sz = unique(que, que + 2 * i) - que;
	for(i = 0; i < n; i++) pt[i] = trip(l[id[i][0]], l[id[i][1]], l[id[i][2]]);
	sort(pt, pt + n);
	j = 0;
	for(i = 0; i < sz; i++) {
		while(j < n && pt[j].z <= que[i].z) add(pt[j++]);
		printf("answering (%d,%d) (%d,%d) <=%d\n", l[que[i].x], r[que[i].x], l[que[i].y], r[que[i].y], que[i].z);
		ans[i] = query(que[i]);
		printf("ans[%d] = %d\n", i, ans[i]);
	}

	for(i = 0; i < q; i++)
		printf("%d\n", get(trip(qs[i].x, qs[i].y, r[qs[i].z])) - get(trip(qs[i].x, qs[i].y, l[qs[i].z]-1)));
}
