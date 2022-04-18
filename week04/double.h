#ifndef DOUBLE_H
#define DOUBLE_H

#include "iterator.h"

template <typename T>
class DoubleListIterator : public Iterator<T> {     
    public: 
        DoubleListIterator() : Iterator<T>() {};
        DoubleListIterator(Node<T> *current) : Iterator<T>(current) {};
        DoubleListIterator<T>& operator++();//++it
        DoubleListIterator<T>& operator--();//--it        
};

template <typename T>
class DoubleList : public List<T>{     
    public:
        typedef DoubleListIterator<T> iterator;
                 
    public:
        DoubleList() : List() { }

        void push_front(T value) override {
            auto new_node = new Node<T>(value);

            if(this->empty()){
                this->head = new_node;
                this->tail = new_node;
            }else{
                auto tmp = this->head;
                this->head = new_node;
                tmp->prev = this->head;
                this->head->next = tmp;
            }
            this->nodes++;
        }

        void push_back(T value)override {
            auto new_node = new Node<T>(value);

            if(this->empty()){
                this->head = new_node;
                this->tail = new_node;
            }else{
                this->tail->next = new_node;
                new_node->prev = this->tail;
                this->tail = new_node;
            }

            this->nodes++;
        }

        T pop_front()override {
            if (this->empty()) {
                return 0;
            }

            auto tmp = this->head;
            auto ret = this->head->data;
            this->head = this->head->next;
            this->head->prev = nullptr;
            delete tmp;
            this->nodes--;
            return ret;
        }

        T pop_back()override {
            if (this->empty()) {
                return 0;
            }

            auto tmp = this->tail;
            auto ret = this->tail->data;
            //this->tail = this->tail->prev;

            this->tail = this->tail->prev;
            this->tail = nullptr;

            delete tmp;
            this->nodes--;
            return ret;
        }

        T insert(T val, int pos)override {
            if(pos > this->size()){
                return -1;
            }
            if(this->empty()){
                return -1;
            }

            if(pos == 0){
                this->push_front(val);
                return val;
            }

            if(pos == this->size()-1){
                this->push_back(val);
                return val;
            }

            auto newnode = new Node<T>(val);

            auto tmp_prev = this->head;

            for(auto i = 0; i < pos - 1; i++){
                tmp_prev = tmp_prev->next;
            }
            newnode->next = tmp_prev->next;
            tmp_prev->next->prev = newnode;

            tmp_prev->next = newnode;
            newnode->prev = tmp_prev;

            tmp_prev = nullptr;
            delete tmp_prev;
            this->nodes++;
        }

        void remove(int pos)override {
            if(pos == 0){
                this->pop_front();
                return;
            }

            if(pos == this->size()-1){
                this->pop_back();
                return;
            }

            if(pos > this->size()){
                return;
            }
            if(this->empty()){
                return;
            }

            auto tmp_prev = this->head;

            for(auto i = 0; i < pos - 1; i++){
                tmp_prev = tmp_prev->next;
            }

            auto tmp_nxt = tmp_prev->next;
            tmp_prev->next = tmp_nxt->next;
            tmp_nxt->next->prev = tmp_prev;

            delete tmp_prev, tmp_nxt;
            this->nodes--;
        }

        T operator[](int pos){
            if (is_empty()){
                throw "List is empty";
            }
            if(pos >= this->nodes){
                throw "Index no valido";
            }
            Node<T> *temp = this->head;
            int i = 0;
            while (i < pos){
                temp = temp->next;
                i++;
            }
            return temp->data;
        };

        bool is_sorted(){
            int i = 0;
            while(i< this->nodes - 1){
                if(operator[](i) > operator[](i+1)){
                    return false;
                }
                ++i;
            }
            return true;
        };

        bool is_empty(){
            return this->head == nullptr;
        };

        int size() {
            return this->nodes;
        };

        void clear() {
            while(!this->empty()){
                pop_front();
            }
        };

        void reverse(){
            Node<T> *nodo = this->head;
            Node<T> *temp = this->head;
            List<T> *list= new DoubleList<T>();
            while(nodo != nullptr){
                list->push_front(nodo->data);
                nodo = nodo->next;
            }
            int i = 0;
            while(temp != nullptr){
                temp->data = list->operator[](i);
                temp = temp->next;
                i++;
            }
        };

        std::string name(){
            return "Double List";
        };

        void display(){
            if (is_empty()){
                throw "List is empty";
            }
            Node<T>* temp = this->head;
            while(temp != nullptr){
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << endl;
        };



        /* new functions */             
        iterator begin() {
            // TODO
        }
             
        iterator end() {
            // TODO
        }      
             
        ~DoubleList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif