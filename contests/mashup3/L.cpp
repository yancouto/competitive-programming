#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;

ll h[112345];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld", &h[i]);
	sort(h, h + n);
	for(i = 2; i < n; i++)
		if(h[i] < h[i - 1] + h[i - 2]) {
			puts("possible");
			return 0;
		}
	puts("impossible");
}
