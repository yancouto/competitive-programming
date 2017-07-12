#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
ll x[N][2];
int p[2][N];
int q[2][N];

ll dist[N];
int visi[N];
set<pii> s;

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> x[i][0] >> x[i][1];

		p[0][i] = p[1][i] = i;
	}

	for (int k = 0; k < 2; k++) {
		sort(p[k], p[k]+n, [k] (int i, int j) {
			return x[i][k] < x[j][k];
		});

		for (int i = 0; i < n; i++)
			q[k][p[k][i]] = i;
	}
	
	dist[0] = 0;
	visi[0] = 0;
	s.insert(pii(0,0));

	while (!s.empty()) {
		pii cur = *(s.begin());
		s.erase(s.begin());

		ll u = cur.second;
		ll d = cur.first;
	
		if (visi[cur.second] == 2) continue;
		visi[cur.second] = 2;
		
		for (int k = 0; k <= 2; k++) {
			ll v = u, e = d;

			if (u < n) {
				if (k > 1) continue;
				v = u + n + k*n;
				e = d;
			} else if (k == 2) {
				v = u%n;
				e = d;
			} else {
				int ty = (u >= n+n);

				int i = q[ty][u%n];
				i += -1 + 2*k;
				if (i < 0 || i >= n) continue;
				v = p[ty][i] + n + ty*n;
				e = d + abs(x[u%n][ty] - x[v%n][ty]);
			}

			if (visi[v] == 2) continue;
			if (visi[v] == 1 && dist[v] <= e) continue;
			visi[v] = 1;
			dist[v] = e;
			s.insert(pii(e,v));
		}
	}

	cout << dist[n-1] << endl;
}
