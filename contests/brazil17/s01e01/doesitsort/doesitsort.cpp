#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 403;

int n;
string cm;
int v[N][3];

void printit (int a) {
	for (int i = 0; i < 20; i++)
		cout << !!(a&(1<<i)) << " ";
	cout << endl;
}

int main () {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cm >> v[i][1] >> v[i][2];
		v[i][0] = (cm[0] == 's');
	}

	for (int vl = 0; vl < (1<<20); vl++) {
		int cr = vl;

		//cout << "=================" << endl;
		//printit(cr);
		
		for (int i = 0; i < n; i++) {
			if (v[i][0]) {
				int neg = (1<<20) - 1;
				neg -= (1<<v[i][2]) - 1;
				neg += (1<<v[i][1]) - 1;

				int pos = (1<<v[i][2]) - 1;
				pos -= (1<<v[i][1]) - 1;

				int c = __builtin_popcount(cr&pos);
				int nw = (1<<c) - 1;
				nw <<= v[i][2] - c;

				cr = ((cr&neg)|nw);
			} else {
				if ((cr&(1<<v[i][1])) && !(cr&(1<<v[i][2]))) {
					cr -= (1<<v[i][1]);
					cr += (1<<v[i][2]);
				}
			}
			//printit(cr);
		}

		bool ok = 1;
		for (int i = 1; ok && i < 20; i++) {
			ok &= !((cr&(1<<(i-1))) && !(cr&(1<<i)));
		}

		if (!ok) {
			cout << "incorrect" << endl;
			for (int i = 0; i < 20; i++)
				cout << !!(vl&(1<<i)) << " ";
			cout << endl;
			return 0;
		}
	}

	cout << "correct" << endl;
}
