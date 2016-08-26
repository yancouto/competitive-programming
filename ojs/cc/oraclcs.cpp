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

char s[200];
int main() {
	int i, j, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		int mna = INT_MAX, mnb = INT_MAX;
		for(i = 0; i < n; i++) {
			scanf("%s", s);
			int cta = 0, ctb = 0;
			for(j = 0; s[j]; j++)
				if(s[j] == 'a') cta++;
				else ctb++;
			mna = min(mna, cta);
			mnb = min(mnb, ctb);
		}
		printf("%d\n", min(mna, mnb));
	}
}
