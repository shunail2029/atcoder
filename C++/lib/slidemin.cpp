#include <algorithm>
#include <deque>
#include <functional>
#include <vector>

// Slide Minimum スライド最小値
template<typename T, class Compare=std::less<T> >
class SlideMin {
    private :
        std::vector<T> data;
        std::deque<int> dq;
    public :
        SlideMin(std::vector<T> a) : data(a) {};
        T get_min();
        int get_min_index();
        void push(int i);
        void pop(int i);
        int size();
};

template<typename T, class Compare>
T SlideMin<T, Compare>::get_min() {
    return data.at(dq.front());
}

template<typename T, class Compare>
int SlideMin<T, Compare>::get_min_index() {
    return dq.front();
}

template<typename T, class Compare>
void SlideMin<T, Compare>::push(int i) {
    while (!dq.empty() && Compare()(data.at(i), data.at(dq.back()))) {
        dq.pop_back();
    }
    dq.push_back(i);
}

template<typename T, class Compare>
void SlideMin<T, Compare>::pop(int i) {
    if (dq.front() == i) {
        dq.pop_front();
    }
}

template<typename T, class Compare>
int SlideMin<T, Compare>::size() {
    return (int)dq.size();
}
