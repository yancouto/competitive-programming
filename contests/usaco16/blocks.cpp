#include <bits/stdc++.h>
using namespace std;

int oc[2][30], all[112];
char s[2][112];

int main() {
	int i, j, k, n;
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s %s", s[0], s[1]);
		for(j = 0; j < 26; j++) oc[0][j] = oc[1][j] = 0;
		for(k = 0; k < 2; k++)
			for(j = 0; s[k][j]; j++)
				oc[k][s[k][j] - 'a']++;
		for(j = 0; j < 26; j++)
			all[j] += max(oc[0][j], oc[1][j]);
	}
	for(i = 0; i < 26; i++)
		printf("%d\n", all[i]);
}
