#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 10009;
int m;
int bought[MAX];
int sz;
void buy(int i) {
	if(!bought[i]) {
		bought[i] = 1;
		sz++;
	}
}

int main() {
	int t, i, a, b;
	scanf("%d", &t);
	while(t--) {
		sz = 0;
		scanf("%d", &m);
		for(i = 0; i < MAX; i++)
			bought[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			buy(a - 1); buy(b - 1);
		}
		printf("%d\n", sz);
	}
	return 0;
}