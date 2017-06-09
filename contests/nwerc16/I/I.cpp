#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5+7;

int n;
int q[2];
queue<int> qu[3];
vector<int> adj[2][N];

ll dist[3][N];

int main () {
	cin >> n >> q[0] >> q[1];

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < n; i++)
			dist[j][i] = INT_MAX;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < q[j]; i++) {
			int a;
			cin >> a;
			a--;

			qu[j].push(a);
			dist[j][a] = 0;
		}
	}

	dist[2][0] = 0;
	qu[2].push(0);

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int x;
			cin >> x;
			x--;
			adj[0][i].push_back(x);
			adj[1][x].push_back(i);
		}

	}

	for (int j = 0; j < 3; j++) {
		while (!qu[j].empty()) {
			int u = qu[j].front();
			qu[j].pop();

			for (int x : adj[j!=2][u]) {
				if (dist[j][x] <= dist[j][u] + 1) 
					continue;

				dist[j][x] = dist[j][u] + 1;
				qu[j].push(x);
			}
		}
	}

	ll res = INT_MAX;
	for (int i = 0; i < n; i++) {
		ll loc = 0;
		for (int j = 0; j < 3; j++) {
			loc += dist[j][i];
		}
		res = min(res, loc);
	}

	if (res == INT_MAX)
		cout << "impossible" << endl;
	else
		cout << res << endl;
}
