#ifndef PAIR_H
#define PAIR_H

template<class T>
class pair {
public:
    T first, second;

    pair() {}
    pair(const pair<T>& p) { first = p.first; second = p.second; }
    pair(const T& first, const T& second) {
        this->first = first;
        this->second = second;
    }

    inline friend bool operator==(const pair<T>& lhs, const pair<T>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
    inline friend bool operator!=(const pair<T>& lhs, const pair<T>& rhs) {
        return lhs.first != rhs.first || lhs.second != rhs.second;
    }
};

#endif