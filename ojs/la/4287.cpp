#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
int k;
char plain[105], cipher[105];
char pp[105], cc[105];

int S[203], size[203], x[203], y[203];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	if(a == b) return;
	if(size[a] < size[b]) swap(a, b);
	size[a] += size[b];
	x[a] += x[b];
	y[a] += y[b];
	S[b] = a;
}
int seen[203];
ull fat[203];

int main() {
	int i, j, ii;
	fat[0] = 1;
	for(i = 1; i <= 200; i++)
		fat[i] = fat[i - 1] * i;
	while(scanf("%d", &k) != EOF) {
		scanf(" %s %s", plain, cipher);
		int d = strlen(plain);
		strcpy(pp, plain);
		strcpy(cc, cipher);
		for(i = 0; i < d ; i += k) {
			sort(pp + i, pp + i + k);
			sort(cc + i, cc + i + k);
		}
		if(strcmp(pp, cc)) {
			puts("0");
			continue;
		}
		for(i = 0; i < k; i++) {
			S[i] = i; S[i + k] = i + k;
			size[i] = size[i + k] = 1;
			x[i] = 1; y[i] = 0;
			x[i + k] = 0; y[i + k] = 1;
		}
		for(i = 0; i < k; i++)
			for(j = 0; j < k; j++) {
				for(ii = 0; ii < d; ii += k)
					if(plain[ii + i] != cipher[ii + j])
						break;
				if(ii == d) join(find(i), find(j + k));
			}
		memset(seen, 0, sizeof seen);
		ull resp = 1;
		for(i = 0; i < 2*k; i++) {
			int a = find(i);
			if(seen[a]) continue;
			seen[a] = true;
			if(x[a] != y[a]) break;
			resp *= fat[size[a] / 2];
		}
		if(i == 2*k) printf("%llu\n", resp);
		else puts("0");	
	}
	return 0;
}