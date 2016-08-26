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

char A[1123456], B[1123456];
int main() {
	int i;
	for_tests(t, tt) {
		scanf("%s", A);
		scanf("%s", B);
		for(i = 1; A[i] == A[i - 1]; i++);
		if(!A[i]) { puts("Unlucky Chef"); continue; }
		int w0 = 0, w1 = 0;
		for(i = 0; A[i]; i++)
			if(A[i] != B[i] && A[i] == '0') w0++;
			else if(A[i] != B[i]) w1++;
		puts("Lucky Chef");
		printf("%d\n", max(w0, w1));
	}
}
