#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;


int main () {
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j <= 300; j++)
			S[j][i] = i, sz[j][i] = 1;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf("%d", &c[i][j]);
			join(c[i][j], i, j);
		}
	for(i = 0; i < n; i++)
		for(j = 0; j <= 300; j++) {
			if(find(j, i) == 1) continue;
		}
}
