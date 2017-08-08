#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 112345;

int a[N];
char s[N];

void imp() {
	puts("-1");
	exit(0);
}

int main() {
	int i, j, K, k;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> K >> s;
	int n = strlen(s);
	for(i = 0; i < n && s[i] == '='; i++);
	if(i == n) {
		for(i = 0; i <= n; i++) putchar('a');
		putchar('\n');
		return 0;
	}
	if(s[i] == '>')
		for(j = 0; j <= i; j++)
			a[j] = K - 1;

	for(; i < n; ) {
		int j = i;
		while(j + 1 < n && (s[j + 1] == '=' || s[j + 1] == s[i]))
			j++;
		int cur;
		if(s[i] == '<') cur = K - 1;
		else cur = 0;
		for(k = j; k >= i; k--) {
			a[k + 1] = cur;
			if(s[k] != '=') {
				if(s[i] == '<') cur--;
				else cur++;
			}
		}
		i = j + 1;
	}
	for(i = 0; i <= n; i++)
		if(a[i] < 0 || a[i] >= K) {
			puts("-1");
			return 0;
		}
	for(i = 0; i < n; i++) {
		if(s[i] == '>' && !(a[i] > a[i + 1])) imp();
		if(s[i] == '<' && !(a[i] < a[i + 1])) imp();
		if(s[i] == '=' && !(a[i] == a[i + 1])) imp();
	}
	for(i = 0; i <= n; i++)
		putchar(a[i] + 'a');
	putchar('\n');
}
