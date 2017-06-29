#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e5+7;

int k;
ll n;
int p[N];
ll v[N][2];
ll inp[N][2];
ll pd[N];

int main () {
	cin >> n >> k;

	for (int i = 0; i < k; i++) {
		cin >> inp[i][0] >> inp[i][1];
		p[i] = i;
	}

	sort(p, p+k, [] (int i, int j) {
		return inp[i][1] < inp[j][1];
	});

	for (int i = 0; i < k; i++) {
		v[i][0] = inp[p[i]][0];
		v[i][1] = inp[p[i]][1];
	}

	pd[0] = v[0][1] - v[0][0] + 1;

	int l = 0;
	for (int i = 1; i < k; i++) {
		int lo = -1;
		int hi = i-1;

		while (lo < hi) {
			int mid = (lo+hi+1)/2;
			if (v[mid][1] >= v[i][0])
				hi = mid - 1;
			else
				lo = mid;
		}

		pd[i] = pd[i-1];
		pd[i] = max(pd[i], v[i][1] - v[i][0] + 1);
		if (lo != -1)
			pd[i] = max(pd[i], pd[lo] + v[i][1] - v[i][0] + 1);
	}

	cout << n - pd[k-1] << endl;
}
