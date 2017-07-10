#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

ll c[4], t[4], r[4];

int main () {
	for (int i = 0; i < 3; i++) {
		cin >> c[i];
		c[i] += c[i];
	}
	
	cin >> t[3] >> t[1];
	t[3] += t[3]; t[1] += t[1];

	sort(c, c+3);

	do {
		//cout << "====" << endl;
		//cout << c[0] << " " << c[1] << " " << c[2] << endl;
		for (int i = 0; i <= c[0]; i++) {
			for (int j = i; j <= i + c[1] || j <= c[0]; j++) {
				r[1] = r[2] = r[3] = 0;
				for (int k = 0; k <= j + c[2] || k <= i + c[1] || k <= c[0]; k++) {
					int q = 0;
					q += (k < c[0]);
					q += (i <= k && k < i + c[1]);
					q += (j <= k && k < j + c[2]);
					r[q]++;
				}
				//cout << r[1] << " " << r[2] << " " << r[3] << endl;

				if (r[1] == t[1] && r[3] == t[3]) {
					cout << (r[2]/2);
					if (r[2]&1)
						cout << ".5";
					cout << endl;
					return 0;
				}
			}
		}
	} while (next_permutation(c,c+3));
}
