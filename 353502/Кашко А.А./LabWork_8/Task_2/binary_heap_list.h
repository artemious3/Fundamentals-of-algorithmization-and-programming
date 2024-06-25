#include <memory>

struct Node {
    int value;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int val) : value(val) {}
};

class BinaryHeapList {
public:
    BinaryHeapList();
    void insert(int value);
    int extractMax();
    int getMax();
    std::shared_ptr<Node> getLastNode();
    bool isEmpty();
    size_t size();

private:
    std::shared_ptr<Node> root;
    size_t heapSize;

    void siftUp(std::shared_ptr<Node> node);
    void siftDown(std::shared_ptr<Node> node);
};

