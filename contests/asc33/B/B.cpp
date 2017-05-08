#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = (1<<26);

bitset<N> s;
char str[11][6];

int main () {
	freopen("beavers.in", "r", stdin);
	freopen("beavers.out", "w", stdout);

	int n = N/2;
	char c = 'A';

	for (int i = 0; i < 10; i++) {
		scanf(" %s", str[i]);
	}
	int I = 0;

	while (c != 'H' && n >= 0 && n < N && (I++ % 20000 || clock() < 1.4 * CLOCKS_PER_SEC)) {
		int p = (2*(c-'A') + s[n]);
		s[n] = int(str[p][0] - '0');
		if (str[p][1] == 'R')
			n++;
		else
			n--;

		c = str[p][2];
	}

	if (c == 'H')
		printf("happy beaver\n");
	else
		printf("unhappy beaver\n");
}
