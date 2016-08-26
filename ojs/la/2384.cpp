#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 1000009;
int n, d;
typedef pair<int, int> pii;

int comps;
bool seen[MAX];
void breakk(int i) {
	seen[i] = false;
	if(!seen[i - 1] && !seen[i + 1]) comps--;
	else if(seen[i - 1] && seen[i + 1]) comps++;
}

pii hs[MAX];

int main() {
	int t, i, h;
	scanf("%d", &t);
	while(t--) {
		comps = 1;
		scanf("%d %d", &n, &d);
		for(i = 1; i <= n; i++) {
			scanf("%d", &h);
			seen[i] = true;
			hs[i - 1] = make_pair(h, i);
		}
		sort(hs, hs + n);
		int top = -1;
		for(i = 0; i < d; i++) {
			scanf("%d", &h);
			while(top < n - 1 && hs[top + 1].first <= h)
				breakk(hs[++top].second);
			if(i > 0) putchar(' ');
			printf("%d", comps);
		}
		putchar('\n');
	}
	return 0;
}