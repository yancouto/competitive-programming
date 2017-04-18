#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;
int n;

int main () {
	scanf("%d", &n);

	if (n == 2) {
		printf("%d\n", 2);
	} else if (n%2 == 0) {
		printf("%d\n", n-1);
	} else {
		printf("%d\n", n);
	}
}
