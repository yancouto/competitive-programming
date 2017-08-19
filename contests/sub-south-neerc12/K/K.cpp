#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 1e5+7;
char str[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fgets(str, sizeof str, stdin);

	int n = strlen(str);

	int rs = 0;
	bool ls = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == ')' && !ls)
			rs++;
		else if (str[i] == '(')
			ls = 1;
		else if (str[i] != ' ' && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
			ls = 0;
	}

	ls = 0;
	for (int i = n-1; i >= 0; i--) {
		if (str[i] == '(' && !ls)
			rs++;
		else if (str[i] == ')')
			ls = 1;
		else if (str[i] != ' ' && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
			ls = 0;
	}

	printf("%d\n", rs);
}
