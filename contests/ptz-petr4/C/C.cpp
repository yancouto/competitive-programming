#include <bits/stdc++.h>
using namespace std;
#define cout if (0) cout

typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

int n, m;
ll inp[N][N];
int mat[N][N];
map<ll,int> mp;
vector<int> adj[N*N];
int ded[N*N];
int viz[N*N];
int col[N*N];
int p[N*N];

int main () {
#ifdef ONLINE_JUDGE
	freopen("control.in", "r", stdin);
	freopen("control.out", "w", stdout);
#endif
	
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%lld", &inp[i][j]);
			int & vl = mp[inp[i][j]];
			if (!vl)
				vl = mp.size();
			mat[i][j] = vl;
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] != mat[0][j]) {
				adj[mat[i][j]].pb(mat[0][j]);
				adj[mat[0][j]].pb(mat[i][j]);
				cout << mat[i][j] << " " << mat[0][i] << endl;
				break;
			}
		}
	}

	queue<int> qu;
	for (int i = 1; i <= mp.size(); i++) {
		viz[i] = adj[i].size();
		if (viz[i] <= 50)
			qu.push(i);
	}

	int k = 0;
	while (!qu.empty()) {
		int i = qu.front();
		p[k++] = i;
		ded[i] = 1;
		qu.pop();
		for (int j : adj[i]) {
			if (ded[j]) continue;
			viz[j]--;
			if (viz[j] == 50)
				qu.push(j);
		}
	}

	set<int> s;
	for (int i = 1; i <= 51; i++)
		s.insert(i);

	for (int _i = mp.size() - 1; _i >= 0; _i--) {
		int i = p[_i];
		cout << i << endl;

		for (int j : adj[i])
			s.erase(col[j]);
		col[i] = *s.begin();
		for (int j : adj[i])
			if (col[j])
				s.insert(col[j]);
	}

	printf("Yes\n");
	for (auto el : mp)
		printf("%lld -> %d\n", el.first, col[el.second] - 1);
}

