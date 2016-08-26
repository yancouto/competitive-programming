#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int x[303], y[303];
int dist(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int cross(int i, int j, int k) {
	return (x[j] - x[i]) * (y[k] - y[i]) - (y[j] - y[i]) * (x[k] - x[i]);
}

map<vector<int>, int> ss;
int main() {
	int i, j, k, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			vector<int> v;
			for(k = 0; k < n; k++)
				if(k == i || k == j || cross(i, j, k) == 0)
					v.push_back(k);
			ss[v] = max(ss[v], dist(i, j));
		}
	double tot = 0;
	for(auto &e : ss)
		tot += sqrt(e.second);
	printf("%.0f\n", tot);
}
