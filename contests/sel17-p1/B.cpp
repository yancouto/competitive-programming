#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 212345;
int a[N];

int main() {
	int i, t, n, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int tot = 0;
		for(; n; n--) {
			swap(*max_element(a, a + n), a[n - 1]);
			int w = a[n - 1];
			if(w > n - 1) {
				tot += w - (n - 1);
				w = n - 1;
			}
			sort(a, a + n - 1);
			for(i = w; i < n - 1; i++) {
				if(--a[i] < 0)
					a[i] = 0, tot++;
			}
		}
		printf("%d\n", tot);
	}
}
