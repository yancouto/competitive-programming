#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

string str;

int main () {
	cin >> str;
	int i = 0;
	while (i < str.size() && str[i] == 'A') i++;
	int j = 0;
	while (j < str.size() && str[str.size()-j-1] == '!') j++;
	if (i + j == str.size() && i && j) printf("Panic!\n");
	else printf("No panic\n");
}
