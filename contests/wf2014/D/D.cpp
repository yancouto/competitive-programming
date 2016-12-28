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

const int N = 25;
const int Q = 1123456;
const int M = (1<<25);


vector<int> adj[N];
int to[M];

char str[N+4];

queue<int> qu;

int n, m, q;
char res[N][N];
char dist[N];

int en = 1;


template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
}

int main () {
	rd(n);

	for (int i = 0; i < n; i++) {
		rd(q);

		for (int j = 0; j < q; j++) {
			while(!isalpha(str[0] = getchar()));
			int ct = 1;
			while(isalpha(str[ct++] = getchar()));
			str[ct-1] = 0;
			int mask = 0;
			for (int k = 0; str[k]; k++) 
				mask |= (1<<(str[k]-'a'));

			for (int k = 0; str[k]; k++) {
				adj[str[k]-'a'].push_back(mask);
			}
			to[mask] |= (1<<i);
		}
	}

	for (int i = 0; i < n; i++) {
		while (!qu.empty()) qu.pop();
		int out = ((1 << n) - 1), o2 = ((1 << n) - 1);
		out ^= (1 << i);

		for (int j = 0; j < n; j++)
			dist[j] = 30;
		dist[i] = 0;

		qu.push(i);

		while (!qu.empty()) { 
			int u = qu.front();
			o2 ^= (1 << u);
			qu.pop();

			for (int j : adj[u]) {

				if (j & o2) continue;

				int ne = (to[j] & out);

				while(ne) {
					int v = __builtin_ctz(ne);
					dist[v] = dist[u] + 1;
					qu.push(v);
					ne ^= (1 << v);
					out ^= (1 << v);
				}
			}
		}

		for (int j = 0; j < n; j++)
			res[j][i] = dist[j];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (res[i][j] == 30)
				printf("-1 ");
			else
				printf("%d ", res[i][j]);
		}
		printf("\n");
	}
}
