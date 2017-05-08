#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	freopen("knights.in", "r", stdin);
	freopen("knights.out", "w", stdout);
	int n, i, a, b;
	while(scanf("%d", &n) != EOF && n) {
		int mnA = INT_MAX, mnB = INT_MAX;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			if(a < 2) mnA = 0;
			else mnA = min(mnA, 1 + (a - 2) / 3);
			mnB = min(mnB, b / 3);
		}
		if(mnA <= mnB) puts("Peter wins the game");
		else puts("Andrew wins the game");
	}
}
