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
inline int id(int i, int j) { return i * 304 + j; }

int S[202 * 306], sz[202 * 306];
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

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
inline int sq(int a) { return a * a; }

int x[202], y[202], r[202];
bool inside(int i, int j, int p) {
	return sq(x[p] - i) + sq(y[p] - j) <= sq(r[p]);
}

bool ok(int p) {
	int i, j, d;
	for(i = 1; i <= 201; i++)
		for(j = 1; j <= 301; j++)
			if(inside(i, j, p))
				for(d = 0; d < 4; d++)
					join(id(i, j), id(i + dx[d], j + dy[d]));
	return find(id(0, 1)) != find(id(202, 1));
}

int main() {
	int i, j, d, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d %d", &x[i], &y[i], &r[i]);
	for(i = 0; i <= 202; i++)
		for(j = 0; j <= 302; j++)
			S[id(i, j)] = id(i, j), sz[id(i, j)] = 1;
	for(j = 2; j <= 301; j++)
		join(id(0, j), id(0, j - 1)),
		join(id(202, j), id(202, j - 1));
	for(i = 0; ok(i); i++);
	printf("%d\n", i);
}
