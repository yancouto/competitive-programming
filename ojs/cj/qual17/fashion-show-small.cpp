#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int v[1123], v2[1123];

int main() {
	int i, p, n, m; char tp;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) v[i] = 0;
		for(i = 0; i < m; i++) {
			scanf(" %c %*d %d", &tp, &p);
			v[p - 1] = tp;
		}
		int ch = 0;
		int any = -1;
		for(i = 0; i < n; i++) {
			v2[i] = '+';
			if(!v[i]) ch++;
			else if(v[i] != '+') any = i, v2[i] = v[i];
		}
		if(any == -1) ch += !!v[0], v2[0] = 'o';
		else if(v[any] != 'o') ch++, v2[any] = 'o';
		printf("Case #%d: %d %d\n", tt, 2 * n, ch + n - 1);
		for(i = 0; i < n; i++)
			if(v[i] != v2[i])
				printf("%c 1 %d\n", v2[i], i + 1);
		for(i = 1; i < n; i++) {
			if(i == any) printf("x %d 1\n", i + 1);
			else printf("x %d %d\n", i + 1, i + 1);
		}
	}
}
