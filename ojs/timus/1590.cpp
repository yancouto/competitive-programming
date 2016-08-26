#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
char str[5009];
int z[5009], mxz[5009];

int main() {
	int i, n, j;
	scanf("%s", str);
	n = strlen(str);
	int tot = n;
	for(i = 0; i < n - 1; i++) {
		int l = 0, r = 0;
		for(j = i + 1; j < n; j++) {
			if(j > r) {
				l = r = j;
				while(str[r] == str[r - l + i]) r++;
				z[j] = (r--) - l;
			} else {
				if(z[j - l + i] < (r - j + 1)) z[j] = z[j - l + i];
				else {
					l = j;
					while(str[r] == str[r - l + i]) r++;
					z[j] = (r--) - l;
				}
			}
			mxz[j] = max(mxz[j], z[j]);
		}
		tot += n - i - 1 - mxz[i + 1];
	}
	printf("%d\n", tot);
	return 0;
}
