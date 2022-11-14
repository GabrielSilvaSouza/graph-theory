class NodeBinaryHeap {

    public:
        float key;
        int value;

        NodeBinaryHeap(int, float);
};

NodeBinaryHeap::NodeBinaryHeap(int new_key = 0, float new_value = 0.0f) { // O(1)

    this->key = new_key;
    this->value = new_value;
}