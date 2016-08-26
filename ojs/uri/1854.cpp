#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
char line[1000];
int n, m;

ull fexp(ull x, ull p) {
	ull resp = 1;
	for(ull i = 1; i <= p; i <<= 1) {
		if(i & p) resp = mod(resp * x);
		x = mod(x * x);
	}
	return resp;
}

ull fat[10010006];
void pre() {
	fat[0] = 1;
	for(int i = 1; i < 10010006; i++)
		fat[i] = mod(fat[i - 1] * i);
}

int bit[1005][1005];
int get(int i, int j) {
	i += 2; j += 2;
	int sum = 0;
	for(; i; i -= (i & -i))
		for(int g = j; g; g -= (g & -g))
			sum += bit[i][g];
	return sum;
}
int get(int x1, int y1, int x2, int y2) {
	return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
}
void add(int i, int j, int x) {
	i += 2; j += 2;
	for(; i < 1005; i += (i & -i))
		for(int g = j; g < 1005; g += (g & -g))
			bit[i][g] += x;
}


int main() {
	pre();
	int day = 0, a;
	scanf("%d %d", &n, &m);
	int x1, x2, y1, y2, c;
	while(true) {
		fgets(line, sizeof line, stdin);
		if(feof(stdin)) return 0;
		a = sscanf(line, "%d %d %d %d %d", &x1, &y1, &x2, &y2, &c);
		if(a == 5) {
			int x = get(x1, y1, x2, y2);
			printf("Day #%d: %d\n", ++day, (int) mod(fat[x + c - 1] * fexp(mod(fat[x - 1] * fat[c]), modn - 2)));
		} else if(a == 3) {
			add(x1, y1, x2);
		} else if(a == 2) {
			add(x1, y1, -get(x1, y1, x1, y1));
		}
	}
	return 0;
}
