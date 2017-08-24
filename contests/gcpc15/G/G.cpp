#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 11234;

int a[N];

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int mn = 9001;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			mn = min(mn, a[j] - a[i]);
	if(mn >= 0) puts("yes");
	else puts("no");
}
