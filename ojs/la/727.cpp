#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
char s1[103], s2[103], s3[103];
int a1[403], a2[403], a3[403];
char conv[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
int inv[257];
int t[500];

void pre() {
	for(int i = 0; i < 16; i++)
		inv[conv[i]] = i;
}

void advance_and_copy(int* &j, int* &k) {
	*k = *j;
	if(*j == 1) {
		*(k + 1) = *(j + 1);
		k += 2; j += 2;
		return;
	}
	k++; j++;
	for(int i = 0; i < 4; i++)
		advance_and_copy(j, k);
}

void create(int* &i, int* &j, int* &k) {
	if(*i == 1 && *j == 1) {
		*k = 1;
		*(k + 1) = *(i + 1) & *(j + 1);
		i += 2; j += 2; k += 2;
		return;
	}
	if(*j == 1) { create(j, i, k); return; }
	if(*i == 1) {
		if(*(i + 1) == 0) {
			*k = 1;
			*(k + 1) = 0;
			int *trash = t;
			advance_and_copy(j, trash);
			i += 2; k += 2;
		} else {
			advance_and_copy(j, k);
			i += 2;
		}
		return;
	}
	int *kk[4];
	*k = 0;
	i++; j++; k++;
	for(int ii = 0; ii < 4; ii++) {
		kk[ii] = k;
		create(i, j, k);
	}
	if(kk[0][0] == 1 && kk[1][0] == 1 && kk[2][0] == 1 && kk[3][0] == 1 && kk[0][1] == kk[1][1] && kk[0][1] == kk[2][1] && kk[0][1] == kk[3][1]) {
		kk[0][-1] = 1;
		kk[0][0] = kk[0][1];
		k = kk[0] + 1;
	}
}

int main() {
	pre();
	int i, j, x;
	int t = 0;
	while(true) {
		scanf(" %s %s", s1, s2);
		if(s1[0] == '0' && s2[0] == '0') return 0;
		if(t > 0) putchar('\n');
		int n1 = 0;
		for(i = 0; s1[i]; i++)
			for(j = 3; j >= 0; j--)
				a1[n1++] = !!((1 << j) & inv[s1[i]]);
		n1 = 0;
		for(i = 0; s2[i]; i++)
			for(j = 3; j >= 0; j--)
				a2[n1++] = !!((1 << j) & inv[s2[i]]);
		int *c1 = a1, *c2 = a2, *c3 = a3 + 4; a3[3] = 1;
		while(*c1 == 0) c1++;
		while(*c2 == 0) c2++;
		c1++; c2++;
		create(c1, c2, c3);
		c3--; i = 0;
		while(c3 - a3 >= 3) {
			x = 0;
			for(j = 0; j < 4; j++) {
				x |= (*c3) * (1 << j);
				c3--;
			}
			s3[i++] = conv[x];
		}
		reverse(s3, s3 + i);
		s3[i] = '\0';
		printf("Image %d:\n%s\n", ++t, s3);
	}

}
