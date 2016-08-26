#include <bits/stdc++.h>
using namespace std;
int n, m;
char s[2][5009];
int sa[2][26][5009];
int memo[5005][5005];
int solve(int i, int j) {
	if(i > n && j > m) return 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	int addi = 0, addj = 0;
	int ci = ((i <= n)? s[0][i] : 0) - 'A';
	int cj = ((j <= m)? s[1][j] : 0) - 'A';
	if(i <= n && sa[0][ci][i] == 1 && sa[0][ci][i - 1] == 0 && sa[1][ci][j - 1] == 0)
		addi = -(i + j - 1);
	if(j <= m && sa[1][cj][j] == 1 && sa[1][cj][j - 1] == 0 && sa[0][cj][i - 1] == 0)
		addj = -(i - 1 + j);
	if(i <= n && sa[0][ci][i] == sa[0][ci][n] && sa[1][ci][j-1] == sa[1][ci][m])
		addi += i + j - 1;
	if(j <= m && sa[1][cj][j] == sa[1][cj][m] && sa[0][cj][i-1] == sa[0][cj][n])
		addj += i - 1 + j;
	r = INT_MAX;
	if(i <= n) r = solve(i + 1, j) + addi;
	if(j <= m) r = min(r, solve(i, j + 1) + addj);
	return r;
}

int main() {
	int i, j, k, t;
	scanf("%d", &t);
	while(t--) {
		scanf("%s %s", s[0] + 1, s[1] + 1);
		n = strlen(s[0] + 1); m = strlen(s[1] + 1);
		for(j = 'A'; j <= 'Z'; j++) {
			for(i = 1; i <= n; i++) {
				sa[0][j - 'A'][i] = (s[0][i] == j) + sa[0][j - 'A'][i - 1];				
			}
		}
		for(j = 'A'; j <= 'Z'; j++)
			for(i = 1; i <= m; i++)
				sa[1][j - 'A'][i] = (s[1][i] == j) + sa[1][j - 'A'][i - 1];				
		for(i = 1; i <= n + 1; i++)
			for(j = 1; j <= m + 1; j++)
				memo[i][j] = -1;
		printf("%d\n", solve(1, 1));
	}
}
