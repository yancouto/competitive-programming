// WA
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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char all[3000009];
char* ln[101][10002];
char* nm[102];
char *cur;
int n;

int read_int() {
	while(*cur && isspace(*cur)) cur++;
	if(*cur == '\0') return -1;
	int x = 0;
	while(isdigit(*cur)) x = 10 * x + *cur++ - '0';
	return x;
}

char* read_line() {
	while(isspace(*cur)) cur++;
	char *l = cur;
	while(*cur != '\n') cur++;
	*cur = '\0'; cur++;
	return l;
}

bool eq(char *a, char *b) {
	while(*a && *b) {
		while(*a && *b && !isspace(*a) && !isspace(*b))
			if(*(a++) != *(b++))
				return false;
		if((*a && *b) && (!isspace(*a) || !isspace(*b)))
			return false;
		while(*a && isspace(*a)) a++;
		while(*b && isspace(*b)) b++;
	}
	return *a == '\0' && *b == '\0';
}

int match(char **c) {
	char **d = ln[n];
	int m = 0, mm = 0;
	while(*c && *d) {
		if(eq(*c, *d)) m++;
		else m = 0;
		mm = max(mm, m);
		c++, d++;
	}
	return mm;
}

int main() {
	int i, j;
	fread(all, sizeof(char), sizeof all, stdin);
	cur = all;
	while((n = read_int()) >= 0) {
		for(i = 0; i < n; i++) {
			nm[i] = read_line();
			for(j = 0; ; j++) {
				ln[i][j] = read_line();
				if(strncmp(ln[i][j], "***END***", 9) == 0)
					break;
			}
			ln[i][j] = NULL;
		}
		for(j = 0; ; j++) {
			ln[n][j] = read_line();
			if(strncmp(ln[n][j], "***END***", 9) == 0)
				break;
		}
		ln[n][j] = NULL;
		int st[102], sn = 0, mm = 0;
		for(i = 0; i < n; i++) {
			int m = match(ln[i]);
			if(m > mm) mm = m, sn = 0;
			if(mm == m) st[sn++] = i;
		}

		printf("%d", mm);
		if(mm)
			for(i = 0; i < sn; i++)
				printf(" %s", nm[st[i]]);
		putchar('\n');
	}
}
