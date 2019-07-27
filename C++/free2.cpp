#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using ll = long long;
using namespace std;

ll keta(ll k) {
    ll buf = 1;
    ll count = 1;
    while (k > buf) {
        buf *= 2;
        count++;
    }
    return count;
}

int main () {
    ll n = 0, k = 0;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i=0; i<n; i++) {
        cin >> a.at(i);
    }
    ll ketaa = keta(n*k);
    vector<vector<ll>> to(n, vector<ll>(ketaa));
    for (int i=0; i<ketaa; i++) {
        for (int j=0; j<n; j++) {
            if (i == 0) {
                int now = j+1;
                while (true) {
                    if (a.at(j) == a.at(now%n)) {
                        to.at(j).at(i) = now - j + 1;
                        break;
                    }
                    else now++;
                }
            }
            else {
                to.at(j).at(i) = to.at(j).at(i-1) + to.at((to.at(j).at(i-1)+j)%n).at(i-1);
            }
        }
    }
    ll start = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i=ketaa-1; i>=0; i--) {
            if (start+to.at(start%n).at(i) > n*k-1) continue;
            else {
                start += to.at(start%n).at(i);
                flag = true;
                break;
            }
        }
    }
    vector<ll> buf;
    vector<ll> check(200001, -1);
    for (ll i=start; i<n*k; i++) {
        if (check.at(a.at(i%n)) >= 0) {
            ll pre = check.at(a.at(i%n));
            for (ll j=start+pre; j<start+buf.size(); j++) {
                check.at(a.at(j%n)) = -1;
            }
            buf.resize(pre-start);
        }
        else {
            buf.push_back(a.at(i%n));
            check.at(a.at(i%n)) = start+buf.size()-1;
        }
    }
    for (int i=0; i<buf.size(); i++) {
        cout << buf.at(i);
        if (i != buf.size()-1) cout << " ";
    }
    cout << endl;
    return 0;
}
