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

string C[] = {
	"rwwgwwwrwwwgwwr",
	"wbwwwywwwywwwbw",
	"wwbwwwgwgwwwbww",
	"gwwbwwwgwwwbwwg",
	"wwwwbwwwwwbwwww",
	"wywwwwwwwwwwwyw",
	"wwgwwwgwgwwwgww",
	"rwwgwwwswwwgwwr",
	"wwgwwwgwgwwwgww",
	"wywwwwwwwwwwwyw",
	"wwwwbwwwwwbwwww",
	"gwwbwwwgwwwbwwg",
	"wwbwwwgwgwwwbww",
	"wbwwwywwwywwwbw",
	"rwwgwwwrwwwgwwr"
};
int L[256], W[256];
int V[] = { 1, 3, 2, 3, 2, 1, 5, 5, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 3, 10, 5, 10, 5, 10, 10, 10, 5, 5, 10, 10, 3 };

void init() {
    L['w'] = 1; W['w'] = 1;
    L['s'] = 1; W['s'] = 1;
    L['g'] = 2; W['g'] = 1;
    L['y'] = 3; W['y'] = 1;
    L['b'] = 1; W['b'] = 2;
    L['r'] = 1; W['r'] = 3;
}

int g[15][15];

int turn() {
	int totp = 0, tot = 0, l, si, sj, x, w; char d;
	scanf("%d", &w);
	while(w--) {
		scanf("%d %c %d %d", &l, &d, &sj, &si); si--; sj--;
		int vall = 0, valw = 1;
		for(int k = 0; k < l; k++) {
			int i = si + (d == 'v') * k, j = sj + (d == 'h') * k;
			if(!g[i][j]) totp++;
			g[i][j] = 1;
			assert(W[C[i][j]]);
			valw *= W[C[i][j]];
			scanf("%d", &x);
			vall += L[C[i][j]] * V[--x];
		}
		assert(vall && valw);
		tot += vall * valw;
	}
	if(totp == 7) tot += 15;
	return tot;
}

int pt[10];
int main() {
	init();
	int n, m, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++)
		pt[i % n] += turn();
	for(i = 0; i < n; i++)
		printf("%d\n", pt[i]);
}
