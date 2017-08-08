#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 2e5+7;

ll n, d, a, b;
ll v[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> d >> a >> b;
	ll ty = 0, k = 0;
	ll s = 0;
	ll qt;

	for (int i = 0; i < n; i++)
		cin >> v[i];

	for (int i = 1; i < n; i++) {
		if (v[i-1] < v[i]) {
			if (ty == 1)
				k++;
			else
				k = ty = 1;
			qt = min(k*a, d/v[i]);
			s += qt;
			d -= qt*v[i];
		} else if (v[i-1] > v[i]) {
			if (ty == -1)
				k++;
			else {
				k = 1;
				ty = -1;
			}
			qt = min(k*b, s);
			s -= qt;
			d += qt*v[i];
		} else {
			ty = 0;
			k = 0;
		}
	}

	cout << d << " " << s << endl;
}
