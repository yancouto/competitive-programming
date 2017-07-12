#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int st[512345], sn;

int main() {
	int i, n, x;
	scanf("%d", &n);
	sn = 0;
	int tot = 0;
	for(i = 0; i < n; i++) {
		scanf("%*d %d", &x);
		while(sn > 0 && st[sn - 1] > x) sn--;
		if(sn && st[sn - 1] == x) continue;
		tot++;
		st[sn++] = x;
	}
	printf("%d\n", tot);
}
