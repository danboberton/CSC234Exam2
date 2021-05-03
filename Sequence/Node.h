// FILE: Node.h
// PROVIDES: A class for a Node in a linked list, and list manipulation
// functions, all within the namespace main_savitch_5
//
// TYPEDEF for the Node class:
//     Each Node of the list contains a piece of data and a pointer to the
//     next Node. The type of the data is defined as Node::value_type in a
//     typedef statement. The value_type may be any
//     of the built-in C++ classes (int, char, ...) or a class with a copy
//     constructor, an assignment operator, and a test for equality (x == y).
//
// CONSTRUCTOR for the Node class:
//   Node(
//     const value_type& init_data = value_type(),
//     Node* init_link = NULL
//   )
//     Postcondition: The Node contains the specified data and link.
//     NOTE: The default value for the init_data is obtained from the default
//     constructor of the value_type. In the ANSI/ISO standard, this notation
//     is also allowed for the built-in types, providing a default value of
//     zero. The init_link has a default value of NULL.
//
// NOTE:
//   Some of the functions have a return value which is a pointer to a Node.
//   Each of these  functions comes in two versions: a non-const version (where
//   the return value is Node*) and a const version (where the return value
//   is const Node*). 
// EXAMPLES:
//    const Node *c;
//    c->link( ) activates the const version of link
//    list_search(c,... calls the const version of list_search
//    Node *p;
//    p->link( ) activates the non-const version of link
//    list_search(p,... calls the non-const version of list_search
//
// MEMBER FUNCTIONS for the Node class:
//   void set_data(const value_type& new_data)
//     Postcondition: The Node now contains the specified new data.
//   
//   void set_link(Node* new_link)
//     Postcondition: The Node now contains the specified new link.
//
//   value_type data( ) const
//     Postcondition: The return value is the data from this Node.
//
//   const Node* link( ) const <----- const version
//   Node* link( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this Node.
//   
// FUNCTIONS in the linked list toolkit:
//   size_t list_length(const Node* head_ptr)
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The value returned is the number of Nodes in the linked
//     list.
//
//   void list_head_insert(Node*& head_ptr, const Node::value_type& entry) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: A new Node containing the given entry has been added at
//     the head of the linked list; head_ptr now points to the head of the new,
//     longer linked list.
//
//   void list_insert(Node* previous_ptr, const Node::value_type& entry) 
//     Precondition: previous_ptr points to a Node in a linked list.
//     Postcondition: A new Node containing the given entry has been added
//     after the Node that previous_ptr points to.
//
//   const Node* list_search(const Node* head_ptr, const Node::value_type& target) 
//   Node* list_search(Node* head_ptr, const Node::value_type& target) 
//   See the note (above) about the const version and non-const versions:
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The pointer returned points to the first Node containing
//     the specified target in its data member. If there is no such Node, the
//     null pointer is returned.
//
//   const Node* list_locate(const Node* head_ptr, size_t position) 
//   Node* list_locate(Node* head_ptr, size_t position) 
//   See the note (above) about the const version and non-const versions:
//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0.
//     Postcondition: The pointer returned points to the Node at the specified
//     position in the list. (The head Node is position 1, the next Node is
//     position 2, and so on). If there is no such position, then the null
//     pointer is returned.
//
//   void list_head_remove(Node*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list, with at
//     least one Node.
//     Postcondition: The head Node has been removed and returned to the heap;
//     head_ptr is now the head pointer of the new, shorter linked list.
//
//   void list_remove(Node* previous_ptr) 
//     Precondition: previous_ptr points to a Node in a linked list, and this
//     is not the tail Node of the list.
//     Postcondition: The Node after previous_ptr has been removed from the
//     linked list.
//
//   void list_clear(Node*& head_ptr) 
//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: All Nodes of the list have been returned to the heap,
//     and the head_ptr is now NULL.
//
//   void list_copy(const Node* source_ptr, Node*& head_ptr, Node*& tail_ptr) 
//     Precondition: source_ptr is the head pointer of a linked list.
//     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
//     a new list that contains the same items as the list pointed to by
//     source_ptr. The original list is unaltered.
//  void list_piece(
//    const Node* start_ptr, const Node* end_ptr, 
//    Node*& head_ptr, Node*& tail_ptr
//  )
//    Precondition: start_ptr and end_ptr are pointers to Nodes on the same
//    linked list, with the start_ptr Node at or before the end_ptr Node
//    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
//    new list that contains the items from start_ptr up to but not including 
//    end_ptr.  The end_ptr may also be NULL, in which case the new list 
//    contains elements from start_ptr to the end of the list.
//
// DYNAMIC MEMORY usage by the toolkit: 
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: the constructor, list_head_insert, list_insert, list_copy,
//   list_piece.

#pragma once
#include <cstdlib> // Provides size_t and NULL

    class Node
    {
    public:
        typedef double value_type;

        // CONSTRUCTOR
        Node(const value_type& init_data = value_type(), Node* init_link = NULL);

        // Member functions to set the data and link fields:
        void set_data(const value_type& );
        void set_link(Node* );

        // Constant member function to retrieve the current data:
        value_type data() const;

        // Two slightly different member functions to retreive
        // the current link:
        const Node* link() const;
        Node* link();

        friend Node* list_locate(Node* , std::size_t );
        friend std::size_t list_length(Node* );
        friend void list_head_insert(Node*& , const Node::value_type& );
        friend void list_insert(Node* , const Node::value_type& );
        friend Node* list_search(Node* , const Node::value_type& );
        friend void list_head_remove(Node*& );
        friend void list_remove(Node* );
        friend void list_copy(const Node* , Node*& , Node*& );
        friend void list_piece(Node* , Node* , Node*& , Node*& );
        friend size_t list_occurrences(Node* , const Node::value_type& );
        friend Node::value_type list_remove_at(Node*& , size_t );

    private:
        value_type data_field;
        Node* link_field;
    };



