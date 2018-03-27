#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 28;

char inp[3][N];
int dec[6];
int n;

bool go (int sz) {
	int u = -1;
	for (char * v : _pre) u = v[0];
	for (char * v : _pos) u = v[sz-1];

	for (char * v : _pre) if (u != v[0]) return 0;
	for (char * v : _pos) if (u != v[sz-1]) return 0;
	assert(u != -1);
	
	int md = -1;
	for (int i = 0; i < sz; i++)

	if (sz) return 1;
}

int main () {
	for (int k = 0; k < 3; k++) scanf(" %s", inp[k]);
	n = strlen(inp[0]);
	for (int k = 0; k < 3; k++) for (int i = 0; i < n; i++) inp[k][i] -= 'A';

	for (int k = 0; k < 6; k++) dec[k] = k/2;

	do {
		int u;
		// tem q fazer varias fita aq
		if (go()) {
			for (int k = 0; k < 6; k++) printf("%s%c", nmf[dec[k]], (k==5)?'\n':' ');
			string a,b,c;
			dfs(u,a,b,c);
			printf("%s\n", a.c_str());
			printf("%s\n", b.c_str());
			printf("%s\n", c.c_str());
		}
	} while (next_permutation(dec, dec+6));
}
