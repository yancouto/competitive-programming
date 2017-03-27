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

const int N = 112;
int in[N], seen[N], t;
int c[N][N];
map<int, int> S[N];


int main() {
	int i, j, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &c[i][j]);
		for(i = 0; i < n; i++) in[i] = 1, S[i].clear();
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(i != j)
					S[i][c[i][j]]++;
		while(true) {
			for(i = 0; i < n; i++) {
				if(!in[i] || S[i].size() >= 2) continue;
				in[i] = 0;
				for(j = 0; j < n; j++)
					if(i != j && in[j]) {
						if((--S[j][c[i][j]]) == 0)
							S[j].erase(c[i][j]);
					}
				break;
			}
			if(i == n) break;
		}
		printf("%d\n", accumulate(in, in + n, 0));
	}
}
