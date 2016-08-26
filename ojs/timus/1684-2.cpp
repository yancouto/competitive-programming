#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 75009;
char str[MAX * 2];
int z[MAX * 2];

int main() {
	int i, j;
	scanf("%s", str);
	int n = strlen(str);
	str[n] = '|';
	scanf("%s", str + n + 1);
	int tot = strlen(str);
	int r = tot - n - 2;
	int st[MAX], sn = 0; st[sn++] = r;
	int ql = 0, qr = 0;
	for(i = 1; i < tot; i++) {
		if(qr < i) {
			ql = qr = i;
			while(str[qr] == str[qr - ql]) qr++;
			z[i] = (qr--) - ql;
			continue;
		}
		if(z[i - ql] < (qr - i + 1)) { z[i] = z[i - ql]; continue; }
		ql = i;
		while(str[qr] == str[qr - ql]) qr++;
		z[i] = (qr--) - ql;
	}
	for(i = r; i >= 0; i--) {
		if(z[i + n + 1] >= r + n + 1 - (i + n + 1) + 1)
			st[sn++] = r = i - 1;
	}
	if(r >= 0) puts("Yes");
	else {
		puts("No");
		for(i = sn - 1; i > 0; i--) {
			for(j = st[i] + 1; j <= st[i-1]; j++)
				putchar(str[j - st[i] - 1]);
			if(i > 1) putchar(' ');
		}
		putchar('\n');
	}
	
}
