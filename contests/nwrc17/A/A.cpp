#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 53;

char str[N];

int memo[N][500];

int pd (int i, char c) {
	if (c > 'z')
		return 0;
	if (!str[i])
		return pd(i, c+1) + 1;

	int & me = memo[i][c];
	
	if (me != -1)
		return me;
	me = min(pd(i+1, c), pd(i, c+1) + (str[i] != c));
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	cin >> str;
	cout << pd(0,'a') << endl;
}
