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

int memo[1003][1003][2], mx[1003][1003];
char s1[1003], s2[1003];
int K;

int seen[1003][1003], t;
int main() {
	int i, j, k, g;
	while(true) {
		scanf("%d", &K);
		if(!K) return 0;
		scanf("%s %s", s1, s2);
		t++;
		for(i = 0; s1[i]; i++)
			for(j = 0; s2[j]; j++)
				if(seen[i][j] < t) {
					for(k = 0; s1[i+k] && s2[j+k] && s1[i+k] == s2[j+k]; k++) seen[i+k][j+k] = t;
					seen[i+k][j+k] = t;
					for(g = 0; g <= k; g++) mx[i+g][j+g] = k - g;
				}
		int l1 = strlen(s1), l2 = strlen(s2);
		for(i = 0; i <= l1; i++)
			memo[i][l2][0] = memo[i][l2][1] = 0;
		for(j = 0; j <= l2; j++)
			memo[l1][j][0] = memo[l1][j][1] = 0;
		for(i = l1 - 1; i >= 0; i--)
			for(j = l2 - 1; j >= 0; j--) {
				int &r = memo[i][j][0];
				r = max(memo[i+1][j][0], memo[i][j+1][0]);
				if(mx[i][j] >= K) r = max(r, K + memo[i+K][j+K][1]);
				int &s = memo[i][j][1];
				s = max(memo[i+1][j][0], memo[i][j+1][0]);
				if(s1[i] == s2[j]) s = max(s, 1 + memo[i+1][j+1][1]);
			}
		printf("%d\n", memo[0][0][0]);
	}
}
