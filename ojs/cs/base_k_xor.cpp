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

int A[100], va[100], B[100], vb[100];
int pot[100];

int prn(int s[], int acc[], int x, ll k) {
	ll b = 1;
	int i = 0;
	pot[0] = 1;
	while(b <= ll(1.1e8)) b *= k, pot[++i] = b;
	int j = 0;
	for(i--, b /= k; i >= 0; i--, b /= k)
		s[j++] = (x / b) % k;
	//for(i = 0; i < j; i++) printf("%d", s[i]); putchar('\n');
	acc[j] = 0;
	acc[j - 1] = s[j - 1];
	for(i = j - 2; i >= 0; i--) acc[i] = acc[i + 1] + s[i] * pot[j - i-1];
	return j;
}
int ans[50];

int main() {
	int a, b, k, i, j, d;
	for_tests(t, tt) {
		scanf("%d %d %d", &a, &b, &k);
		if(a == b) { printf("%d\n", a); continue; }
		memset(ans, 0, sizeof ans);
		int n = prn(B, vb, b, k);
		prn(A, va, a, k);
		int ak = ((k * (k - 1)) / 2) % k;
		for(i = 0; A[i] == B[i]; i++);
		assert(B[i] > A[i]);
		int s = i;
		int cur = 0;
		for(i++; i < n; i++) {
			ans[i] = (ans[i] + ak * cur) % k;
			//printf("(1)ans[%d] += %d * %d\n", n-i, cur, ak);
			cur = (cur + pot[n - i - 1-1] * (k - A[i] - 1)) % k;
			ans[i] = (ans[i] + (pot[n - i-1] - va[i + 1]) * A[i]) % k;
			//printf("(2)ans[%d] += %d * %d\n", n-i, pot[n - i-1] - va[i + 1], A[i]);
			for(d = A[i] + 1; d < k; d++) ans[i] = (ans[i] + pot[n - i-1] * d) % k;
			//for(d = A[i] + 1; d < k; d++) printf("(3)ans[%d] += %d * %d\n", n-i, pot[n-i-1], d);
		}
		ans[s] = (ans[s] + (pot[n - s-1] - va[s + 1]) * A[s]) % k;
		//printf("(4)ans[%d] += %d * %d\n", n-s, pot[n - s-1] - va[s + 1], A[s]);
		//puts("--------");
		int tm = B[s] - A[s] - 1;
		for(i = A[s] + 1; i < B[s]; i++) ans[s] = (ans[s] + i * pot[n - s-1]) % k;
		//for(i = A[s] + 1; i < B[s]; i++) printf("(5)ans[%d] += %d * %d\n", n-s, pot[n-1-i], i);
		for(i = s + 1; i < n; i++) ans[i] = (ans[i] + ((ak * tm) % k) * pot[n - s - 1-1]) % k;
		//for(i = s + 1; i < n; i++) printf("(6)ans[%d] += %d * %d\n", n-i, pot[n-i-1-1] * tm, ak);
		ans[s] = (ans[s] + B[s] * (vb[s + 1] + 1)) % k;
		//printf("(7)ans[%d] += %d * %d\n", n-s, vb[s+1] + 1, B[s]);
		cur = 0;
		for(i = s + 1; i < n; i++) {
			ans[i] = (ans[i] + ak * cur) % k;
			//printf("(8)ans[%d] += %d * %d\n", n-i, cur, ak);
			cur = cur + pot[n - i - 1-1] * (B[i]);
			for(d = 0; d < B[i]; d++) ans[i] = (ans[i] + d * pot[n - i-1]) % k;
			//for(d = 0; d < B[i]; d++) printf("(9)ans[%d] += %d * %d\n", n-i, pot[n-1-i], d);
			ans[i] = (ans[i] + B[i] * (vb[i + 1] + 1)) % k;
			//printf("(10)ans[%d] += %d * %d\n", n-i, vb[i + 1] + 1, B[i]);
		}
		for(i = 0; i < s; i++) ans[i] = (A[i] * (b - a + 1)) % k;
		int v = 0;
		for(i = 0; i < n; i++) v = k * v + ans[i];
		//for(i = 0; i < n; i++) printf("%d", ans[i]); putchar('\n');
		printf("%d\n", v);
	}
}
