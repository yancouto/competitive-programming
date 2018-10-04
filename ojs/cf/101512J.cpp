#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int maze[230][105];

int di[] = {  0, -1,  0, +1};
int dj[] = { +1,  0, -1,  0};
char s[112345];

int main() {
	int t;
	scanf("%d", &t);
	printf("%d\n", t);
	while(t--) {
		scanf("%s", s);
		int i = 105, j = 0;
		int mn_i = 105, mx_i = 105;
		int mx_j = 0;
		int dir = 0;
		memset(maze, 0, sizeof maze);
		maze[i][j] = 1;
		for(char c : string(s)) {
			if(c == 'L') dir = (dir + 1) % 4;
			if(c == 'R') dir = (dir + 3) % 4;
			if(c == 'B') dir = (dir + 2) % 4;
			i += di[dir]; j += dj[dir];
			maze[i][j] = 1;
			mx_i = max(mx_i, i);
			mn_i = min(mn_i, i);
			mx_j = max(mx_j, j);
		}
		mn_i--;
		mx_i++;
		mx_j++;
		printf("%d %d\n", mx_i - mn_i + 1, mx_j - 0 + 1);
		for(i = mn_i; i <= mx_i; i++) {
			for(j = 0; j <= mx_j; j++)
				putchar(maze[i][j]? '.' : '#');
			putchar('\n');
		}
	}
}
