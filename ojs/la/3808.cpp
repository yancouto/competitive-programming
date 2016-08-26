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

int v[10] = {14, 1, 5, 3, 11, 9, 7, 15, 13, 6};
int inv[50];
void pre() {
	for(int i = 0; i < 10; i++)
		inv[v[i]] = i;
}
char g[3][1000];
void print_on(int d, int o) {
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 2; j++)
			g[i][j+o] = (v[d] & (1 << (2*i + j)))? '*' : '.';
}

int get(int o) {
	int x = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 2; j++)
			x |= ((g[i][j+o] == '*') << (2*i+j));
	return x;
}

int main() {
	pre();
	int i, j, d;
	char op, c;
	while(scanf("%d", &d) != EOF && d) {
		scanf(" %c", &op);
		if(op == 'S') {
			memset(g, ' ', sizeof g);
			for(i = 0; i < d; i++) {
				scanf(" %c", &c);
				print_on(c - '0', i * 3);
			}
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3 * (d - 1) + 2; j++)
					putchar(g[i][j]);
				putchar('\n');
			}
		} else {
			for(i = 0; i < 3; i++)
				for(j = 0; j < 2 * d; j++)
					scanf(" %c", &g[i][j]);
			for(i = 0; i < d; i++)
				putchar('0' + inv[get(2*i)]);
			putchar('\n');
		}
	}
}
