#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

char s[11234];
int up[11234];

int main() {
	int i, j, k;
	while(true) {
		fgets(s, 11234, stdin);
		if(feof(stdin)) return 0;
		for(i = 0; s[i]; ) {
			if(!isalpha(s[i])) { i++; continue; }
			for(j = i; isalpha(s[j + 1]); j++);
			for(k = i; k <= j; k++) {
				up[k] = isupper(s[k]);
				s[k] = tolower(s[k]);
			}
			if((j - i + 1) & 1) {
				reverse(s + i, s + j + 1);
			} else {
				for(k = 0; k < (j - i + 1) / 2; k++)
					swap(s[i + k], s[i + k + (j - i + 1) / 2]);
			}
			for(k = i; k <= j; k++)
				if(up[k])
					s[k] = toupper(s[k]);
			i = j + 1;
		}
		printf("%s", s);
	}
}
