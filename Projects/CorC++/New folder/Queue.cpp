#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated linked list
//Note: Because the linked list is a templated class,
//      there is only ONE file (Queue.cpp)

//Templated node class
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
void Node<T>::SetData( const T& data ) {
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

template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
  Queue();
  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
 ~Queue();
  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
  Queue(const Queue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
  Queue<T>& operator= (Queue&);
  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
  void PushBack(const T&);
  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
  T PopFront();
  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T);
  // Name: Clear
  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();
  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T& At (int x);
  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
  void Swap(int);
  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (may use overloaded < or >).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < or > is overloaded
  //        Uses bubble sort and Swap function above.
  //        Ensure working with queue_test before rest of project.
  // Note: Allowed to use the break command in just this function if necessary
  void Sort();
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Queue Class Here***********
//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Movie here*****************





#endif
