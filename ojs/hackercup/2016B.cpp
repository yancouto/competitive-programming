#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char t[2][1009];

bool lone(int j, int i) {
	return (!i || t[j][i - 1] == 'X') && t[j][i] == '.' && t[j][i + 1] == 'X';
}

int main() {
	int i, j, k, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		scanf("%s %s", t[0], t[1]);
		t[0][n] = t[1][n] = 'X';
		int g = 0;
		for(i = 0; i < n; i++) {
			if(lone(0, i) && lone(1, i)) { g++; t[0][i] = t[1][i] = 'X'; continue; }
			for(j = 0; j < 2; j++)
				if(lone(j, i)) {
					g++; t[j][i] = 'X';
					if(t[!j][i] != 'X')
						for(k = i + 1; k < n && t[!j][k] != 'X';) t[!j][k++] = 'X';
					for(k = i; k >= 0 && t[!j][k] != 'X';) t[!j][k--] = 'X';
				}
		}
		t[0][n+1] = t[1][n+1] = 0;
		for(i = 1; i <= n; i++)
			for(j = 0; j < 2; j++)
				g += (t[j][i] == 'X' && t[j][i - 1] == '.');
		printf("Case #%d: %d\n", tt, g);
	}
}
