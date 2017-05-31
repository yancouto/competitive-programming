#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int main() {
	for_tests(t, tt) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 0; i < m; i++) scanf("%*d %*d");
		if(n & 1) puts("no");
		else puts("yes");
	}
}
