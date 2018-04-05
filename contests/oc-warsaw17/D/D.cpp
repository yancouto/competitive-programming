#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back


int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int x;
		scanf("%d", &x);
		string s;
		int i;
		for(i = 30; !((x >> i) & 1); i--);
		s = "1";
		int j = i;
		for(i--; i >= 0; i--) {
			if(i == j - 1) s = s + "*(1+1)";
			else s = "(" + s + ")*(1+1)";
			if((x >> i) & 1) s = s + "+1";
		}
		printf("%s\n", s.c_str());
	}
}
