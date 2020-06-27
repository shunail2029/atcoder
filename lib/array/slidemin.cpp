#include <algorithm>
#include <deque>
#include <functional>
#include <vector>

// Slide Minimum スライド最小値
template<class T, class Compare=std::less<T>>
class SlideMin {
    private :
        std::vector<T> dat;
        std::deque<int> dq;
    public :
        SlideMin(std::vector<T> a) : dat(a) {};
        T getMin() { return dat[dq.front()]; }
        int getMinIndex() { return dq.front(); }
        void push(const int i) {
            while (!dq.empty() && Compare()(dat[i], dat[dq.back()])) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        void pop(const int i) { if (dq.front() == i) dq.pop_front(); }
        int size() { return (int)dq.size(); }
};
