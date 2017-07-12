#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 103;

int t;
char bst[] = "99887766554433221100";
char str[N];
int res[N];
int cn[10];

int get (int i) {
	while (i >= 0 && !cn[i])
		i--;
	if (i >= 0)
		cn[i]--;
	return i;
}

bool isbig () {
	for (int i = 0; i < 20; i++) {
		if (str[i] > bst[i])
			return 1;
		else if (str[i] < bst[i])
			return 0;
	}
	return 0;
}

int main () {
	cin >> t;
	int bn = strlen(bst);
	assert(bn == 20);

	while (t--) {
		cin >> str;
		int n = strlen(str);

		int z = 0;
		while (str[z] == '0')
			z++;
		for (int i = z; i <= n; i++)
			str[i-z] = str[i];
		n-=z;

		if (n > bn) {
			cout << bst << endl;
		} else {
			bool done = 0;
			for (int i = n; !done && i >= (str[0] <= '1'); i--) {
				//cout << "try at " << i << endl;
				bool ok = 1;

				for (int j = 0; j < 10; j++)
					cn[j] = 2;

				for (int j = 0; ok && j < n; j++) {
					if (j < i) {
						res[j] = get(str[j]-'0');
						if (res[j] != str[j]-'0') {
							ok = 0;
							break;
						}
					} else if (j == i)
						res[j] = get(str[j]-'0'-1);
					else
						res[j] = get(9);

					//cout << res[j];

					if (res[j] < 0)
						ok = 0;
				}

				//cout << endl;

				if (ok) {
					for (int j = 0; j < n; j++) {
						cout << res[j];
					}
					cout << endl;
					done = 1;
				}
			}

			if (!done) {
				int j = 19;
				for (int i = 0; i + 1 < n; i++) {
					cout << j/2;
					j--;
				}
				cout << endl;
			}
		}
	}
}
