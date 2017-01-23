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

const int N = 5e4+7;

char v[2][N];
char p[5];
int n;

int solve (int k) {
}

int main () {
	scanf(" %s", v[0]);
	scanf(" %s", v[1]);
	n = strlen(v[0]);

	for (int i = 0; i < 5; i++)
		p[i] = 'a'+i;

	int r = n;
	do {
		for (int i = 0; i < n; i++)
			r = min(r, solve(i));
	} while (next_permutation(p, p+5));

	printf("%d\n", r);
}
