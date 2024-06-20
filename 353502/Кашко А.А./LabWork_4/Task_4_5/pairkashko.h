#ifndef PAIRKASHKO_H
#define PAIRKASHKO_H

template<typename T1, typename T2>
class PairKashko {
public:
    T1 first;
    T2 second;

    PairKashko() : first(T1()), second(T2()) {}
    PairKashko(const T1& first, const T2& second) : first(first), second(second) {}

    bool operator==(const PairKashko& other) const {
        return first == other.first && second == other.second;
    }

    bool operator!=(const PairKashko& other) const {
        return !(*this == other);
    }
};

#endif // PAIRKASHKO_H
