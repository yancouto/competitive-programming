#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 112345;
int p[N];

int main() {
	int i, j, t;
	for(i = 2; i < N; i++)
		if(p[i] == 0)
			for(j = i; j < N; j += i)
				p[j]++;
	vector<int> all;
	for(i = 2; i < N; i++)
		if(p[i] >= 3)
			all.pb(i);
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &i);
		printf("%d\n", all[i - 1]);
	}
}
