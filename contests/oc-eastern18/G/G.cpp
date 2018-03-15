#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = (1<<9);

int memo[M][M]; // 0: draw, 1: win, 2: lose
pii win[M][M];

bool winning (int a) {
	for (int i = 0; i < 3; i++) {
		int j = 0;
		for (; j < 3; j++)
			if ((a&(1<<(i*3+j))) == 0) break;
		if (j == 3) return true;
	}
	for (int j = 0; j < 3; j++) {
		int i = 0;
		for (; i < 3; i++)
			if ((a&(1<<(i*3+j))) == 0) break;
		if (i == 3) return true;
	}
	int i = 0;
	for (; i < 3; i++)
		if ((a&(1<<(i*3+i))) == 0) break;
	if (i == 3) return true;
	i = 0;
	for (; i < 3; i++)
		if ((a&(1<<(i*3+2-i))) == 0) break;
	if (i == 3) return true;
	return false;
}


int dp (int a, int b) {
	assert(!(a&b));
	int & me = memo[a][b];
	if (me != -1) return me;
	if (winning(b)) return me = 2;
	if (winning(a)) return me = 1;
	me = 2;
	int cn = 0;
	for (int i = 0; me != 1 && i < 3; i++) {
		for (int j = 0; me != 1 && j < 3; j++) {
			if (((a+b)&(1<<(i*3+j)))) continue;
			cn++;
			int ret = dp(b,a+(1<<(i*3+j)));
			if (ret != 1) win[a][b] = pii(i,j);
			if (ret == 2) me = 1;
			else if (ret == 0) me = 0;
		}
	}
	if (!cn && me == 2) me = 0;
	return me;
}

int turn;

int main () {
	memset(memo, -1, sizeof memo);
	char c;
	scanf(" %c", &c);
	if (c == 'X') turn = 1;

	int a = 0, b = 0;
	
	while (true) {
		int i, j;
		if (turn) {
			if (a + b == M-1) break;
			dp(a,b);
			i = win[a][b].first; j = win[a][b].second;
			printf("%d %d\n", i+1, j+1);
			fflush(stdout);
			a += (1<<(i*3+j));
		} else {
			if (scanf("%d %d", &i, &j) != 2) break;
			i--; j--;
			b += (1<<(i*3+j));
		}
		turn = !turn;
	}
}
