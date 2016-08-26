#include <bits/stdc++.h>
using namespace std;
char line[1009];
char ns[209][209];


map<string, int> mp;
int get() {
	string s(line);
	if(!mp.count(s)) mp[s] = mp.size() - 1;
	return mp[s];
}
void gl() {
	fgets(line, sizeof line, stdin);
}
int a[209], b[209], up[209];
int main() {
	int i, j, t, n;
	gl(); sscanf(line, "%d", &t);
	while(t--) {
		mp.clear();
		gl(); sscanf(line, "%d", &n);
		for(i = 0; i < n; i++) {
			gl(); get();
		}
		for(i = 0; i < n; i++) {
			gl();
			strcpy(ns[i], line);
			a[get()] = i;
			b[i] = get();
		}
		do {
			for(i = 0; i < n; i++) up[i] = 0;
			for(i = 0; i < n; i++) {
				for(j = 0; j < i; j++)
					if(a[j] == a[i] + 1)
						break;
				up[a[i]] = (j < i);
			}
			for(i = n - 1; i >= 0; i--)
				if(up[i]) {
					printf("%s", ns[i]);
					for(j = 0; a[j] != i; j++);
					for(j--; j >= 0; j--) swap(a[j], a[j+1]);
					break;
				}
		} while(i >= 0);
		putchar('\n');
	}
}
