using namespace std;
#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <iostream>


// TODO: Implement all methods
template <typename T>
class List {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;

    public:
        List() : head(nullptr), tail(nullptr), nodes(0) {};
        ~List(){
            // TODO            
        } ;

        virtual T front(){
            return head->data;
        };

        virtual T back() {
            return tail->data;
        };

        virtual void push_front(T value) override {
            auto new_node = new Node<T>(value);

            if(this->empty()){
                this->head = new_node;
                this->tail = new_node;
            }else{
                auto tmp = this->head;
                this->head = new_node;
                this->head->next = tmp;
            }
            this->nodes++;
        }

        virtual void push_back(T value) override {

            auto new_node = new Node<T>(value);

            if(this->empty()){
                this->head = new_node;
                this->tail = new_node;
            }else{
                this->tail->next = new_node;
                this->tail = new_node;
            }

            this->nodes++;
        }

        virtual T pop_front() override {
            if (this->empty()) {
                return 0;
            }

            auto tmp = this->head;
            auto ret = this->head->data;
            this->head = this->head->next;
            delete tmp;
            this->nodes--;
            return ret;
        }

        virtual T pop_back()override {
            if (this->empty()) {
                return 0;
            }
            auto tmphead = this->head;
            auto tmp = this->tail;
            auto ret = this->tail->data;
            //this->tail = this->tail->prev;
            while(tmphead->next != this->tail){
                tmphead = tmphead->next;
            }

            this->tail = tmphead;
            tmphead = nullptr;
            delete tmp;
            delete tmphead;
            this->nodes--;
            return ret;
        }

        virtual T insert(T val, int pos)override {
            if(pos == 0){
                this->push_front(val);
                return val;
            }

            if(pos == this->size()-1){
                this->push_back(val);
                return val;
            }

            auto newnode = new Node<T>(val);

            if(pos > this->size()){
                return -1;
            }
            if(this->empty()){
                return -1;
            }

            auto tmp_prev = this->head;
            auto tmp_nxt = this->head->next;
            for(auto i = 0; i < pos - 1; i++){
                tmp_prev = tmp_nxt;
                tmp_nxt = tmp_nxt->next;
            }

            tmp_prev->next = newnode;
            newnode->next = tmp_nxt;

            tmp_prev = nullptr;
            delete tmp_prev, tmp_nxt;
            this->nodes++;
        }

        virtual bool remove(int pos) {
            if (is_empty()){
                throw "List is empty";
            }
            if(pos >= this->nodes){
                throw "Index no valido";
            }
            Node<T> *temp = this->head;
            int i = 0;
            while (i < pos-1 && temp != nullptr){
                temp = temp->next;
                i++;
            }
            Node<T> *temp1 = temp->next;
            temp->next = temp1->next;
            delete temp1;
            this->nodes--;
        };

        virtual T operator[](int val)override {
            if(val < this->nodes){
                auto tmp = this->head;
                for(int i = 0; i < val; i++){
                    tmp = tmp->next;
                }
                return tmp->data;
            }
        }

        virtual bool empty(){
            return !nodes;
        };

        virtual bool find(T) = 0;

        virtual int size(){
            return nodes;
        }

        virtual void clear(){
            while(!this->empty()){
                pop_front();
            }
        }
        virtual void sort() = 0;

        virtual bool is_sorted(){
            auto tmp = this->head;
            while(tmp->next != nullptr || tmp == this->tail){
                if (tmp->data > tmp->next->data){
                    return false;
                }
                tmp = tmp->next;
            }
            return true;
        }

        List<T>* reverse(){
            List<T>* newlist = new ForwardList<T>();
            auto tmp = this->head;
            for(;tmp != nullptr;tmp=tmp->next){
                newlist->push_front(tmp->data);
            }
            return newlist;
        }

        virtual void display(std::ostream& os) {
            if (is_empty()){
                throw "List is empty";
            }
            Node<T>* temp = this->head;
            while(temp != nullptr){
                cout << temp->data << " => ";
                temp = temp->next;
            }
            cout << endl;
        };

        virtual std::string name(){
            return "List";
        };
};

#endif