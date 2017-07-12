#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

string str;

int main () {
	cin >> str;
	vector<int> v;
	int l = 0, r = 0;

	v.push_back(0);
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '<') {
			v.push_back(++r);
		} else {
			v.push_back(--l);
		}
	}

	for (int i : v) {
		cout << i - l + 1 << " ";
	}
	cout << endl;
}
