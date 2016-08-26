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
#define div lalalal

int dv[512345];
int ps[512345]; int pn;
vector<int> div[512345];

int best = 0;
int n;
int a[10];

//int vs[100]; int vn;
//void go(int x, int ind) {
//	vs[ind] = x;
//	for(int i = 0; i < pn && x * ps[i] <= 500000; i++)
//		go(x * ps[i], ind + 1);
//	if(x * 2 > 500000) {
//		int tot = 0;
//		for(int i = 0; i < n && tot < best; i++) {
//			int k = a[i];
//			for(int j = ind; j >= 0 && tot < best; j--)
//				while(k >= vs[j] && tot < best)
//					tot++, k -= vs[j];
//		}
//		best = tot;
//	}
//}

int bk[100][7];
inline void go2(int x, int tot, int ind) {
	if(x == 1 && clock() > 1.9 * CLOCKS_PER_SEC) {
		printf("%d\n", best);
		exit(0);
	}
	if(tot >= best) return;
	int i;
	for(i = 0; i < n; i++) {
		bk[ind][i] = a[i];
		while(tot < best && a[i] >= x) a[i] -= x, tot++;
		if(tot == best) {
			for(int j = 0; j <= i; j++) a[j] = bk[ind][j];
			return;
		}
	}
	if(x == 1) return (void) (best = tot);
	for(int y : div[x])
		go2(y, tot, ind + 1);
	for(i = n - 1; i >= 0; i--) a[i] = bk[ind][i];
}

int st[100], sn;
int main() {
	int i, j;
	for(i = 2; i <= 500000; i++)
		if(!dv[i]) {
			ps[pn++] = i;
			for(j = 2*i; j <= 500000; j += i)
				dv[j] = i;
		}
	for(i = 1; i <= 500000; i++)
		for(j = 0; j < pn && ps[j] * i <= 500000; j++)
			div[i * ps[j]].pb(i);
	for(i = 2; i <= 500000; i++)
		random_shuffle(div[i].begin(), div[i].end());
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n, greater<int>());
	for(i = 0; i < n; i++) best += __builtin_popcount(a[i]);
	for(i = 3; i <= 5; i++) {
		sn = 0;
		for(j = 1; j <= 500000; j *= i)
			st[sn++] = j;
		int tot = 0;
		for(int k = 0; k < n && tot < best; k++) {
			int x = a[k];
			for(j = sn - 1; j >= 0 && tot < best; j--)
				while(x >= st[j] && tot < best)
					x -= st[j], tot++;
		}
		best = tot;
	}
	//go(1, 0);
	for(i = 500000; i * 2 > 500000; i--) go2(i, 0, 0);
	printf("%d\n", best);
}
