#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int n;

void go (int n) {
	for (int i = 1; i <= n; i+=2) {
		cout << i << "A " << i+1 << "A" << endl;
		cout << i << "B " << i+1 << "B" << endl;
	}
}

int main () {
	cin >> n;

	if (n == 1) {
		cout << 2 << endl;
		cout << "1A 0X" << endl;
		cout << "1B 0X" << endl;
	} else if (n&1) {
		cout << n << endl;
		go(n-3);
		cout << n-2 << "A " << n-1 << "A" << endl;
		cout << n-2 << "B " << n << "A" << endl;
		cout << n-1 << "B " << n << "B" << endl;
	} else {
		cout << n << endl;
		go(n);
	}
}
