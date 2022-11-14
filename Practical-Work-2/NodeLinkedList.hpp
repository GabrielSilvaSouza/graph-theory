class NodeLinkedList {

    public:
        int data_int;
        float data_float;
        NodeLinkedList* next_node;

        NodeLinkedList(int, float);
};

NodeLinkedList::NodeLinkedList(int new_data_int = 0, float new_data_float = 0.0f) { // O(1)
    
    this->data_int = new_data_int;
    this->data_float = new_data_float;
    this->next_node = nullptr;
}