#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 207;
int t;

char str[N];
int memo[6][N][N];

int pd (int t, int i, int j) {
	int & me = memo[t][i][j];
	if (me != -1)
		return me;
	
	if (t == 0) { // set
		if (i < j && str[i] == '{' && str[j] == '}')
			me = pd(1, i+1, j-1);
		else
			me = 0;
	} else if (t == 1) { // elementlist
		if (j + 1 == i) me = 1;
		else me = pd(2, i, j);
	} else if (t == 2) { // list
		me = pd(3, i, j);
		for (int k = i; !me && k <= j; k++)
			me = ((str[k] == ',') && pd(3, i, k-1) && pd(2, k+1, j));
	} else if (t == 3) { // element
		me = (pd(4, i, j) || pd(0, i, j));
	} else if (t == 4) { // atom
		me = ((i == j) && (str[i] == '{' || str[i] == '}' || str[i] == ','));
	}
	//cout << t << " " << i << " " << j << " : " << me << endl;
	return me;
}

int main () {
	cin >> t;

	for (int ts = 1; ts <= t; ts++) {
		cin >> str;
		int n = strlen(str)-1;

		memset(memo, -1, sizeof memo);
		cout << "Word #" << ts << ": ";
		if (pd(0, 0, n))
			cout << "Set" << endl;
		else
			cout << "No Set" << endl;
	}

}
