// FILE: Node1.cxx
// IMPLEMENTS: The functions of the Node class and the
// linked list toolkit (see Node1.h for documentation).
// INVARIANT for the Node class:
//   The data of a Node is stored in data_field, and the link in link_field.

#include "Node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
using namespace std;

// Constructor
template <typename value_type>
Node<value_type>::Node(const value_type& init_data, Node* init_link)
{
    data_field = init_data;
    link_field = init_link;
}

// Member functions to set the data and link fields:
template <typename value_type>
void Node<value_type>::set_data(const value_type& new_data) { data_field = new_data; }
template <typename value_type>
void Node<value_type>::set_link(Node* new_link) { link_field = new_link; }

// Constant member function to retrieve the current data:
template <typename value_type>
value_type Node<value_type>::data() const { return data_field; }

// Two slightly different member functions to retreive
// the current link:
template <typename value_type>
const Node<value_type>* Node<value_type>::link() const { return link_field; }
template <typename value_type>
Node<value_type>* Node<value_type>::link() { return link_field; }

