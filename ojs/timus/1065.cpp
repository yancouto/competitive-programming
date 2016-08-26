#include <bits/stdc++.h>
using namespace std;
double dist[52][52];
bool seen[52][52]; int n, m;
int x[1100], y[1100];
double memo[52][52];

int cross(int i, int j, int k) {
	return (x[j] - x[i]) * (y[k] - y[i]) - (y[j] - y[i]) * (x[k] - x[i]);
}

bool bad(int i, int j) {
	for(int p = 0; p < m; p++)
		if(cross(i, j, p + n) >= 0)
			return true;
	return false;
}

double go(int i, int fst) {
	double &r = memo[i][fst];
	if(seen[i][fst]) return r;
	seen[i][fst] = true;
	bool ok = true;
	r = 1/0.;
	for(int j = i + 1; ok && j < n; j++) {
		if(bad(i, j)) ok = false;
		else r = min(r, dist[i][j] + go(j, fst));
	}
	if(ok && !bad(i, fst)) r = min(r, dist[i][fst]);
	return r;
}

void do0() {
	int i, j, k;
	double cur = 1/0.;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			for(k = j + 1; k < n; k++)
				if(cross(i, j, k) != 0)
					cur = min(cur, dist[i][j] + dist[j][k] + dist[k][i]);
	printf("%.2f\n", cur);
}

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	for(i = 0; i < m; i++)
		scanf("%d %d", &x[n + i], &y[n + i]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
	if(m == 0) { do0(); return 0; }
	double cur = 1/0.;
	for(i = 0; i < n; i++)
		cur = min(cur, go(i, i));
	printf("%.2f\n", cur);
}
