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
const int MAX = 502;
int acc[MAX][MAX];
int r, c, q;
void accc() {
	int i, j;
	for(i = 1; i <= r; i++)
		for(j = 2; j <= c; j++)
			acc[i][j] += acc[i][j - 1];
	for(j = 1; j <= c; j++)
		for(i = 2; i <= r; i++)
			acc[i][j] += acc[i - 1][j];
}
int get(int i1, int j1, int i2, int j2) {
	return acc[i2][j2] - acc[i1 - 1][j2] - acc[i2][j1 - 1] + acc[i1 - 1][j1 - 1];
}

int r1, c1, r2, c2;
ull query() {
	int i, j;
	ull mnj = 0;
	for(j = c1 + 1; j <= c2; j++) 
		mnj += get(r1, j, r2, j) * (j - c1);
	ull cur = mnj;
	for(j = c1 + 1; j <= c2; j++) {
		cur += get(r1, c1, r2, j - 1);
		cur -= get(r1, j, r2, c2);
		mnj = min(mnj, cur);
	}

	ull mni = 0;
	for(i = r1 + 1; i <= r2; i++)
		mni += get(i, c1, i, c2) * (i - r1);
	cur = mni;
	for(i = r1 + 1; i <= r2; i++) {
		cur += get(r1, c1, i - 1, c2);
		cur -= get(i, c1, r2, c2);
		mni = min(mni, cur);
	}
	return mni + mnj;
}

int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d %d", &r, &c, &q);
		for(i = 1; i <= r; i++)
			for(j = 1; j <= c; j++) {
				scanf("%d", &acc[i][j]);
			}
		accc();
		printf("Test Case %d:\n", tt);
		for(i = 0; i < q; i++) {
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			if(r1 > r2) swap(r1, r2);
			if(c1 > c2) swap(c1, c2);
			printf("%d %llu\n", i + 1, query());
		}
		printf("\n");
	}
	return 0;
}
