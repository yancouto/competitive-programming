#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
#define double long double

const int N = 1e3;

double x, t, y;
int n;
double w[N], f[N];

int main () {
	cin >> x >> y;
	cin >> n;

	for (int i = 0; i < n; i++) {
		double l, r;
		cin >> l >> r;
		w[i] = r-l;
		cin >> f[i];

		y += (f[i] - 1.) * w[i];
	}

	cout << setprecision(20) << (x / y) << endl;
}

