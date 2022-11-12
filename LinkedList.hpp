#ifndef ADDR_H
#define ADDR_H

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

#endif