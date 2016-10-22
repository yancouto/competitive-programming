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
const int N = 112345;
map<char, int> adj[N];
int F[N], mn[N], mx[N], en = 2;
char s[N];

int main() {
	scanf("%s", s);
	int last = 1, i;
	for(i = 0; s[i]; i++) {
		char c = s[i];
		int n = en++;
		int p = last;
		mx[n] = mx[last] + 1;
		while(!adj[p].count(c)) {
			adj[p][c] = n;
			mn[n] = mn[p] + 1;
			p = F[p];
		}
		if(!p) F[n] = 1;
		else {
			int y = adj[p][c];
			if(mx[y] == mx[p] + 1) F[n] = y;
			else {
				int x = en++;
				mx[x] = mx[p] + 1;
				mn[y] = mx[x] + 1;
				adj[x] = adj[y];
				F[x] = F[y];
				F[y] = F[n] = x;
				while(adj[p].count(c) && adj[p][c] == y) {
					adj[p][c] = x;
					mn[x] = mn[p] + 1;
					p = F[p];
				}
			}
		}
		last = n;
	}
	int tot = 0;
	for(i = 2; i < en; i++)
		tot += mx[i] - mn[i] + 1;
	printf("%d\n", tot);
}
