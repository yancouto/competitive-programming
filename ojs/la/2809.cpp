#include <cstdio>
#include <cstdlib>
#include <cstring>

char a[2][12];
int memo[2][10][2][2][10][10];
int solve(int n, int d, bool prev, bool init, int num, int dig) {
	if(!a[n][d]) return num;
	int &m = memo[n][d][prev][init][num][dig];
	if(m != -1) return m;
	m = 0;
	for(int i = 0; i <= 9; i++) {
		if(prev && i > (a[n][d] - '0'))
			break;
		m += solve(n, d + 1, prev && i == (a[n][d] - '0'), init && !i, num + (i == dig && (dig || !init)), dig);
	}
	return m;
}

int main() {
	int i;
	while(true) {
		scanf(" %s %s", a[1], a[0]);
		if(a[0][0] == '0' && a[0][1] == '\0') return 0;
		sprintf(a[1], "%d", atoi(a[1]) - 1);
		memset(memo, -1, sizeof memo);
		printf("%d", solve(0, 0, true, true, 0, 0) - solve(1, 0, true, true, 0, 0));
		for(i = 1; i <= 9; i++)
			printf(" %d", solve(0, 0, true, true, 0, i) - solve(1, 0, true, true, 0, i));
		putchar('\n');
	}
}