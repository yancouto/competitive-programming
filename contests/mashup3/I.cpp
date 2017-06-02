#include <bits/stdc++.h>
using namespace std;
#define pb push_back

int main() {
	int i, n;
	scanf("%d", &n);
	if(n == 1) { puts("no"); return 0; }
	for(i = 2; i * i <= n && (n % i); i++);
	if(n % i) puts("yes");
	else {
		while(!(n % i)) n /= i;
		if(n > 1) puts("no");
		else puts("yes");
	}

}
