#ifndef NEWPAIR_H
#define NEWPAIR_H


template<typename T1, typename T2>
class NewPair {
public:
    T1 first;
    T2 second;

    NewPair() : first(T1()), second(T2()) {}
    NewPair(const T1& first, const T2& second) : first(first), second(second) {}

    bool operator==(const NewPair& other) const {
        return first == other.first && second == other.second;
    }

    bool operator!=(const NewPair& other) const {
        return !(*this == other);
    }
};

#endif // NEWPAIR_H
