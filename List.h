#pragma once
template<typename type>
class List {
private:
    struct Node
    {
        type data;
        Node* next;
        Node* prev;

        Node(const type& _data) : data(_data), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    List()
    {
        head = new Node(type());
        tail = new Node(type());
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~List()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addFront(type data) {
        Node* newNode = new Node(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        size++;
    }

    void addBack(type data) {
        Node* newNode = new Node(data);
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;
        size++;
    }
    void addAt(type data, int index) {
        if (index > size || index < 0) return;

        Node* temp = head; // no need for head->next here because we add at that index
        for (int i = 0; i < index; i++)
        {
            if (temp->next == tail) break;
            temp = temp->next;
        }

        Node* newNode = new Node(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }


    void deleteFront() {
        if (head->next == tail) return;

        Node* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        size--;
    }

    void deleteBack() {
        if (tail->prev == head) return;

        Node* temp = tail->prev;
        tail->prev = temp->prev;
        temp->prev->next = tail;
        delete temp;
        size--;
    }

    void deleteAt(int index) {
        if (head->next == tail || index >= size || index < 0) return;

        Node* temp = head->next;
        for (int i = 0; i < index; i++)
        {
            if (temp->next == tail) break;
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
    }


    void readList() {
        if (size == 0) return;
        Node* temp = head->next;
        
        std::cout << "Elements of List are: " << std::endl;
        while (temp != tail) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    type& nodeAt(int index)
    {
        // if indecies are small, brute force way // 30% faster
        if (index == 0) return head->next->data;
        if (index == 1) return head->next->next->data;
        if (index == 2) return head->next->next->next->data;
        if (index == 3) return head->next->next->next->next->data;
        if (index == 4) return head->next->next->next->next->next->data;

        // if they are bigger, this way
        type ErrorReturn = type();
        if (index < 0 || index >= size) return ErrorReturn;

        Node* temp = head->next;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    int findIndex(type data)
    {
        if (size == 1) return 0;
        Node* temp = head->next;
        for (int i = 0; i < size; i++)
        {
            if (data == temp->data) return i;
            temp = temp->next;
        }
        return -1;
    }


    bool doesExist(type data)
    {
        Node* temp = head->next;
        while (temp != tail)
        {
            if (data == temp->data)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool isEmpty()
    {
        if (size > 0) return true;
        else return false;
    }

    int getSize()
    {
        return size;
    }

};