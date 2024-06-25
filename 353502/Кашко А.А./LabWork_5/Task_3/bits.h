#ifndef BITS_H
#define BITS_H
#include <QVector>

class Bits
{
public:
    explicit Bits(int size);
    Bits(Bits const &other);

    void resize(size_t newSize);
    bool all();
    bool any();
    int count();
    void flip();
    void flip(int index);
    bool none();
    void reset();
    void reset(int index);
    int get(int index);
    void set();
    void set(int index);
    void checkIndex(int index);
    bool test(int index);
    size_t getSize() const;

    QString to_string();
    unsigned long long to_ullong();
    unsigned long to_ulong();

    bool operator[](size_t index);

    void setType(int value);

private:
    QVector <int> bits;
    size_t bit_size;
    int type;
};


#endif // BITS_H
