#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e4+7;

int n;
char str[N];
char pat[10];
int res = 0;
int nx[N][4];

inline int sq (int i) { return i*i; }

void go (int i) {
	if (i == 8) return;
	if (res >= sq(n)/(i+1)) return;
	for (pat[i] = 'a'; pat[i] <= 'c'; pat[i]++) {
		pat[i+1] = 0;
		int j = 0;
		int k = 0;
		while ((k = nx[k][pat[j%(i+1)]-'a']) < n) {
			j++;
			k++;
		}
		res = max(res, sq(j - (j%(i+1)))/(i+1));
		go(i+1);
	}
}

int main () {
	res = 1;
	scanf("%d %s", &n, str);
	nx[n][0] = nx[n][1] = nx[n][2] = n;
	for (int i = n-1; i >= 0; i--) {
		for (int j = 0; j < 3; j++) nx[i][j] = nx[i+1][j];
		nx[i][str[i]-'a'] = i;
	}
	go(0);
	printf("%d\n", res);

}
