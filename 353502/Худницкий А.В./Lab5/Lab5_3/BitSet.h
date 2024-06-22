#ifndef BITSET_H
#define BITSET_H

#include <QString>

class BitSet {
public:
    explicit BitSet(int size);
    ~BitSet();

    int getSize() const;

    bool operator[](int pos) const;
    bool& operator[](int pos);

    void set(int pos);
    void reset(int pos);

    void set();
    void reset();

    bool test(int pos) const;

    bool all() const;
    bool any() const;

    int count() const;

    void flip(int pos);
    void flip();

    bool none() const;

    QString to_string() const;
    unsigned long long to_ullong() const;
    unsigned long to_ulong() const;

private:
    short* data;
    int size;

};

#endif // BITSET_H
