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

string dig[10][7] = {
{
".XX.",
"X..X",
"X..X",
"....",
"X..X",
"X..X",
".XX."
},
{
"....",
"...X",
"...X",
"....",
"...X",
"...X",
"...."
},
{
".XX.",
"...X",
"...X",
".XX.",
"X...",
"X...",
".XX."
},
{
".XX.",
"...X",
"...X",
".XX.",
"...X",
"...X",
".XX."
},
{
"....",
"X..X",
"X..X",
".XX.",
"...X",
"...X",
"...."
},
{
".XX.",
"X...",
"X...",
".XX.",
"...X",
"...X",
".XX."
},
{
".XX.",
"X...",
"X...",
".XX.",
"X..X",
"X..X",
".XX."
},
{
".XX.",
"...X",
"...X",
"....",
"...X",
"...X",
"...."
},
{
".XX.",
"X..X",
"X..X",
".XX.",
"X..X",
"X..X",
".XX."
},
{
".XX.",
"X..X",
"X..X",
".XX.",
"...X",
"...X",
".XX."
}
};

// 0 - burnt, 1 - correct, 2 - doubt
int ans[7][25], cur[7][25];
char A[7][25], B[7][25], C[7][25]; 
char mat[102][7][25];

void write_dig(int d, char A[7][25], int off) {
	for(int i = 0; i < 7; i++)
		for(int j = off; j < off + 4; j++)
			A[i][j] = dig[d][i][j - off];
}

void write(int min, char A[7][25]) {
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 21; j++)
			A[i][j] = '.';
	int hour = min / 60; min = min % 60;
	if(hour > 9) write_dig(hour / 10, A, 0);
	write_dig(hour % 10, A, 5);
	A[2][10] = A[4][10] = 'X';
	write_dig(min / 10, A, 12);
	write_dig(min % 10, A, 17);
}
int n;
bool any = false;

void go(int min) {
	// 0 - dunno 1 - burnt in
	memset(cur, 0, sizeof cur);
	for(int k = 0; k < n; k++) {
		write((k + min) % (60 * 24), A);
		//for(int i = 0; i < 7; i++) {
		//	for(int j = 0; j < 21; j++)
		//		putchar(A[i][j]);
		//	putchar('\n');
		//}
		//puts("===============");
		for(int i = 0; i < 7; i++)
			for(int j = 0; j < 21; j++)
				if(A[i][j] != mat[k][i][j])
					cur[i][j] = 1;
	}
	//for(int i = 0; i < 7; i++) {
	//	for(int j = 0; j < 21; j++)
	//		putchar('0' + cur[i][j]);
	//	putchar('\n');
	//}
	//puts("===============");
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 21; j++) {
			int bur = cur[i][j], vis = 0;
			for(int k = 0; k < n; k++)
				if(mat[k][i][j] == '.') vis |= 1;
				else vis |= 2;
			if(bur && vis == 3) return;
			if(bur) cur[i][j] = 0;
			if(!bur && vis == 3) cur[i][j] = 1;
			if(!bur && vis < 3) cur[i][j] = 2;
		}
	any = true;
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 21; j++)
			if(cur[i][j])
				ans[i][j] = cur[i][j];
}

string O[7] = {
".??...WW.....??...??.",
"?..?.W..?...?..1.0..?",
"?..?.W..?.?.?..1.0..?",
".??...??.....11...WW.",
"?..?.W..?.0.W..?.1..?",
"?..?.W..?...W..?.1..?",
".??...11.....??...??."
};

string id = " W?.";
int main() {
	int i, j, k;
	scanf("%d", &n);
	for(k = 0; k < n; k++)
		for(i = 0; i < 7; i++)
			for(j = 0; j < 21; j++)
				scanf(" %c", &mat[k][i][j]);
	for(i = 0; i < 60 * 24; i++)
		go(i);
	for(i = 0; i < 7; i++)
		for(j = 0; j < 21; j++)
			if(O[i][j] == '.')
				ans[i][j] = 3;
	if(!any) puts("impossible");
	else
		for(i = 0; i < 7; i++) {
			for(j = 0; j < 21; j++) 
				putchar(ans[i][j]? id[ans[i][j]] : '0' + (mat[0][i][j] == 'X'));
			putchar('\n');
		}
}
