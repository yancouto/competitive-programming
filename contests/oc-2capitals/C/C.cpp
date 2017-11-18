#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
	int i, n, l, r;
	scanf("%d %d %d", &n, &l, &r);
	int cp = 0, cc = 0;
	for(i = 1; i <= n; i++) {
		if(i >= l && i <= r) {
			if(cc & 1) putchar(']');
			else putchar('[');
			cc++;
		} else {
			if(cp & 1) putchar(')');
			else putchar('(');
			cp++;
		}
	}
	putchar('\n');
}
