#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct st {
	int i;
	int f;
	ll d;
	bool operator < (const st &o) const { return d > o.d; }
};


const int inf = 1000000007;

const int N = 1123;
int ps[N], pn;
int p[N];
int d[N][N];
int seen[129][112345];
int dist[129][112345];
int mp[N];

bool is[N];

int main() {
	int T;
	scanf("%d", &T); T++;
	int n, m, s, t, i, j, k;
	while(--T >= 1) {
		scanf("%d %d %d %d", &n, &m, &s, &t);
		for(i = 0; i < n; i++) is[i] = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				d[i][j] = inf * (i != j);
		for(i = 0; i < m; i++) {
			int a, b, f;
			scanf("%d %d %d", &a, &b, &f); a--; b--;
			d[a][b] = d[b][a] = min(d[a][b], f);
		}
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		pn = 0;
		for(i = 0; i < s; i++) {
			int x;
			scanf("%d", &x); x--;
			is[x] = 1;
			scanf("%d", &p[x]);
			mp[x] = pn;
			ps[pn++] = x;
		}
		int C, D;
		scanf("%d %d", &C, &D); C--; D--;
		if(!is[D]) {
			is[D] = 1;
			mp[D] = pn;
			ps[pn++] = D;
		}
		//for(i = 0; i < n; i++)
		//	for(j = 0; j < n; j++)
		//		printf("%d%c", d[i][j], " \n"[j == n - 1]);

		priority_queue<st> pq;
		pq.push({C, 0, 0});
		while(!pq.empty()) {
			st x = pq.top(); pq.pop();
			if(seen[mp[x.i]][x.f] == T) continue;
			seen[mp[x.i]][x.f] = T;
			//printf("(%d, %d) with %lld moniz\n", x.i, x.f, x.d);
			if(x.i == D) {
				printf("%lld\n", x.d);
				break;
			}
			if(x.f < t && seen[mp[x.i]][x.f + 1] != T) pq.push({x.i, x.f + 1, x.d + ll(p[x.i])});
			for(i = 0; i < pn; i++) {
				j = ps[i];
				int c = d[x.i][j];
				if(c > x.f) continue;
				if(seen[mp[j]][x.f - c] == T) continue;
				pq.push({j, x.f - c, x.d});
			}
		}
	}
}
