#include <bits/stdc++.h>
using namespace std;

char s[1123456];

int main() {
	scanf("%s", s);
	int mx = 0, cur = 0, h = 0;
	for(int i = 0; s[i]; i++) {
		if(s[i] == 'M') cur++;
		else if(s[i] ==  'K') h--;
		else h++;
		if(h < 0) cur = 0, h = 0;
		mx = max(mx, cur);
	}
	printf("%d\n", mx);
}
