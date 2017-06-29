#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

char s[1123456];
int main() {
	scanf("%s", s);
	int l = 0, r = strlen(s) - 1;
	while(l <= r && s[l] == 'L') l++;
	while(l <= r && s[r] == 'R') r--;
	printf("%d\n", l + (int(strlen(s)) - 1 - r) + ((r - l + 1) > 0));
}
