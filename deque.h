#ifndef deque_h 
#define deque_h 
#include <stdexcept>
#include <iostream>

template <typename T> 
class deque{
    class node{
        T data;
        node* next, * prev;
        node(T x){
            data = x;
        }
        friend class deque;
    };

    node* first;
    unsigned long sz;
public: 

    deque (){ 
        first = NULL;
        sz = 0;
    }

    T front(){
        if (first == NULL)
            throw std::bad_exception();
        return first->data;
    }

    T back(){
        if (first == NULL)
            throw std::bad_exception();
        return (first->prev)->data;
    }

    deque& push_back(T elem){ //вставка элемента в конец дека
        node* ptr = new node(elem);
        if (ptr == NULL) 
            return *this;
        ++sz;
        if (first == NULL) {
            first = ptr;
            ptr->next = ptr;
            ptr->prev = ptr;
            return *this;
        }
        first->prev->next = ptr; //переменная prev хранит указатель на последний элемент в деке 
        ptr->prev = first->prev;
        first->prev = ptr;
        ptr->next = first;
        return *this;
    } 

    deque& push_front(T elem){ //вставка элемента в начало дека 
        node* ptr = new node(elem);
        if (ptr == NULL)
            return *this;
        ++sz;
        if (first == NULL){
            first = ptr;
            ptr->next = ptr;
            ptr->prev = ptr;
            return *this;
        }
        first->prev->next = ptr;
        ptr->prev = first->prev;
        ptr->next = first;
        first->prev = ptr;
        first = ptr;
        return *this; 
    } 

    deque& pop_back(){ //удаление элемента с конца 
        if (first == NULL) 
            return *this;
        node* ptr = first->prev; //указатель на удаляемый элемент 
        (ptr->prev)->next = first;
        first->prev = ptr->prev;
        if (first == ptr)
            first = NULL;
        delete ptr;
        --sz;
        return *this; 
    }

    deque& pop_front(){ //удаление элемента с начала 
        if (first == NULL)
            return *this;
        node* ptr = first; //указатель на удаляемый элемент 
        (ptr->next)->prev = ptr->prev;
        (ptr->prev)->next = ptr->next;
        if (first->next == first)
            first = NULL;
        else
            first = first->next;
        delete ptr;
        --sz;
        return *this; 
    }

    T& operator [](long long num){ //оператор возвращающий i-ый элемент в деке (отчёт с нуля)
        if (first == NULL)
            throw std::invalid_argument("There isn't any elements in deque");
        node* ptr = first;
        for (long long i = 0; i < num; ++i)
            ptr = ptr->next;
        for (long long i = 0; i > num; --i)
            ptr = ptr->prev;
        return ptr->data;
    }

    unsigned long size(){ //возвращает количество элементов в деке 
        return sz;
    }

    bool search_with_key(unsigned* equal_elems, T key){ //ищет элементы со значением key и заполняет их номерами массив equal_elems (нумерация начинается с 1) 
        node* p = first;
        if (equal_elems == NULL)
            return 0;
        equal_elems[0] = 1; 
        unsigned num = 1;
        do {
            if (p->data == key) 
                equal_elems[equal_elems[0]++] = num; 
            p = p->next;
            ++num; 
        } while (p != this && p != NULL); 
        --equal_elems[0];
        return 1; 
    } 
};

template <typename T> 
void print_deque(deque <T>& a){
    unsigned long sz = a.size();
    if (sz) {
        std::cout << "Дек состоит из " << sz << " элемент";
        if (sz % 10 != 1 || sz % 100 == 11)
            std::cout << "ов" << std::endl;
        else
            std::cout << "а" << std::endl;
    }
    else
        std::cout << "Дек пуст" << std::endl;
    for (unsigned i = 0; i < sz; ++i)
        printf("%d-й элемент из дека:\t% 2d\n", i+1, a[i]);
        //std::cout << '\t' << i+1 << "-й элемент из дека: " << a[i] << std::endl;
} 

 
#endif 