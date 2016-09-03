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
#define pc __builtin_popcount

int p3[100], m;
inline int at(int num, int i) {
	return (num / p3[i]) % 3;
}

int sz[200000];
int memo[200000];
int seen[200000], t;
int solve(int val) {
	int &r = memo[val];
	if(seen[val] == t) return r;
	seen[val] = t;
	if(sz[val] == 1) return r = 0;
	r = 100;
	for(int i = 0; i < m; i++) {
		if(at(val, i) != 2) continue;
		r = min(r, max(solve(val + p3[i] * (0 - 2)), solve(val + p3[i] * (1 - 2))) + 1);
	}
	return r;
}

void gen(int i, int val, vector<int> &v) {
	if(i == m) return (void) (sz[val] = v.size());
	gen(i + 1, val + p3[i] * 2, v);
	vector<int> A, B;
	for(int x : v)
		if((x >> i) & 1) B.pb(x);
		else A.pb(x);
	gen(i + 1, val + p3[i] * 0, A);
	gen(i + 1, val + p3[i] * 1, B);
}

const int N = 51234;
int a[N], st[N];
int main() {
	int i, j, n, sn; char c;
	p3[0] = 1;
	for(i = 1; i < 20; i++)
		p3[i] = p3[i - 1] * 3;
	while(scanf("%d %d", &m, &n) != EOF && m) {
		vector<int> v; int val = 0;
		for(i = 0; i < n; i++) {
			a[i] = 0;
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				a[i] |= (int(c -'0') << j);
			}
			v.pb(a[i]);
		}
		gen(0, 0, v);
		t++;
		for(i = 0; i < m; i++) val += p3[i] * 2;
		printf("%d\n", solve(val));
		//sn = 0;
		//for(i = 0; i < n; i++)
		//	for(j = i + 1; j < n; j++)
		//		st[sn++] = (a[i] ^ a[j]);
		//sort(st, st + sn, [](int x, int y) { return pc(x) < pc(y); });
		//sn = unique(st, st + sn) - st;
		//for(j = 0; j < sn; j++) printf("%d ", st[j]); printf("\n");
		//int bs = (1 << m) - 1;
		//for(i = 1; i < (1 << m); i++) {
		//	if(pc(i) >= pc(bs)) continue;
		//	for(j = 0; j < sn && (st[j] & i); j++);
		//	if(j == sn) bs = i;
		//	if(j == sn) printf("new bs %d (%d)\n", i, pc(i));
		//	bool all = true;
		//	for(j = 0; j < n; j++)
		//		for(int k = j + 1; k < n; k++)
		//			all = (all && ((a[j] ^ a[k]) & i));
		//	if(all) printf("%d\n", i);
		//}
		//printf("%d\n", (int) pc(bs));
	}
}
