#include <bits/stdc++.h>
using namespace std;

int a[11234];
int d[11234];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int i, n, t;
		scanf("%d %d", &n, &t);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		queue<int> q;
		q.push(0);
		for(i = 1; i <= 3600; i++) d[i] = 1e8;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(i = 0; i < n; i++) {
				int y = max(min(x + a[i], 3600), 0);
				if(d[y] > 1e7) {
					d[y] = d[x] + 1;
					q.push(y);
				}
			}
		}
		int ot = t;
		while(d[t] > 1e7) t++;
		printf("%d %d\n", d[t], t - ot);
	}
}
