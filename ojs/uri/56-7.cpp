#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, m;
const int MAX = 50009;
int x[MAX], y[MAX], nxt[MAX];


/*int bit[1000][1000];

int get(int x, int y) {
	x += 402; y += 402; int sum = 0;
	for(; x; x -= (x & -x))
		for(int j = y; j; j -= (j & -j))
			sum += bit[x][j];
	return sum;
}
inline int get(int x1, int y1, int x2, int y2) { return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1, y1); }
void add(int x, int y, int val) {
	x += 402; y += 402;
	for(; x < 1000; x += (x & -x))
		for(int j = y; j < 1000; j += (j & -j))
			bit[x][j] += val;
}*/
inline int l1(int i) { return i << 2; }
inline int l2(int i) { return l1(i) + 1; }
inline int l3(int i) { return l1(i) + 2; }
inline int l4(int i) { return l1(i) + 3; }

//int tree[2100000];
//void add_tree(int i, int x1, int y1, int x2, int y2, int x3, int y3, int val) {
//	x1 += 400; x2 += 400; y1 += 400; y2 += 400; x3 += 400; y3 += 400;
//	if(x1 > x2 || y1 > y2) return;
//	if(x3 < x1 || x3 > x2 || y3 < y1 || y3 > y2) return;
//	if(x1 == x2 && y1 == y2) { tree[i] += val; return; }
//	int mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
//	if(x3 <= mx && y3 <= my) add_tree(l1(i), x1, y1, mx, my, x3, y3, val);
//	else if(x3 > mx && y3 <= my) add_tree(l2(i), mx + 1, y1, x2, my, x3, y3, val);
//	else if(x3 <= mx && y3 > my) add_tree(l3(i), x1, my + 1, mx, y2, x3, y3, val);
//	else add_tree(l4(i), mx + 1, my + 1, x2, y2, x3, y3, val);
//	tree[i] = max(max(tree[l1(i)], tree[l2(i)]), max(tree[l3(i)], tree[l4(i)]));
//}
//
//int get_tree(int i, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//	x1 += 400; x2 += 400; y1 += 400; y2 += 400; x3 += 400; x4 += 400; y3 += 400; y4 += 400;
//	if(x1 > x2 || y1 > y2) return INT_MIN;
//	if(x4 < x1 || x3 > x2 || y4 < y1 || y3 > y2) return INT_MIN;
//	if(x1 >= x3 && x2 <= x4 && y1 >= y3 && y2 <= y4) return tree[i];
//	int mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
//	int a1 = get_tree(l1(i), x1, y1, mx, my, x3, y3, x4, y4);
//	int a2 = get_tree(l2(i), mx + 1, y1, x2, my, x3, y3, x4, y4);
//	int a3 = get_tree(l3(i), x1, my + 1, mx, y2, x3, y3, x4, y4);
//	int a4 = get_tree(l4(i), mx + 1, my + 1, x2, y2, x3, y3, x4, y4);
//	return max(max(a1, a2), max(a3, a4));
//}
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }


int tree[803 << 2][803 << 2];

void y_add(int x, int i, int y1, int y2, int y3, int val) {
	if(y1 == y2) {
		//printf("adding %d on (%d, %d)\n", val, x, i);
		tree[x][i] += val;
		//if(tree[x][i]) printf("(%d, %d) now %d\n", y1, y2, tree[x][i]);
		return;
	} 
	int my = (y1 + y2) / 2;
	if(y3 <= my) y_add(x, l(i), y1, my, y3, val);
	else y_add(x, r(i), my + 1, y2, y3, val);
	tree[x][i] = max(tree[x][l(i)], tree[x][r(i)]);
	//if(tree[x][i]) printf("(%d, %d) now %d\n", y1, y2, tree[x][i]);
}


void add_tree(int i, int x1, int y1, int x2, int y2, int x3, int y3, int val) {
	//printf("acessing (%d, %d)\n", x1, x2);
	y_add(i, 1, y1, y2, y3, val); 
	if(x1 == x2) return;
	int mx = (x1 + x2) / 2;
	if(x3 <= mx) add_tree(l(i), x1, y1, mx, y2, x3, y3, val);
	else add_tree(r(i), mx + 1, y1, x2, y2, x3, y3, val);
}

int y_get(int x, int i, int y1, int y2, int y3, int y4) {
	if(y1 > y4 || y2 < y3) return INT_MIN;
	if(y1 >= y3 && y2 <= y4)  {
		//printf("got %d on (%d, %d)\n", tree[x][i], y1, y2);
		return tree[x][i];
	}
	int my = (y1 + y2) / 2;
	return max(y_get(x, l(i), y1, my, y3, y4), y_get(x, r(i), my + 1, y2, y3, y4));
}

int get_tree(int i, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	if(x4 < x1 || x3 > x2) return INT_MIN;
	if(x1 >= x3 && x2 <= x4) { /*printf("getting (%d, %d) y\n", x1, x2);*/ return y_get(i, 1, y1, y2, y3, y4); }
	int mx = (x1 + x2) / 2;
	return max(get_tree(l(i), x1, y1, mx, y2, x3, y3, x4, y4), get_tree(r(i), mx + 1, y1, x2, y2, x3, y3, x4, y4));
}

/*int mxx;
void flsh(int i, int x1, int y1, int x2, int y2) {
	x1 += 400; x2 += 400; y1 += 400; y2 += 400;
	mxx = max(i, mxx);
	if(x1 > x2 || y1 > y2) return;
	if(x1 == x2 && y1 == y2) return;
	int mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
	flsh(l1(i), x1, y1, mx, my);
	flsh(l2(i), mx + 1, y1, x2, my);
	flsh(l3(i), x1, my + 1, mx, y2);
	flsh(l4(i), mx + 1, my + 1, x2, y2);
}*/

/*int memo[MAX];
int solve(int i) {
	if(memo[i] != -1) return memo[i];
	int ret = 0;
	for(int j = nxt[i]; j != -1; j = nxt[j])
		if(x[j] > x[i] && y[j] > y[i])
			ret = max(ret, 1 + solve(j));
	return memo[i] = ret;
}*/

vector<int> adj[MAX];
int memo[MAX];
int dfs(int u) {
	int &r = memo[u];
	r = 1 + get_tree(1, -400 + 400, -400 + 400, 400 + 400, 400 + 400, x[u] + 1 + 400, y[u] + 1 + 400, 400 + 400, 400 + 400);
	add_tree(1, -400 + 400, -400 + 400, 400 + 400, 400 + 400, x[u] + 400, y[u] + 400, r);
	//printf("s(%d, %d) = %d\n", x[u], y[u], r);
	for(int v : adj[u])
		dfs(v);
	add_tree(1, -400 + 400, -400 + 400, 400 + 400, 400 + 400, x[u] + 400, y[u] + 400, -r);
	//printf("clear (%d, %d)\n", x[u], y[u]);
}

int deg[MAX];
int main() {
	//flsh(1, -400, -400, 400, 400);
	//printf("%d\n", mxx);
	int i, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		memo[i] = nxt[i] = -1;
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		nxt[a] = b;
		adj[b].pb(a);
		deg[a]++;
	}
	for(i = 0; i < n; i++) {
		if(deg[i]) continue;
		dfs(i);
	}

	int mx = 0;
	for(i = 0; i < n; i++)
		mx = max(mx, memo[i]);
	printf("%d\n", mx);
}
