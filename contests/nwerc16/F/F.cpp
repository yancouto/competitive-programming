#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e6+2;

int n;
int w[2][N];

ll solve (ll x) {
	for (int j = 0; j < 2; j++) {
		ll ls = -1;
		for (int i = 0; i < n; i++) {
			if (w[j][i] <= x) continue;
			if (ls == w[j][i])
				ls = -1;
			else if (ls == -1)
				ls = w[j][i];
			else
				return 0;
		}
		if (ls != -1)
			return 0;
	}

	return 1;
}

int main () {
	cin >> n;
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < n; i++)
			cin >> w[j][i];

	ll lo = 0, hi = 1e9;

	while (lo < hi) {
		ll mid = (lo + hi)/2;

		if (solve(mid))
			hi = mid;
		else 
			lo = mid+1;
	}

	cout << lo << endl;

}
