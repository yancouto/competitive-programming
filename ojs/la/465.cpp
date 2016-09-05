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
int pr[100], p[100], n;
int us[100];

void solve(int i) {
	if(i == n) {
		if(!pr[p[0] + p[n - 1]]) return;
		printf("1");
		for(i = 1; i < n; i++)
			printf(" %d", p[i]);
		printf("\n");
		return;
	}
	for(int g = 2; g <= n; g++)
		if(!us[g] && pr[p[i-1] + g]) {
			us[g] = true; p[i] = g;
			solve(i + 1);
			us[g] = false;
		}
}

int main() {
	int i, j;
	for(i = 2; i < 50; i++) {
		for(j = 2; j < i && (i % j); j++);
		if(j == i) pr[i] = 1;
	}
	int tt = 0;
	p[0] = 1; us[1] = true;
	while(scanf("%d", &n) != EOF) {
		if(tt) printf("\n");
		printf("Case %d:\n", ++tt);
		solve(1);
	}
}
