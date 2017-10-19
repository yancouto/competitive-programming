   
#include <bits/stdc++.h>
using namespace std;

int longestParenthesisedSubstring(const string& S) {
    vector<int> fst(S.size() + 1, -1);
    int l = 0;
    int best = 0;
    vector<int> st;
    for(int i = 0; i < int(S.size()); i++) {
        if(S[i] == '(') st.push_back(i);
        else if(!st.empty()) st.pop_back();
        else {
            l = i + 1;
            continue;
        }
        if(st.empty()) best = max(best, i - l + 1);
        else best = max(best, i - st.back());
    }
    return best? best : -1;
}
   
int main() {
    string S;
    cin >> S;
    cout << longestParenthesisedSubstring(S) << "\n";
    return 0;
}
