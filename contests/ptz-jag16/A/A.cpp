#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const  int N = 1e3+7;

int memo[N][N];
int n, m;
char str[2][N];

int pd (int i, int j) {
	if (i >= n) return 1;
	if (j >= m) return 0;

	int & me = memo[i][j];
	if (me != -1) return me;


	me = pd(i, j+1);
	if (!me && str[0][i] == str[1][j])
		me = pd(i+2, j+1);
	
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf(" %s %s",  str[0], str[1]);

	n = strlen(str[0]);
	m = strlen(str[1]);

	if (pd(0, 0))
		printf("Yes\n");
	else if (pd(1, 0))
		printf("Yes\n");
	else
		printf("No\n");
}
