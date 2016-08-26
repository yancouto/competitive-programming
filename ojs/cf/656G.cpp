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

int it[100];
char g[100][100];

int main() {
	int F, I, T, i, j, tot = 0;
	scanf("%d %d %d", &F, &I, &T);
	for(i = 0; i < F; i++)
		for(j = 0; j < I; j++) {
			scanf(" %c", &g[i][j]);
			it[j] += (g[i][j] == 'Y');
			if(it[j] == T && g[i][j] == 'Y') tot++;
		}
	printf("%d\n", tot);
}
