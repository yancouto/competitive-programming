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

char l[2][200009];

int tryrun(int li) {
	int i = 0, ct = 0;
	while(l[0][i]) {
		if(l[li][i] == '#') return INT_MAX;
		while(l[li][i] == '.') i++;
		li = !li; ct++;
	}
	return ct - 1;
}

int main() {
	for_tests(t, tt) {
		scanf("%s %s", l[0], l[1]);
		int a = min(tryrun(0), tryrun(1));
		if(a == INT_MAX) puts("No");
		else printf("Yes\n%d\n", a);
	}
	return 0;
}
