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

int main() {
    int n = 0, k = 0;
    cin >> n >> k;
    n--;
    k--;
    if (n%k == 0) {
        cout << n/k << endl;
    }
    else {
        cout << n/k+1 << endl;
    }
    return 0;
}
