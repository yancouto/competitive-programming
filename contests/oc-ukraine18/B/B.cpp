#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int main() {
	int n, m, x;
	scanf("%d %d", &n, &m);
	map<int, int> ct;
	for(int i = 0; i < m; i++) {
		scanf("%d", &x);
		ct[x]++;
	}
	int dif = 0;
	int mn = 0;
	for(pii p : ct)
		mn = max(mn, p.snd),
		dif = max(dif, p.fst);
	int pos = 0;
	for(int i = 1; i * i <= n; i++) {
		if(n % i) continue;
		if(i >= dif && (n / i) >= mn) {
			pos++;
		}
		if(i * i != n && (n / i) >= dif && i >= mn) {
			pos++;
		}
	}
	if(pos == 1) puts("YES");
	else puts("NO");
}
