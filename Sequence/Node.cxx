// FILE: Node1.cxx
// IMPLEMENTS: The functions of the Node class and the
// linked list toolkit (see Node1.h for documentation).
// INVARIANT for the Node class:
//   The data of a Node is stored in data_field, and the link in link_field.

#include "Node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
using namespace std;

Node::Node(const value_type& init_data, Node* init_link)
{
    data_field = init_data; link_field = init_link;
}

// Member functions to set the data and link fields:
void Node::set_data(const value_type& new_data) { data_field = new_data; }
void Node::set_link(Node* new_link) { link_field = new_link; }

// Constant member function to retrieve the current data:
Node::value_type Node::data() const { return data_field; }

// Two slightly different member functions to retreive
// the current link:
const Node* Node::link() const { return link_field; }
Node* Node::link() { return link_field; }

