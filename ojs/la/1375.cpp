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
inline int conv(int i, int j) { return m * i + j; }

bitset<16> fi, bi, ori;
int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
void wrap(int &i, int &j) {
	if(i < 0) i = n - 1;
	if(i >= n) i = 0;
	if(j < 0) j = m - 1;
	if(j >= m) j = 0;
}
bool pos() {
	int i, j, k;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			int nei = 0;
			for(k = 0; k < 8; k++) {
				int ni = i + dir[k][0], nj = j + dir[k][1];
				wrap(ni, nj);
				if(bi[conv(ni, nj)]) nei++;
			}
			if(bi[conv(i, j)]) fi.set(conv(i, j), ((nei == 2) || (nei == 3)));
			else fi.set(conv(i, j), (nei == 3));
		}
	return fi.to_ulong() == ori.to_ulong();
}

int main() {
	int i, j, k, ni, nj, t = 0;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		ori.reset();
		scanf("%d", &k);
		for(i = 0; i < k; i++) {
			scanf("%d %d", &ni, &nj);
			ori.set(conv(ni, nj));
		}
		int p = 0;
		for(i = 0; i < (1 << (n*m)); i++) {
			bi = bitset<16>(i);
			fi.reset();
			p += pos();
		}
		printf("Case %d: ", ++t);
		if(!p) puts("Garden of Eden.");
		else printf("%d possible ancestors.\n", p);
	}
}
