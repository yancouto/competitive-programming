#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 3e5+7;

vector<pii> rs;
int v[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int ls = 0;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i];

	while (ls < n) {
		int i, ps;
		for (i = ls, ps = 1; i < n && v[i] >= ps; i++, ps++);

		int mx = n;
		for (int j = ls; j < mx; j++)
			mx = min(mx, j + v[j]);

		int nx = max(mx,i);
		if (i == nx)
			rs.pb(pii(ls+1,nx));
		else
			rs.pb(pii(nx,ls+1));

		ls = nx;
	}

	cout << rs.size() << endl;
	for (pii a : rs)
		cout << a.first << " " << a.second << endl;


}
