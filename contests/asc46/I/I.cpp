#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;

int n1, n2, n3, n;
int f2;
int pos[N];
int typ[N];
int us[N];

void alloc1(int qi) {
	if(n2 && n1 == f2) {
		pos[us[f2]] = f2 + 2 * n2;
		swap(us[f2], us[f2 + 2 * n2]);
		printf("M %d %d\n", f2 + 1, f2 + 2 * n2 + 1);
		f2 += 2;
	}
	us[n1] = qi;
	pos[qi] = n1;
	printf("A %d\n", n1 + 1);
	n1++;
}

void alloc2(int qi) {
	if(n2 == 0) f2 = n1 + 2;
	if(f2 - 2 >= n1) {
		f2 -= 2;
		us[f2] = qi;
		pos[qi] = f2;
		printf("A %d\n", f2 + 1);
	} else {
		us[f2 + 2 * n2] = qi;
		pos[qi] = f2 + 2 * n2;
		printf("A %d\n", f2 + 2 * n2 + 1);
	}
	n2++;
}

void alloc3(int qi) {
	n3++;
	while(n2 && n - 3 * n3 < f2 + 2 * n2) {
		f2 -= 2;
		pos[us[f2 + 2 * n2]] = f2;
		swap(us[f2 + 2 * n2], us[f2]);
		printf("M %d %d\n", f2 + 2 * n2 + 1, f2 + 1);
	}
	us[n - 3 * n3] = qi;
	pos[qi] = n - 3 * n3;
	printf("A %d\n", n - 3 * n3 + 1);
}

void rem1(int p) {
	us[p] = 0;
	n1--;
	if(p != n1) {
		pos[us[n1]] = p;
		swap(us[p], us[n1]);
		printf("M %d %d\n", n1 + 1, p + 1);
	}
	printf("D\n");
}

void rem2(int p) {
	us[p] = 0;
	if(p != f2) {
		pos[us[f2]] = p;
		swap(us[p], us[f2]);
		printf("M %d %d\n", f2 + 1, p + 1);
	}
	f2 += 2;
	n2--;
	printf("D\n");
	
}

void rem3(int p) {
	us[p] = 0;
	if(p != n - 3 * n3) {
		pos[us[n - 3 * n3]] = p;
		swap(us[p], us[n - 3 * n3]);
		printf("M %d %d\n", n - 3 * n3 + 1, p + 1);
	}
	n3--;
	printf("D\n");
}

int main() {
	int t = 0, op;
	scanf("%d", &n);
	while(scanf("%d", &op) != EOF && op != 0) {
		typ[++t] = op;
		if(op == 1) alloc1(t);
		else if(op == 2) alloc2(t);
		else if(op == 3) alloc3(t);
		else if(typ[-op] == 1) rem1(pos[-op]);
		else if(typ[-op] == 2) rem2(pos[-op]);
		else if(typ[-op] == 3) rem3(pos[-op]);
		else assert(false);
		fflush(stdout);
	}
}
