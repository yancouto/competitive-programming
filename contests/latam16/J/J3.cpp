#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

bool prime(ll x) {
	for(ll i = 2; i * i <= x; i++)
		if(!(x % i))
			return false;
	return true;
}

int n;

int main () {
	scanf("%d", &n);

	while(!prime(n)) n--;
	printf("%d\n", n);
}
