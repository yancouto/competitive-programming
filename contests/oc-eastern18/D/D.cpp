#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 100123;
char str[N];
int n;

void yes (char d) {
	printf("%c\n", d);
	exit(0);
}

int main () {
	scanf(" %s", str);
	n = strlen(str);

	for (char d = '1'; ; d++) {
		bool ok = 0;
		for (int j = n-1; j >= 0; j--) {
			if (str[j] == d) { yes(d); }
			if (str[j] == d+1 && ok) { yes(d); }
			if (str[j] != '9') ok = 1;
		}
	}
}
