#include <bits/stdc++.h>
using namespace std;

int a[25009];

int main() {
	int m;
	scanf("%d", &m);
	multiset<int> s;
	for(int i = 0; scanf("%d", &a[i]); i++) {
		if(a[i] == -1) return 0;
		s.insert(a[i]);
		if(i >= m - 1) {
			printf("%d\n", *s.rbegin());
			s.erase(s.find(a[i - m+1]));
		}
	}
}
