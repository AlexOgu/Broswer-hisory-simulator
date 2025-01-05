#include <iostream>
#include <stdexcept>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
  m_data = data;
  m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
  return m_data;
}


//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data ) {
  m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
  m_next = next;
}

//**********Stack Class Declaration***********
template <typename T> //Indicates linked list is templated
class Stack {
public:
  Stack();
  ~Stack();
  Stack(const Stack& source);
  Stack<T>& operator=(const Stack& other);
  void Push(const T& value);

  T Pop();
  T Peek() const;
  T At(int num);

  bool IsEmpty() const;
  T RemoveBottom();
  void Display();
  size_t GetSize() const;  
private:
  Node<T>* m_top; //Top node in stack
  size_t m_size; //Number of nodes in stack
};


template <typename T>
Stack<T>::Stack() :
m_top(nullptr),
m_size(0) {}

template <typename T>
Stack<T>::~Stack() {

    // This will start from the beginning and move to the next
    Node<T>* current = m_top;
    while (current != nullptr) {
        Node<T>* next = current->GetNext();
        delete current;
        current = next;
    }
    m_top = nullptr;
    m_size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack& source) {
    if (source.m_top != nullptr) {

        // This will check if the stacks are empty
        m_top = new Node<T>(source.m_top->GetData());
        Node<T>* main_target = source.m_top->GetNext();
        Node<T>* destination = m_top;
        while (main_target != nullptr) {
            Node<T>* newNode = new Node<T>(main_target->GetData());
            destination->SetNext(newNode);
            destination = newNode;
            main_target = main_target->GetNext();
        }
    } else {
        m_top = nullptr;
    }

    //This copies the size
    m_size = source.m_size;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this == &other) return *this;
    while (m_top) {
        Node<T>* temp = m_top;
        m_top = m_top->GetNext();
        delete temp;
    }
    
    //This will copy the other stack
    if (other.m_top) {
        m_top = new Node<T>(other.m_top->GetData());
        Node<T>* destination = m_top;
        for (Node<T>* main_target = other.m_top->GetNext(); 
        main_target; main_target = main_target->GetNext()) {
            destination->SetNext(new Node<T>(main_target->GetData()));
            destination = destination->GetNext();
        }
    }
    m_size = other.m_size;
    return *this;
}

template <typename T>
void Stack<T>::Push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->SetNext(m_top);
    m_top = newNode;
    m_size++;
}

template <typename T>
T Stack<T>::Pop() {
    T data = m_top->GetData();
    Node<T>* temp = m_top;
    m_top = m_top->GetNext();
    delete temp;
    return m_size--, data;
}

template <typename T>
T Stack<T>::Peek() const {
    return m_top->GetData();
}

template <typename T>
T Stack<T>::At(int num) {
    if (m_top == nullptr || num < 0 || num >= static_cast<int>(m_size)) {
        return T(); 
    }
    Node<T>* current = m_top;
    for (int i = 0; i < num; i++) {

        //Moves on to the next node
        current = current->GetNext();
    }
    return current->GetData();
}

template <typename T>
bool Stack<T>::IsEmpty() const {
    return m_top == nullptr;
}

template <typename T>
T Stack<T>::RemoveBottom() {
    T data; 
    if (!m_top->GetNext()) { 
        data = m_top->GetData();
        delete m_top;
        m_top = nullptr;
    } else {
        Node<T>* current = m_top;
        while (current->GetNext()->GetNext()) 
            current = current->GetNext();

        // Goes throught the nodes and updates them
        Node<T>* bottom = current->GetNext();
        data = bottom->GetData();
        delete bottom;
        current->SetNext(nullptr);
    }
    m_size--;
    return data; 
}

template <typename T>
void Stack<T>::Display() {
    Node<T>* current = m_top;
    int count = 1;

    //This will number the websites
    while (current != nullptr) {
        cout << count++ << ". " << current->GetData() << endl;
        current = current->GetNext();
    }
}

template <typename T>
size_t Stack<T>::GetSize() const {
    return m_size;
}




