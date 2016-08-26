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

int freq[105][256];
int f[256];
char s1[102][100], s2[102][100];
int main() {
	int i, j, k, j2, n, m; char c;
	scanf("%d", &k);
	for(i = 0; i < k; i++) {
		scanf(" %s %s", s1[i], s2[i]);
		for(j = 0; s1[i][j]; j++)
			freq[i][s1[i][j]]++;
		for(j = 0; s2[i][j]; j++)
			freq[i][s2[i][j]]++;
	}
	int mi, mx = -1;
	for(i = 0; i < k; i++) {
		scanf("%d %d", &n, &m);
		memset(f, 0, sizeof f);
		for(j = 0; j < n; j++)
			for(j2 = 0; j2 < m; j2++) {
				scanf(" %c", &c);
				f[c]++;
			}
		int mn = INT_MAX;
		for(j = 0; j < 256; j++) {
			if(!freq[i][j]) continue;
			mn = min(mn, f[j] / freq[i][j]);
		}
		if(mn > mx) {
			mx = mn;
			mi = i;
		}
	}
	printf("%s %s\n", s1[mi], s2[mi]);
	return 0;
}
