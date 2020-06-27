#include <string>
#include <vector>

// create table
std::vector<int> createTable(const std::string &pattern) {
    int len_p = (int)pattern.size();
    std::vector<int> table(len_p);
    table[0] = 0;
    int j = 0;
    for (int i=1; i<len_p; i++) {
        if (pattern[i] == pattern[j]) {
            table[i] = j;
            j++;
        } else {
            table[i] = j;
            j = 0;
        }
    }
    return table;
}

// KMP(Knuth–Morris–Pratt) algorithm KMP(クヌース-モリス-プラット)法
int KMP(const std::string &target, const std::string &pattern) {
    int len_t = (int)target.size(), len_p = (int)pattern.size();

    std::vector<int> table = createTable(pattern);

    // search pattern in target
    int cur_t = 0, cur_p = 0;
    while (cur_t < len_t && cur_p < len_p) {
        if (target[cur_t] == pattern[cur_p]) {
            cur_p++; cur_t++;
        } else if (cur_p == 0) {
            cur_t++;
        } else {
            cur_p = table[cur_p];
        }
    }
    if (cur_p == len_p) return cur_t - cur_p;
    return -1;
}

// check periodicity of pattern
int getPeriod(const std::string &pattern) {
    int len_p = (int)pattern.size();
    if (len_p == 1) return 0;
    if (len_p == 2) {
        if (pattern[0] == pattern[1]) return 1;
        else return 0;
    }

    std::vector<int> table = createTable(pattern);

    int len = (int)table.size();
    bool isPeriodical = true;
    int period;
    if (table[len-1] == 0) return 0;
    for (int i=len-2; i>=0; i--) {
        if (table[i] == 0) {
            period = i;
            break;
        } else if (table[i] != table[i+1] - 1) {
            isPeriodical = false;
        }
    }
    if (!isPeriodical || len%period != 0) return 0;
    else return period;
}
