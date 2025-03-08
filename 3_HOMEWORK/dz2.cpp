#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;


class Client {
    static inline unsigned total_count {0};         // данный счетчик общий для всех экземпляров класса и показывает сколько клиентов находится во всех списках
    int current_total = 0;                          // данный счетчик для каждого отдельного списка

    char *surname;
    char create_time[80];

    public:
        void set_time() {
            time_t t = time(0);

            struct tm tstruct;
            tstruct = *localtime(&t);
            strftime(this -> create_time, sizeof(create_time), "%H:%M %d.%m.%Y", &tstruct);
        };

        Client() {total_count++; set_time();};      // При добавлении клиента в список будет увеличиваться общий счетчик

        Client(const char *s) {
            this -> surname = new char[strlen(s) + 1];
            strcpy(this -> surname, s);
            set_time();
        };

        ~Client() {
            total_count--;
        }

        char* get_surname() {
            return this -> surname;
        }

        char *get_create_time() {
            return this -> create_time;
        }

        static int get_count() {
            return total_count;
        }

        int get_current_count() {
            return current_total;
        }

        void set_current_total(int total) {
            this -> current_total = total;
        }

};


struct Node {
    Client item;     
    Node *next,*prev; 
};

class List {
    Node *first, *last;
    void change_current_count() {
        Node *temp = first;
        int count = size();
        while (temp != nullptr) {
            temp -> item.set_current_total(count);
            temp = temp -> next;
        }
    }
    public:
        List():first(nullptr), last(nullptr){};

        ~List(){
            Node *curr;
            while (first != nullptr) {
                curr = first;
                first = first -> next;
                delete curr;
            }
        }

        void print() {
            Node *temp = first;
            while (temp != nullptr) {
                cout << temp -> item.get_surname() << endl;
                cout << temp -> item.get_create_time() << endl;
                temp = temp -> next;
            }
        }

        void push_front(const Client &client) {
            Node *temp = new Node;
            temp -> item = client;
            temp -> prev = nullptr;
            temp -> next = first;
            if (first != nullptr) {
                first -> prev = temp;
            }
            first = temp;
            if (last == nullptr) {
                last = temp;
            }
            change_current_count();
        }

        void push_back(const Client &client) {
            Node *temp = new Node;
            temp -> item = client;
            temp -> prev = last;
            temp -> next = nullptr;
            if (last != nullptr) {
                last -> next = temp;
            }
            last = temp;
            if (first == nullptr) {
                first = temp;
            }
            change_current_count();
        }

        Client front() {
            return first -> item;
        }

        Client back() {
            return last -> item;
        }

        void pop_front() {
            if (first != nullptr) {
                Node *temp = first;
                first = first -> next;
                if (first != nullptr) {
                    first -> prev = nullptr;
                } else {
                    last = nullptr;
                }
                delete temp;
            }
            change_current_count();
        }

        void pop_back() {
            if (last != nullptr) {
                Node *temp = first;
                while(temp -> next != last) {
                    temp = temp -> next;
                }
                delete last;
                last = temp;
                last -> next = nullptr;
            }
            change_current_count();
        }

        int size(){
            Node *temp = first;
            int size = 0;
            while (temp != nullptr){
                size++;
                temp = temp->next; 
            }
            return size;
        }

        bool empty(){
            return first == nullptr;
        }

        void insert(int p, const Client& client){
            if (p > size() || p < 0){
                cout << "Error, pos is not true" << '\n' << '\n';
                return;
            }
            Node *when_insert = first;
            while (p > 0 && when_insert != nullptr){
                p--;
                when_insert = when_insert->next;
            }
            if (when_insert == first){
                push_front(client);
                return;
            }
            if (when_insert  == nullptr){
                push_back(client);
                return;
            }
            Node *temp = new Node;
            temp->item = client;
            temp->next = when_insert;
            temp->prev = when_insert->prev;
            temp->prev->next = temp;
            when_insert->prev = temp;
            change_current_count();
        }

        void erase(int p){
            if (p > size() || p < 0){
                cout << "Error, p is not true" << '\n' << '\n';
                return;
            }
            Node *what_delete = first;
            while (p > 0 && what_delete != nullptr){
                p--;
                what_delete = what_delete->next;
            }   
            if (what_delete != nullptr){
                if (what_delete == first){
                    pop_front();
                }
                else if (what_delete == last){
                    pop_back();
                }
                else{
                    what_delete->prev->next = what_delete->next;
                    what_delete->next->prev = what_delete->prev;
                    delete what_delete;
                }
            }
            change_current_count();
        }

        int get_current_count() {                                   // будем применять эту фукнцию по пересчету количества элементов в списке в конце каждой функции
            if (first != nullptr) {
                return first -> item.get_current_count();
            }
            return 0;
        }
};

class Queue: private List {
    int max_size;
    int len = 0;
    public:
        Queue(int size = 10): max_size(size) {};
        ~Queue() {}
        void back(Client & client) {
            if (!full()) {
                List::push_back(client);
                len++;
            }
        } 

        Client front() {
            if(!empty()) {
                return List::front();
            }
        }

        void pop() {
            if (!empty()) {
                List::pop_front();
                len--;
            }
        }

        bool empty() {
            return len == 0;
        }

        int size() {
            return len;
        }

        bool full() {
            return len == max_size;
        }

        void print() {
            List::print();
        }


};


int main () {

    Client one("Arkasha");
    Client two("Egor");
    Client three("Daniel");
    Client four("Kostya");
    Client five("Misha");

    Client uno("Semen");
    Client dos("Vova");

    // List list1, list2;

    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;
    // cout << "list is empty: " << list1.empty() << endl;
    // cout << "---------------------------------" << endl;
    // list1.push_front(one);
    // cout << "list is empty: " << list1.empty() << endl;
    // cout << "---------------------------------" << endl;
    // list1.print();
    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.push_front(two);
    // list1.print();
    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.push_back(three);
    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.push_back(four);
    // list1.print();
    // cout << "---------------------------------" << endl;
    // list1.pop_front();
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.pop_back();
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.insert(2, two);
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.insert(0, three);
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // list1.erase(1);
    // list1.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list1.get_current_count() << endl;
    // cout << "---------------------------------" << endl;

    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;

    // list2.push_front(uno);
    // list2.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list2.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;
    // list2.push_front(dos);
    // list2.print();
    // cout << "---------------------------------" << endl;
    // cout << "elements in this list: " << list2.get_current_count() << endl;
    // cout << "---------------------------------" << endl;
    // cout << "total Clients: " << Client::get_count() << endl;
    // cout << "---------------------------------" << endl;


    //--------------------------------------------------------------------------------------------------------------------------------//

    Queue queue;

    cout << queue.empty() << endl;
    queue.back(one);
    queue.print();
    cout << queue.empty() << endl;
    cout << queue.size() << endl;
    queue.back(two);
    queue.print();
    cout << queue.front().get_surname() << endl;
    queue.pop();
    queue.print();

}
