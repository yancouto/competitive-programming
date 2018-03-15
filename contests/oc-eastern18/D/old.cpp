#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

char s[112345];

int main () {
	scanf("%s", s);
	int i;
	for(i = 1; s[i] && s[i] == '9'; i++);
	if(!s[i]) putchar(s[0]);
	else if(s[0] != '1') putchar(s[0] - 1);
	else putchar('1');
	putchar('\n');
}
