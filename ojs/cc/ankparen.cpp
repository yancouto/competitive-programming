#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

char par[100009];
int p[100009];

void prn(int a) {
	for(int i = 0; par[i]; i++)
		if(i != a)
			putchar(par[i]);
	putchar('\n');
}

bool valid() {
	int open = 0;
	for(int i = 0; par[i]; i++) {
		if(par[i] == '(') open++;
		else if(par[i] == ')') open--;
		if(open < 0) return false;
	}
	return open == 0;
}

int main() {
	int t, i, j; scanf("%d", &t);
	while(t--) {
		int k;
		scanf(" %s %d", par, &k);
		if(!valid()) {
			if(k == 1) prn(-1);
			else puts("-1");
			continue;
		}
		p[0] = 0;
		for(i = j = 1; par[i]; i++)
			if(par[i] != par[p[j - 1]])
				p[j++] = i;
		if(k > j) { puts("-1"); continue; }
		if(k <= j / 2) prn(p[k * 2 - 1]);
		else prn(p[j - (k - j/2) * 2]);
	}
}