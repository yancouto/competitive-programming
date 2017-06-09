#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e2+2;

ll n, q, s;
int to[N];
ll siz[N];
ll amm[N];
ll cur[N];

ll cd, d;
ll a;

void fail () {
	cout << "impossible" << endl;
	exit(0);
}

int main () {
	cin >> n >> q >> s;

	for (int i = 0; i < s; i++) {
		cin >> to[i];
		to[i]--;
	}

	for (int i = 0; i < q; i++) {
		cin >> siz[i];
	}

	for (int i = 0; i < n; i++) {
		cin >> d;

		for (int j = 0; j < q; j++)
			cur[j] = 0;

		for (int j = 0; j < s; j++) {
			cin >> a;
			
			cur[to[j]] += a;
		}

		for (int j = 0; j < q; j++) {
			if (cur[j] > siz[j])
				fail();

			amm[j] += cur[j];
			ll ch = max(0ll, amm[j] - siz[j]);
			amm[j] -= ch;
			if (ch > cd)
				fail();
			cd -= ch;
		}

		cd += d;
	}

	for (int j = 0; j < q; j++) {
		cd -= amm[j];
	}

	if (cd < 0)
		fail();

	cout << "possible" << endl;
}
