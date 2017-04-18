#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

const int N = 1e5+7;
const double pi = acos(-1.);

int n;
ll a[N];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	
	sort(a, a+n);

	ll rs = 0;
	rs += a[0] * a[1] + a[0] * a[2];

	for (int j = 0; j < 2; j++)
		for (int i = 1+j; i + 2 < n; i+=2)
			rs += a[i] * a[i+2];
	
	rs += a[n-1] * a[n-2];

	printf("%.3f\n", double(rs)*sin(2.*pi/n)*.5);
}
