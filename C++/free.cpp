#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;
using namespace std;


int main() {
    string s = "";
    cin >> s;
    vector<bool> check(26, false);
    for (char c : s) {
        check.at(c-'a') = true;
    }
    for (int i=0; i<26; i++) {
        if (!check.at(i)) {
            cout << s + (char)('a'+i) << endl;
            return 0;
        }
    }
    string ret = "";
    for (int i=24; i>=0; i--) {
        if (s.at(i) > s.at(i+1)) {
            continue;
        }
        else {
            for (int j=0; j<i; j++) {
                ret += s.at(j);
            }
            int now = 25;
            while (true) {
                if (s.at(now) > s.at(i)) {
                    ret += s.at(now);
                    cout << ret << endl;
                    return 0;
                }
                now--;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
