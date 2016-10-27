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

const int N = 1e5+7;

int ts;
int n;
int fr[N];
int a[2][N];
int df;
int ls;

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);

		df = 0;

		for (int k = 0; k < 2; k++)
			for (int i = 0; i < n; i++) {
				fr[i] = 0;
				scanf("%d", &a[k][i]);
			}


		ls = 0;
		for (int i = 0; i < n; i++) {
			fr[a[0][i]]++;
			df += !!(fr[a[0][i]]) - !(fr[a[0][i]]);
			fr[a[1][i]]--;
			df += !!(fr[a[1][i]]) - !(fr[a[1][i]]);

			if (df == 0) {
				printf("%d-%d ", ls+1, i+1);
				ls = i+1;
			}
		}
		printf("\n");

	}
}
