#include <iostream>

using namespace std;

int main() {
    string s;
    
    cin >> s;

    // count[0] = 연속된 0 묶음의 개수
    // count[1] = 연속된 1 묶음의 개수
    int count[2] = {0, };

   for (int i = 0; i < (int)s.size(); i++) {
       if (i == 0 || s[i] != s[i - 1]) {
           count[s[i] - '0']++;
       }
   }

    cout << min(count[0], count[1]) << '\n';
    
    return 0;
}