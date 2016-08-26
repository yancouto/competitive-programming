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
int modn;
inline int mod(int x) { return x % modn; }
int fexp(int x, int p) {
	int resp = 1;
	for(int i = 1; i <= p; i <<= 1) {
		if(i & p) resp = mod(resp * x);
		x = mod(x * x);
	}
	return resp;
}
int a[102][102], b[102];
int n, p;

void deb() {
	return;
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			printf("%d ", a[i][j]);
		printf("= %d\n", b[i]);
	}
	puts("--------------------------");
}

int main() {
	int i, j, jj, s, t, tn = 0;
	while(scanf("%d %d", &n, &p) != EOF) {
		modn = p;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &s, &t);
			b[i] = mod(t - s + 1 + p);
			for(j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
				a[i][j] = mod(a[i][j]);
			}
		}
		deb();
		bool pos = true;
		for(j = 0; j < n; j++) {
			for(i = j; i < n && a[i][j] == 0; i++);
			if(i == n) { pos = false; continue; }
			if(i != j) {
				for(jj = 0; jj < n; jj++)
					swap(a[j][jj], a[i][jj]);
				swap(b[j], b[i]);
			}
			int inv = fexp(a[j][j], p - 2);
			for(i = j + 1; i < n; i++) {
				if(a[i][j] == 0) continue;
				int div = mod(inv * (p - a[i][j]));
				for(jj = j; jj < n; jj++)
					a[i][jj] = mod(a[i][jj] + div * a[j][jj]);
				b[i] = mod(b[i]  + div * b[j]);
			}
		}
		for(j = 0; j < n; j++) {
			if(a[j][j] == 0) continue;
			int inv = fexp(a[j][j], p - 2);
			for(i = j - 1; i >= 0; i--) {
				if(a[i][j] == 0) continue;
				int div = mod(inv * (p - a[i][j]));
				for(jj = j; jj < n; jj++)
					a[i][jj] = mod(a[i][jj] + div * a[j][jj]);
				b[i] = mod(b[i]  + div * b[j]);
			}
		}
		deb();
		for(i = 0; i < n; i++) {
			for(j = 0; j < n && a[i][j] == 0; j++);
			if(j == n && b[i]) break;
		}
		if(i < n) { puts("-1"); continue; }
		if(!pos)  { puts("-2"); continue; }
		for(j = n - 1; j >= 0; j--) {
			b[j] = mod(b[j] * fexp(a[j][j], p - 2));
			for(i = j - 1; i >= 0; i--)
				b[i] = mod(b[i] - mod(b[j] * a[i][j]) + p);
		}
		printf("%d", b[0]? b[0] : p);
		for(i = 1; i < n; i++)
			printf(" %d", b[i]? b[i] : p);
		putchar('\n');
	}
	return 0;
}
