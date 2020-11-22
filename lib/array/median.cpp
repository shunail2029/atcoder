#include <vector>

// median of medians
// return k-th minimum value in [first, last)
// k is 0-indexed
template<class RandomAccessIterator>
auto medianOfMedians(RandomAccessIterator first, RandomAccessIterator last, int k) {
    auto _first = *first;
    using T = decltype(_first);

    int len = last - first;
    if (len == 1 && k == 0) return *first;

    int ms = (len + 4) / 5;
    T *medians = new T[ms];
    for (int i=0; i<ms; ++i) {
        auto iter = first + 5*i;
        if (5*i + 4 < len) {
            for (int j=0; j<3; ++j) {
                int minInd = j;
                for (int k=j+1; k<5; ++k) {
                    if (*(iter+k) < *(iter+minInd)) minInd = k;
                }
                swap(*(iter+j), *(iter+minInd));
            }
            medians[i] = *(iter+2);
        } else {
            medians[i] = *iter;
        }
    }

    T pivot = medianOfMedians(medians, medians + ms, ms/2);
    delete [] medians;

    int store = 0, same = 0;
    for (int i=0; i<len; ++i) {
        if (*(first+i) < pivot) {
            if (i != store + same) swap(*(first+store), *(first+store+same));
            swap(*(first+i), *(first+store));
            ++store;
        } else if (*(first+i) == pivot) {
            swap(*(first+i), *(first+store+same));
            ++same;
        }
    }

    if (store <= k && k < store + same) return pivot;
    else if (k < store) return medianOfMedians(first, first+store, k);
    else return medianOfMedians(first+store+same, last, k-store-same);
}
