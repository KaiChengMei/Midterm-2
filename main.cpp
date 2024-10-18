#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;
    // for delete randomposition
    int size;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;

        size--;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        // output 1st guy is served
        cout << temp->data << " is served" << endl ;
        size--;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
        size--;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " " << endl ;
            current = current->next;
        }
        cout << endl;
    }
    // add a get size for delete randomposition
    int get_size() const {
        return size;  // Return the current size of the list
    }

};

int main() {
    srand(time(0)); // seed for random number generator

    // load name from names.txt
    vector<string> names;
    ifstream nameFile("names.txt");
    // creat customername and vipname for later
    string name, customername, vipname;
    // for random events
    int prob;
    // for random guy in the mid of the line leave
    int randomposition;


    while (nameFile >> name) {
        names.push_back(name);
    }
    nameFile.close();

    // make a line
    DoublyLinkedList line;

    // when stor open 5 customers get in line
    cout << "Store opens:\n";
    for (int i = 0; i < 5; ++i) {
        customername = names[rand() % 99];
        line.push_back(customername);
        cout << "   " << customername << " join the line. " << endl ;
    }
    line.print();


    // simulate for 20 miniutes
    for (int minute = 1; minute <= 20; ++minute) {
        cout << "Time step #" << minute << ":" << endl ;

        prob = rand() % 100 + 1;  // returns random number 1-100
        // A customer being helped at the beginning of the line and ordering their coffee is 40%
        if (prob <= 40) {
            // delete head 
            
            line.pop_front();
        }

        prob = rand() % 100 + 1;  // returns random number 1-100
        // A new customer joining the end of the line is 60%
        if (prob <= 60) {
            // find random name and put it in the end of the line
            customername = names[rand() % 99 ];
            cout << customername << " joins the line." << endl ;
            line.push_back(customername);
        }

        prob = rand() % 100 + 1;  // returns random number 1-100
        // The customer at the end of the line deciding they don't want to wait and leaving is 20%
        if (prob <= 20) {
            // delete tail 
            cout << name[line.get_size()] << " left the line." << endl ;
            line.pop_back();
        }

        prob = rand() % 100 + 1;  // returns random number 1-100
        // Any particular customer can decide they don't want to wait and leave the line: 10%
        if (prob <= 10) {
            // random people leave
            randomposition = (rand() % line.get_size()) + 1;
            cout << name[randomposition] << " left the line." << endl ;
            line.delete_pos(randomposition);
        }

        prob = rand() % 100 + 1;  // returns random number 1-100
        // A VIP (very important person) customer with a Coffee House Gold Card gets to skip the line and go straight to the counter and order: 10%
        if (prob <= 10) {
            // put vip in the front of the line
            vipname = names[rand() % 99 ];
            cout << vipname << " (VIP) joins the front of the line." << endl ;
            line.push_back(vipname);
        }

        // output the line result
        cout << "Resulting line:\n";
        line.print();

    }
    return 0;
}