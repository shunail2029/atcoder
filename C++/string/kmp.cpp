#include <string>
#include <vector>

int KMP(const std::string &, const std::string &);
std::vector<int> createTable(const std::string &);
int getPeriod(const std::string &);

// KMP(Knuth–Morris–Pratt) algorithm KMP(クヌース-モリス-プラット)法
int KMP(const std::string &target, const std::string &pattern) {
    int len_t = (int)target.size(), len_p = (int)pattern.size();

    std::vector<int> table = createTable(pattern);

    // search pattern in target
    int cur_t = 0, cur_p = 0;
    while (cur_t < len_t && cur_p < len_p) {
        if (target.at(cur_t) == pattern.at(cur_p)) {
            cur_p++; cur_t++;
        } else if (cur_p == 0) {
            cur_t++;
        } else {
            cur_p = table.at(cur_p);
        }
    }
    if (cur_p == len_p) {
        return cur_t - cur_p;
    }
    return -1;
}

// create table
std::vector<int> createTable(const std::string &pattern) {
    int len_p = (int)pattern.size();
    std::vector<int> table(len_p);
    table.at(0) = 0;
    int j = 0;
    for (int i=1; i<len_p; i++) {
        if (pattern.at(i) == pattern.at(j)) {
            table.at(i) = j;
            j++;
        } else {
            table.at(i) = j;
            j = 0;
        }
    }
    return table;
}

// check periodicity of pattern
int getPeriod(const std::string &pattern) {
    int len_p = (int)pattern.size();
    if (len_p == 1) return -1;
    if (len_p == 2) {
        if (pattern.at(0) == pattern.at(1)) {
            return 1;
        } else {
            return -1;
        }
    }

    std::vector<int> table = createTable(pattern);

    int len = (int)table.size();
    bool isPeriodical = true;
    int period;
    if (table.at(len-1) == 0) return -1;
    for (int i=len-2; i>=0; i--) {
        if (table.at(i) == 0) {
            period = i;
            break;
        } else if (table.at(i) != table.at(i+1) - 1) {
            isPeriodical = false;
        }
    }
    if (!isPeriodical || len%period != 0) {
        return -1;
    } else {
        return period;
    }
}
