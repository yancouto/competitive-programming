#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

char s[1123456]; int ss;
inline char peek() { return s[ss]; }
inline char get() { return s[ss++]; }

void error() {
	printf("Error at position %d!\n", ss);
	exit(0);
}

void check(ll add) {
	if(add + ss > n) error();
}

void readObj(int);

void readList(int add) {
	check(add + 2);
	debug("readList(%d) peek %c\n", add, peek());
	assert(get() == 'l');
	add += 1;
	while(peek() != 'e') {
		check(add + 2);
		readObj(add);
	}
	check(add);
	assert(get() == 'e');
}

void readDict(int add) {
	check(add + 2);
	debug("readDict(%d) peek %c\n", add, peek());
	assert(get() == 'd');
	add += 1;
	while(peek() != 'e') {
		check(add + 4);
		readObj(add + 2);
		check(add + 2);
		readObj(add);
	}
	check(add);
	assert(get() == 'e');
}

void readInt(int add) {
	check(add + 3);
	debug("readInt(%d) peek %c\n", add, peek());
	assert(get() == 'i');
	add += 1;
	check(add + 1);
	if(!isdigit(peek())) error();
	if(get() == '0' && peek() != 'e') error();
	while(peek() != 'e') {
		check(add + 1);
		if(!isdigit(peek())) error();
		get();
	}
	check(add);
	assert(get() == 'e');
}

void readStr(int add) {
	debug("readStr(%d) peek %c ss %d\n", add, peek(), ss);
	check(add + 2);
	if(!isdigit(peek())) error();
	ll sz = peek() - '0';
	check(add + sz + 1 + 1);
	get();
	if(sz == 0 && peek() != ':') error();
	while(peek() != ':') {
		if(!isdigit(peek())) error();
		sz = 10ll * sz + peek() - '0';
		check(add + sz + 1 + 1);
		get();
	}
	check(add + sz + 1);
	assert(get() == ':');
	check(add + sz);
	while(sz--) {
		if(!peek()) error();
		check(add + sz + 1);
		get();
	}
}

void readObj(int add) {
	debug("readObj(%d) peek %c\n", add, peek());
	if(peek() == 'l') readList(add);
	else if(peek() == 'i') readInt(add);
	else if(peek() == 'd') readDict(add);
	else readStr(add);
}

void all() {
	readObj(0);
	if(peek()) error();
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	scanf("%d %s", &n, s);
	all();
	puts("ok");
}
