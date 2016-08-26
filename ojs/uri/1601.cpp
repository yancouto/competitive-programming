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
int n, a[1003];
int mult[2005][2005];

int main() {
	int i, j, t = 0;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a, a + n);
		for(i = 1; i <= 2*n; i++)
			for(j = 1; j <= 2*n; j++)
				mult[i][j] = abs(a[(i-1)%n] - a[((j-1)%n)]);
		for(i = 1; i <= 2*n; i++)
			for(j = 1; j <= 2*n; j++)
				mult[i][j] += mult[i][j - 1];
		for(j = 1; j <= 2*n; j++)
			for(i = 1; i <= 2*n; i++)
				mult[i][j] += mult[i - 1][j];
		int mn = INT_MAX;
		for(i = 1; i < n; i++) {
			for(j = 0; j < n; j++) {
				int A = 0, B = 0;
				A = (mult[i+j][i+j] - mult[j][i+j] - mult[i+j][j] + mult[j][j]) / 2;
				B = (mult[n+j][n+j] - mult[n+j][i+j] - mult[i+j][n+j] + mult[i+j][i+j]) / 2;
				mn = min(mn, A + B);
			}
		}
		printf("%d\n", mn);
	}
	return 0;
}
