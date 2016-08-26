#include <bits/stdc++.h>
using namespace std;

int d1[200], d2[200];
char str[200];
int main() {
	int i;
	while(scanf(" %s", str) != EOF) {
		int l = strlen(str);
		for(i = 0; i < l; i++)
			d2[i] = str[l - 1 - i] - '0';
		for(i = 0; i < 200; i++) {
			d1[i] += d2[i];
			d2[i] = 0;
			if(d1[i] >= 10) {
				d1[i] -= 10;
				d1[i + 1]++;
			}
		}
	}
	for(i = 200; i >= 0 && d1[i] == 0; i--);
	if(i < 0) putchar('0');
	else
		while(i >= 0)
			putchar(d1[i--] + '0');
	putchar('\n');
	return 0;
}
