#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

char str[1009];

int main() {
	int i, w, d, x0, y0, x1, y1;
	fgets(str, 1009, stdin); sscanf(str, "%d %d", &w, &d);
	fgets(str, 1009, stdin); sscanf(str, "%d %d", &x0, &y0);
	fgets(str, 1009, stdin); sscanf(str, "%d %d", &x1, &y1);
	fgets(str, 1009, stdin);
	int up = 0, ri = 0;
	int u = 0, r = 0;
	for(i = 0; str[i]; i++) {
		bool fb = (str[i] == 'F') || (str[i] == 'B');
		bool lr = (str[i] == 'L') || (str[i] == 'R');
		if(!fb && !lr) continue;
		if(!up && fb) up = 2*(str[i] == 'B') - 1;
		if(!ri && lr) ri = 2*(str[i] == 'R') - 1;
		if(fb) u++;
		else r++;
	}
	if(r & 1) x1 = w - x1;
	if(u & 1) y1 = d - y1;
	x1 += ri * r * w;
	y1 += up * u * d;
	printf("%.4f\n", sqrt(ll(x1 - x0) * ll(x1 - x0) + ll(y1 - y0) * ll(y1 - y0)));
	return 0;
}
