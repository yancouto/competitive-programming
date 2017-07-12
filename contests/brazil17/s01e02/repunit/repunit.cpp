#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int s[112345];
int sn;

int main() {
	int i, n, a, b, x;
	scanf("%d", &n);
	scanf("%d %d", &a, &b);
	a = 2 * n - a;
	b = 2 * n - b;
	swap(a, b);
	while(a <= b && a <= n) {
		int x = ((a - 1 - 10) / 9) + 1;
		if(a <= 10) x = 0;
		x += a;
		s[sn++] = x % 10;
		a++;
	}
	int k = ((n - 10) / 9) + 1;
	if(n < 10) k = 0;
	int nk = k;
	for(i = n + 1; i < 2 * n;) {
		if(i == a && a <= b) {
			s[sn++] = (n - (i - n) + nk) % 10;
			a++;
		}
		nk = (n - (i - n) + nk) / 10;
		i++;
		if(nk < k) break;
	}
	if(a <= b) {
		nk = nk - (a - i) / 9;
		i += int((a - i) / 9) * 9;
		while(a <= b) {
			if(a == i + 9) nk--, i = a;
			s[sn++] = (n - (a - n) + nk) % 10;
			a++;
		}
	}
	reverse(s, s + sn);
	for(i = 0; i < sn; i++) printf("%d", s[i]);
	putchar('\n');
}
