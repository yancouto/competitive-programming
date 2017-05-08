#include <bits/stdc++.h>
using namespace std;


string g[1123], g2[1123];
string s[1123], t[1123];

inline char gchar(string s[], int n, int m, int i, int j, int k) {
	if(k < m - j) return s[i][j + k];
	if(k >= n * m - j) return s[i][j - (n * m - k)];
	k -= m - j;
	int di = (k / m) + ((k / m) >= i);
	return s[di][k % m];
}

inline string solve(string s[], int n, int m) {
	sort(s, s + n); reverse(s, s + n);
	int i, j, k;
	int bi = 0, bj = 0;
	for(i = 0; i < n; i++) {
		if(i && s[i] == s[i - 1]) continue;
		for(j = 0; j < m; j++) {
			for(k = 0; k < n * m && gchar(s, n, m, i, j, k) == gchar(s, n, m, bi, bj, k); k++);
			if(k == n * m) continue;
			if(gchar(s, n, m, i, j, k) > gchar(s, n, m, bi, bj, k)) bi = i, bj = j;
		}
	}
	string S;
	for(k = 0; k < n * m; k++)
		S.push_back(gchar(s, n, m, bi, bj, k));
	return S;
}

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) cin >> g[i];
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			g2[j].push_back(g[i][j]);
	string S = solve(g, n, m);
	string T = solve(g2, m, n);
	if(T > S) S = T;
	for(i = 0; S[i] == '0'; i++);
	for(; S[i]; i++) putchar(S[i]);
	putchar('\n');
}
