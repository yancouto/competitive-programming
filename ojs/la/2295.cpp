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

const int MAX = 200009;
int x[MAX], ok[MAX], freq[MAX];
int nok;
void rem(int i) {
	freq[i]--;
	if(freq[i] == 1) nok--;
}
void add(int i) {
	if(freq[i] == 1) nok++;
	freq[i]++;
}

int main() {
	int i, n, s;
	for_tests(t, tt) {
		scanf("%d %d", &s, &n);
		for(i = 0; i < n; i++) freq[i] = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x[i]);
		}
		nok = 0; int resp = 0;
		for(i = 0; i < n + s; i++) {
			if(i < n) add(x[i]);
			if(i - s >= 0) rem(x[i - s]);
			ok[i] = (nok == 0) && ((i - s < 0) || ok[i - s]);
			if(i >= n && ok[i]) resp++;
		}
		printf("%d\n", resp);
	}
	return 0;
}
