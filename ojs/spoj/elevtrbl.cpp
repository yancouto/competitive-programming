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

int di[1123456];

int main() {
	int f, s, g, u, d;
	scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
	queue<int> q;
	q.push(s);
	for(int i = 0; i <= f; i++) di[i] = INT_MAX;
	di[s] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(x == g) {
			printf("%d\n", di[x]);
			return 0;
		}
		if(x + u <= f && di[x + u] == INT_MAX) {
			di[x + u] = di[x] + 1;
			q.push(x + u);
		}
		if(x - d > 0 && di[x - d] == INT_MAX) {
			di[x - d] = di[x] + 1;
			q.push(x - d);
		}
	}
	puts("use the stairs");
}
