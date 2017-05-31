#include <bits/stdc++.h>
using namespace std;

int h[10], t[10], w[10];

int main() {
	int i;
	for(i = 0; i < 4; i++) scanf("%d %d", &h[i], &t[i]);
	w[2] = 2;
	for(i = 0; i < 4; i += 2)
		if(h[i] + t[i] < h[i + 1] + t[i + 1])
			swap(h[i], h[i + 1]), swap(t[i], t[i + 1]), w[i] = i + 1;
	t[2] += t[1];
	t[0] += t[3];
	if(t[0] + h[0] >= t[2] + h[2]) printf("%d\n", w[0] + 1);
	else printf("%d\n", w[2] + 1);
}
