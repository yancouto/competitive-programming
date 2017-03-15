#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 5e3+7;

int n, w;
int h, m;
int l, k;
int qr;
ll vl[2][N][2];
set<int> s[N];
int lm[N][2];

void fail () {
	printf("yes\n%d\n", qr+1);
	exit(0);
}

int main() {
	freopen("jenga.in", "r", stdin);
	freopen("jenga.out", "w", stdout);
	scanf("%d %d", &w, &n);
	scanf("%d", &n);
	scanf("%d", &m);

	ll sm = 0;
	for (int j = 1; j <= w; j++)
		sm += j;

	for (int i = n-1; i >= 0; i--) {
		lm[i][0] = 1;
		lm[i][1] = w;
		
		for (int j = 0; j < 2; j++) {
			if (i + 1 < n)
				for (int k = 0; k < 2; k++)
					vl[j][i][k] = vl[j][i+1][k];
			vl[j][i][0] += sm;
			vl[j][i][1] += w;
		}

	}

	for (qr = 0; qr < m; qr++) {
		scanf("%d %d", &l, &k);
		l--;
		
		s[l].insert(k);
		while (lm[l][0] <= w && s[l].find(lm[l][0]) != s[l].end()) lm[l][0]++;
		while (lm[l][1] >= 1 && s[l].find(lm[l][1]) != s[l].end()) lm[l][1]--;

		for (int i = l; i >= 0; i--) {
			vl[l&1][i][0] -= k;
			vl[l&1][i][1]--;

			if (lm[i][0] > w) {
				if (i == n-1) {
					n--;
				} else {
					fail();
				}
			}
			
			if (i + 1 < n)
				if (2ll*vl[i&1][i+1][0] <= (2ll*lm[i][0] - 1)*vl[i&1][i+1][1] || 
					2ll*vl[i&1][i+1][0] >= (2ll*lm[i][1] + 1)*vl[i&1][i+1][1] )
					fail();
		}
	}

	printf("no\n");
}
