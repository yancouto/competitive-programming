#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull modn = 1000000;
inline ull mod(ull x) { return x % modn; }

int memo[1009][1009];
int acc[1009][1009];
inline int& m(int i, int j) { return memo[i+2][j+2]; } 
inline int& a(int i, int j) { return acc[i+2][j+2]; }
int main() {
	int n, i, j, k;
	for(i = 0; i <= 1000; i++)
		for(j = 0; j <= i; j++) {
			int x = i - j, y = j;
			m(x, y) = 0;
			if(y > 0)
				m(x, y) = m(x, y - 1);
			m(x, y) = mod(m(x, y) + a(0, x + y - 1) - a(x, y - 1) + modn);
			if(x == 0 && y == 0) m(x, y) = 1;
			a(x, y) = mod(m(x, y) + a(x + 1, y - 1));
		}
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		printf("%d\n", m(n, 0));
	}
}