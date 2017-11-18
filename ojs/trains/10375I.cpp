#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int opc = 2;

#define op(args...) (printf(args), opc++)

int bl2[100], shift[100], dirty[100], esc[100];

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	bl2[1] = 0;
	for(i = 2; i <= n; i++)
		bl2[i] = op("swap_rows 0 1 %d\n", i);
	shift[0] = dirty[0] = 1;
	for(i = 1; i <= n; i++) {
		dirty[i] = op("+ %d %d\n", shift[i - 1], bl2[i]);
		//printf("dirty %d = %d\n", i, dirty[i]);
		if(i < n) {
			shift[i] = dirty[i];
			for(j = i; j > 0; j--) {
				//printf("shift[%d] bef = %d\n", i, shift[i]);
				shift[i] = op("swap_columns %d %d %d\n", shift[i], j + 1, j + 2);
				//printf("shift[%d] aft = %d\n", i, shift[i]);
			}
		}
	}
	esc[n] = dirty[n];
	for(i = n; i >= 1; i--) {
		for(j = 1; j <= i; j++) {
			//printf("esc[%d] bef = %d\n", i, esc[i]);
			esc[i] = op("swap_columns %d %d %d\n", esc[i], j, j + 1);
			//printf("esc[%d] bef = %d\n", i, esc[i]);
		}
		if(i == 1) continue;
		esc[i - 1] = op("+ %d %d\n", esc[i], dirty[i - 1]);
		for(j = i + 1; j <= n; j++) {
			esc[i - 1] = op("swap_rows %d %d %d\n", esc[i - 1], i, j);
			esc[i - 1] = op("+ %d %d\n", esc[i - 1], esc[i]);
		}
	}
	int fin = 1;
	for(i = 1; i <= n; i++) {
		int unit;
		if(i == 1) unit = esc[1];
		else unit = op("swap_rows %d 1 %d\n", esc[1], i);
		fin = op("+ %d %d\n", fin, unit);
	}
	op("answer %d\n", fin);
}
