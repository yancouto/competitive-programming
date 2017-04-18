#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

int a[112345];
multiset<int> s[112345];

int n, k;

int go(int x) {
	if(x < k) return 0;
	return (x - k) / (k + 1) + 1;

}

int main () {
	int i;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	for(i = 0; i < n; i++)
		s[go(i)].insert(a[i]);
	multiset<int> ms;
	int tot = accumulate(a, a + n, 0);
	for(i = go(n - 1); i > 0; i--) {
		for(int x : s[i]) ms.insert(x);
		tot -= *ms.rbegin();
		ms.erase(ms.find(*ms.rbegin()));
	}
	printf("%d\n", tot);
}
