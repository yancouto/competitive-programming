#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

const int mv[4][2] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

char ** mat;
int ** mrk[2][2];
int * sm[2][2];
bool ** res;
int n, m, k;
string cm[N];
ll qt[N];
ll cnt;

int getdir (int i) {
	if (cm[i][0] == 'u')
		return 0;
	if (cm[i][0] == 'r')
		return 1;
	if (cm[i][0] == 'd')
		return 2;
	if (cm[i][0] == 'l')
		return 3;
	assert(false);
}

void printa () {
	cout << "=============" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (res[i][j])
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;

	for (int a = 0; a < 2; a++) {
	for (int b = 0; b < 2; b++) {
		cout << endl;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				cout << mrk[a][b][i][j] << " ";
			}
			cout << endl;
		}
	}
	}
}

void add (int p, int d, ll & i, ll & j, ll k) {
	if (d == 0) { // up
		mrk[p][0][i+1][j]--;
		mrk[p][0][i-k][j]++;
	} else if (d == 1) { // right
		mrk[p][1][i][j]++;
		mrk[p][1][i][j+k+1]--;
	} else if (d == 2) { // down
		mrk[p][0][i][j]++;
		mrk[p][0][i+k+1][j]--;
	} else { // left
		mrk[p][1][i][j+1]--;
		mrk[p][1][i][j-k]++;
	}

	//cout << p << " from " << i << "," << j << " : ";

	i += mv[d][0]*k;
	j += mv[d][1]*k;
	//cout << i << "," << j << endl;
}

ll solve (ll x) {
	for (int a = 0; a < 2; a++) {
		for (int i = 0; i < n; i++)
			sm[a][1][i] = 0;
		for (int j = 0; j < m; j++)
			sm[a][0][j] = 0;
		for (int b = 0; b < 2; b++) {
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= m; j++)
					mrk[a][b][i][j] = 0;
		}
	}
	

	ll i = n-1;
	ll j = 0;

	ll y = 0;
	bool p = 1;
	for (int z = 0; z < k; z++) {
		int d = getdir(z);
		if (p && y + qt[z] >= x) {
			add(1, d, i, j, x - y);
			add(0, d, i, j, y + qt[z] - x);
			p = 0;
		} else {
			add(p, d, i, j, qt[z]);
		}

		y += qt[z];
	}

	ll c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int a = 0; a < 2; a++) {
				sm[a][0][j] += mrk[a][0][i][j];
				sm[a][1][i] += mrk[a][1][i][j];
			}
			res[i][j] = (!sm[0][0][j] && !sm[0][1][i] && (sm[1][0][j] || sm[1][1][i]));
			c += res[i][j];
		}
		//cout << endl;
	}
	//printa();
	return c;
}

ll bb (ll lo, ll hi, ll x) {
	ll cc = 0;

	while (lo < hi) {
		ll md = (lo+hi)/2;

		if (solve(md) < x)
			lo = md + 1;
		else
			hi = md;
	}

	return lo;
}

void fail () {
	cout << "-1 -1" << endl;
	exit(0);
}

int main () {
	cin >> n >> m >> k;

	mat = new char*[n+2];
	for (int i = 0; i < n+2; i++)
		mat[i] = new char[m+2];

	res = new bool*[n+2];
	for (int i = 0; i < n+2; i++)
		res[i] = new bool[m+2];

	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			mrk[a][b] = new int*[n+2];
			for (int i = 0; i < n+2; i++)
				mrk[a][b][i] = new int[m+3];
			sm[a][b] = new int[n+m];
		}
	}

	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mat[i][j];
			if (mat[i][j] == '#')
				cnt++;
		}
	}

	ll qtd = 1;
	for (int i = 0; i < k; i++) {
		cin >> cm[i] >> qt[i];
		qtd += qt[i];
	}
	
	ll l = bb(0, qtd, cnt);
	ll r = bb(l, qtd, cnt+1);

	solve(l);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((mat[i][j] == '#') != res[i][j])
				fail();
		}
	}
	//printa();
	cout << l << " " << max(l,r-1) << endl;
}
