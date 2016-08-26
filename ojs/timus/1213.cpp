#include <bits/stdc++.h>
using namespace std;

char s[300];
int main() {
	set<string> se;
	scanf("%s", s);
	se.insert(s);
	while(true) {
		scanf("%s", s);
		if(s[0] == '#') { printf("%d\n", (int)se.size() - 1); return 0; }
		char *c = strchr(s, '-');
		*c = '\0';
		se.insert(s);
		se.insert(c + 1);
	}
}
