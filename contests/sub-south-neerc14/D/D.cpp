#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 102;

int t, n;
int ans[N];
int fin[N];
int qt[2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> t;
	while (t--) {
		cin >> n;
		qt[0] = qt[1] = 0;
	
		for (int i = 1; i <= n; i++) {
			cout << "1\n" << i << endl;
			cout.flush();
			cin >> ans[i];
			qt[ans[i]]++;
		}

		for (int i = 1; i <= n; i++) {
			if (ans[i] == 0) {
				cout << qt[1] + 1 << "\n";
				for (int j = 1; j <= n; j++) {
					if (ans[j] == 1 || j == i)
						cout << j << " ";
				}
				cout << endl;
				cout.flush();

				int x;
				cin >> x;
				if (x == qt[1] + 1)
					fin[i] = -1;
				else
					fin[i] = 0;
			} else {
				cout << qt[0] + 1 << "\n";
				for (int j = 1; j <= n; j++) {
					if (ans[j] == 0 || j == i)
						cout << j << " ";
				}
				cout << endl;
				cout.flush();

				int x;
				cin >> x;
				if (x == 0)
					fin[i] = -1;
				else
					fin[i] = 1;
			}
		}

		cout << "-1\n";
		for (int i = 1; i <= n; i++) {
			if (i != 1)
				cout << " ";
			if (fin[i] == 1)
				cout << 1;
			else if (fin[i] == 0)
				cout << 2;
			else
				cout << 3;
		}
		cout << endl;
		cout.flush();
	}

}
