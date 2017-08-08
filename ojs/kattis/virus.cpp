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

char a[112345], b[112345];

int main() {
	int i;
	scanf("%s %s", a, b);
	deque<char> A, B;
	for(i = 0; a[i]; i++) A.pb(a[i]);
	for(i = 0; b[i]; i++) B.pb(b[i]);
	while(!A.empty() && !B.empty()) {
		if(A.front() == B.front()) A.pop_front(), B.pop_front();
		else if(A.back() == B.back()) A.pop_back(), B.pop_back();
		else break;
	}
	printf("%d\n", int(B.size()));
}
