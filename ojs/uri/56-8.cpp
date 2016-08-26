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

char str[] = "LIFE IS NOT A PROBLEM TO BE SOLVED";
char aux[100];
int main() {
	int i, n;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			aux[i] = str[i];
		aux[n] = '\0';
		printf("%s\n", aux);
	}
	return 0;
}
