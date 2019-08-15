#include <vector>

// binary_search 二分探索
long long binary_searching(std::vector<long long> &str, long long key, long long imin, long long imax) {
    if (imax < imin) return -1;
    long long imid = imin + (imax - imin) / 2;
    if (str.at(imid) < key) {
        return binary_searching(str, key, imid+1, imax);
    }
    else if (str.at(imid) > key) {
        return binary_searching(str, key, imin, imid-1);
    }
    else {
        return imid;
    }
}
