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

void go(int p[], int n) {
	for(int i = 0; i < n; i++)
		printf("%d%c", p[i], " \n"[i == n - 1]);
}

int a[100], p[100];
int main() {
	int i, j, k, n;
	bool b = false; int t = 0;
	while(scanf("%d", &n) != EOF && n) {
		if(b) putchar('\n');
		b = true;
		printf("Run %d n=%d\n", ++t, n);
		int tot = 1;
		for(i = 1; i <= n; i++) tot *= i, a[i-1] = i;
		go(a, n);
		for(i = 0; i < tot - 1; i++) {
			for(j = n - 2; a[j] > a[j + 1]; j--);
			int mn = -1;
			for(k = j + 1; k < n; k++)
				if(a[k] > a[j] && (mn == -1 || a[mn] > a[k]))
					mn = k;
			swap(a[j], a[mn]);
			sort(a + j + 1, a + n);
			go(a, n);
		}
	}
}
