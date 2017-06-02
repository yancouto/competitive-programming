#include <bits/stdc++.h>
using namespace std;

char s[1123456], o[256];

int main() {
	o['R'] = 'S';
	o['B'] = 'K';
	o['L'] = 'H';
	scanf("%s", s);
	int n = strlen(s);
	for(int i = 0; i < n;) {
		if(i + 2 < n && s[i] + s[i + 1] + s[i + 2] == 'R' + 'B' + 'L') putchar('C'), i += 3;
		else putchar(o[s[i++]]);
	}
	putchar('\n');
}
