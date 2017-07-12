#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
pii v[N];

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> v[i].first;
		v[i].second = i;
	}

	sort(v, v+n);

	ll cur = -1;
	ll res = 0;

	for (int i = 0; i < n; i++) {
		if (v[i].second < cur)
			continue;
		res += (v[i].second - cur)*v[i].first;
		cur = v[i].second;
	}
	cout << res << endl;
}
