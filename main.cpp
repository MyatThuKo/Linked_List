#include<iostream>
#include<string>
using namespace std;

class node {
private:
  string info;
  int age;
  node* next;
  node* prev;
  node* last;
  int length;
public:
  node* first;
  node();
  ~node();
  void insertItem(string item, int age);
  void deleteItem(string item);
  void printList();
  void reversePrint(node* p);
  int getLength();
  bool checkName(string name);
};

// default constructor
node::node() {
  first = NULL;
  length = 0;
}

// default deconstructor
node::~node() {
  node* p = first;
  while (first != NULL) {
    p = first;
    first = first->next;
    delete p;
  }
}

// insertion function
void node::insertItem(string item, int age) {
  node* p = new node;
  p->info = item;
  p->age = age;
  if (length == 0) {
    p->next = NULL;
    first = p;
    last = p;
    length++;
    cout << "Name added..." << endl;
  } else if (checkName(item)) {
    // checks the duplication
    cout << "No duplication is allowed..." << endl;
  } else {
    if (p->info < first->info) {
      // checks if new name is less than first name on the list
      p->next = first;
      first = p;
      length++;
      cout << "Name added..." << endl;
    } else if (p->info > first->info && first->next == NULL) {
      // checks if new name is greater than first name and the list has only one name
      first->next = p;
      p->next = NULL;
      length++;
      cout << "Name added..." << endl;
    } else if (p->info > first->info) {
      /*
      checks if the new name is greater than first name and the list has more than one name
    	Also, it checks with every single name on the list to find the right position
      */
      node* current = first;
      while (current->info < p->info) {
        node* temp = current;
        current = current->next;
        if (current->info > p->info) {
          p->next = current;
          temp->next = p;
        } else if (current->next == NULL) {
          current->next = p;
          p->next = NULL;
        }
      }
      length++;
      cout << "Name added..." << endl;
    }
  }
}

// delete function
void node::deleteItem(string item) {
  if (length == 0) {
    cout << "EMPTY LIST!" << endl;
  } else {
    node *p = first;
    if (first->info == item){
      first = first->next;
      length--;
      cout << "Name deleted..." << endl;
    } else {
      while (p->next != NULL && p->next->info != item)
      p = p->next;
      if (p->next != NULL) {
        node*t = p->next;
        p->next = p->next->next;
        delete t;
        length--;
        cout << "Name deleted..." << endl;
      } else {
        cout << "Item not found!" << endl;
      }
    }
  }
}

// print function
void node::printList() {
  node* p = first;
  while (p != NULL) {
    cout << "Name: " << p-> info << ", Age: " << p->age << endl;
    p = p->next;
  }
}

// function to print the list in reversed order
void node::reversePrint(node* p) {
  if (p != NULL) {
    reversePrint(p->next);
    cout << "Name: " << p->info << ", Age: " << p->age << endl;
  }
}

// get length function
int node::getLength() {
  return length;
}

// to check the duplication in the list
bool node::checkName(string name) {
  bool found = false;
  node* p = first;
  while (!found && p != NULL) {
    if (name == p->info) {
      found = true;
    } else if (name > p->info) {
      p = p->next;
    } else {
      break;
    }
  }
  return found;
}

int main() {

  node obj;
  string name;
  string choice;
  int age;

  cout << "This program will add, and delete names and age...";
  cout << "\nAlso, will print the list in sorted order or reversed order..." << endl;

  cout << "Enter \'A\' to add" << endl;
  cout << "Enter \'D\' to delete" << endl;
  cout << "Enter \'L\' to print in sorted order" << endl;
  cout << "Enter \'R\' to print in reversed order" << endl;
  cout << "Enter \'Q\' to quit" << endl;

  while (choice != "Q") {
    cout << "Select your menu choice: ";
    cin >> choice;
    if (choice == "A") {
      cout << "Enter the name and age to add: ";
      cin >> name;
      cin >> age;
      obj.insertItem(name, age);
    } else if (choice == "D") {
      cout << "Enter the name to delete: ";
      cin >> name;
      obj.deleteItem(name);
    } else if (choice == "L") {
      if (obj.getLength() != 0) {
        cout << "The list has " << obj.getLength() << " items." << endl;
        obj.printList();
        cout << endl;
      } else {
        cout << "Empty list" << endl;
      }
    } else if (choice == "R") {
      if (obj.getLength() != 0) {
        cout << "The reversed list has " << obj.getLength() << " items." << endl;
        obj.reversePrint(obj.first);
        cout << endl;
      } else {
        cout << "Empty List" << endl;
      }
    } else if (choice == "Q") {
      cout << "Quit" << endl;
    } else {
      cout << "Invalid input!" << endl;
    }
  }
  return 0;
}
