#include <vector>

class BinaryHeapArray {
public:
    BinaryHeapArray();
    void insert(int value);
    int extractMax();
    int getMax();
    bool isEmpty();
    size_t size();

private:
    std::vector<int> heap;

    void siftUp(int index);
    void siftDown(int index);
};
