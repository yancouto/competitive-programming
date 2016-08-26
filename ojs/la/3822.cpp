#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int C, D, H, S;

double memo[14][14][14][14][3][3][3][3];
double solve(int c, int d, int h, int s, int cj, int dj, int hj, int sj) {
	if((c + cj) >= C && (d + dj) >= D && (h + hj) >= H && (s + sj) >= S)
		return 0.;
	double &m = memo[c][d][h][s][cj][dj][hj][sj];
	if(m > 0.5) return m - 1;
	int x[4] = {c, d, h, s};
	int j[4] = {cj, dj, hj, sj};
	double ans = 0;
	double left = 54 - c - d - h - s - cj - dj - hj - sj;
	for(int i = 0; i < 4; i++) {
		int i_left = 13 - x[i];
		if(!i_left) continue;
		x[i]++;
		ans += (i_left / left) * (1 + solve(x[0], x[1], x[2], x[3], cj, dj, hj, sj));
		x[i]--;
	}
	int j_left = 2 - cj - dj - hj - sj;
	if(j_left) {
		double jok = 1000;
		for(int i = 0; i < 4; i++) {
			j[i]++;
			jok = min(jok, solve(x[0], x[1], x[2], x[3], j[0], j[1], j[2], j[3]));
			j[i]--;
		}
		ans += (j_left / left) * (1 + jok);
	}
	m = ans + 1;
	return ans;

}

int main() {
	int t;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		scanf("%d %d %d %d", &C, &D, &H, &S);
		printf("Case %d: ", tt);
		memset(memo, 0, sizeof memo);
		if(max(C - 13, 0) + max(D - 13, 0) + max(H - 13, 0) + max(S - 13, 0) > 2)
			puts("-1.000");
		else {
			double s = solve(0, 0, 0, 0, 0, 0, 0, 0);
			if(s < 0.000009)
				 puts("0.000");
			else
				printf("%.3f\n", s);
		}
	}
	return 0;
}