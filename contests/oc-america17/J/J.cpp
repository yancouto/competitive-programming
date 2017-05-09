#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 1e5+7;

char str[N];

int main () {
	scanf(" %s", str);

	int n = strlen(str);

	int w = 0, b = 0;
	for (int i = 0; i < n; i++)
		if (str[i] == 'W')
			w++;
		else
			b++;

	int aw = 0, ab = 0;
	int r = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == 'W')
			aw++;
		else
			ab++;

		if (aw + 1 == ab && w - aw == b - ab + 1)
			r = 1;
		if (ab + 1 == aw && b - ab == w - aw + 1)
			r = 1;
	}
	printf("%d\n", r);
}
