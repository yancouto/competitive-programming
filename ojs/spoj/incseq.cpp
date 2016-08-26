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
const int modn = 5000000;
inline int mod(int x) { return x % modn; }
int n, k;
int a[10009];
const int BMAX = 100009;
int bit[54][BMAX];
int get(int b, int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum = mod(sum + bit[b][i]);
	return sum;
}
inline int get(int b, int i, int j) { return mod(get(b, j) - get(b, i - 1) + modn); }
void add(int b, int i, int x) {
	for(i += 2; i < BMAX; i += (i & -i))
		bit[b][i] = mod(bit[b][i] + x);
}

int memo[10009][55];
inline int& m(int i, int j) { return memo[i][j]; }
int main() {
	int i, j;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = n - 1; i >= 0; i--) {
		for(j = k; j > 1; j--) {
			m(i, j) = get(j - 1, a[i] + 1, 100002);
			add(j, a[i], m(i, j));
		}
		m(i, 1) = 1;
		add(1, a[i], 1);
	}
	int tot = 0;
	for(i = 0; i < n; i++)
		tot = mod(tot + m(i, k));
	printf("%d\n", tot);
	return 0;
}
