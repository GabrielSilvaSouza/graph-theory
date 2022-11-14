#include "NodeLinkedList.hpp"

class LinkedList {
    
    public:
        NodeLinkedList* head;
        int size;

        LinkedList();
        void insert(int, float);
};

LinkedList::LinkedList() { // O(1)

    head = nullptr;
    size = 0;
}

void LinkedList::insert(int new_data_int = 0, float new_data_float = 0.0f) { // O(1)

    if (head == nullptr) {
        head = new NodeLinkedList(new_data_int, new_data_float);
    } else {
        NodeLinkedList* new_node = new NodeLinkedList(new_data_int, new_data_float);
        new_node->next_node = head;
        this->head= new_node;
    }
    
    size++;
}