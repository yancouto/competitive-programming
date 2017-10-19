   
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int pal(const string &s) {
    ll H = 0, R = 0;
    ll B = 243; ll M = 1000000007;
    ll BP = 1;
    int mx = 0;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        H = (H * B + ll(s[i])) % M;
        R = (R + BP * ll(s[i])) % M;
        if(H == R) mx = i + 1;
        BP = (BP * B) % M;
    }
    return n - mx;
}

int palindromeCreation(string& S) {
    int ans = pal(S);
    reverse(S.begin(), S.end());
    return min(ans, pal(S));
}
   
int main() {
    string S;
    cin >> S;
    cout << palindromeCreation(S) << "\n";
    return 0;
}
