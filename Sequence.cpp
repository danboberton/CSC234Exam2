/*

CSC 234 Class Lab

FILE: Sequence.cxx
CLASS IMPLEMENTED: Sequence (see Sequence.h for documentation)
INVARIANT for the Sequence class:
	1. The items are stored in their Sequence order in a linked list.
	2. The head pointer of the list is stored in the member variable head_ptr.
	   If the list is empty, head_ptr is NULL.
	3. The tail pointer of the list is stored in the member variable tail_ptr.
	   If the list is empty, tail_ptr is NULL.
	4. The number of items in the list is stored in the member variable many_Nodes.
	5. The current item is stored in the member variable cursor.
	6. The item before the current item is stored in the member variable precursor.
	7. If there is no current item, then cursor and precursor are NULL.
*/

#include <cassert>
#include "Node.h"
#include "Sequence.h"
using namespace std;

// Friend and Helper Functions
template <typename value_type>
void list_insert(Node<value_type>* previous_ptr, const value_type& entry) 
{
    Node<Sequence::value_type> *insert_ptr;
    
    insert_ptr = new Node<Sequence::value_type>;
    insert_ptr->data_field = entry;
    insert_ptr->link_field = previous_ptr->link_field;
    previous_ptr->link_field = insert_ptr;
}

template <typename value_type>
void list_head_insert(Node<value_type>*& head_ptr, const value_type& entry)
{
    Node<Sequence::value_type>* insert_ptr;

    insert_ptr = new Node<Sequence::value_type>;
    insert_ptr->data_field = entry;
    insert_ptr->link_field = head_ptr;
    head_ptr = insert_ptr;
}

template <typename value_type>
void list_head_remove(Node<value_type>*& head_ptr)
{
    Node<Sequence::value_type> *remove_ptr;

    remove_ptr = head_ptr;
    head_ptr = head_ptr->link_field;
    delete remove_ptr;
}

template <typename value_type>
void list_remove(Node<value_type>* previous_ptr)
{
    Node<Sequence::value_type> *remove_ptr;

    remove_ptr = previous_ptr->link_field;
    previous_ptr->link_field = remove_ptr->link_field;
    delete remove_ptr;
}

template <typename value_type>
void list_copy(const Node<value_type>* source_ptr, Node<value_type>*& head_ptr, Node<value_type>*& tail_ptr) 
// Library facilities used: stdlib.h
{
    head_ptr = NULL;
    tail_ptr = NULL;

    // Handle the case of the empty list
    if (source_ptr == NULL)
        return;
    
    // Make the head node for the newly created list, and put data in it
    list_head_insert(head_ptr, source_ptr->data_field);
    tail_ptr = head_ptr;
    
    // Copy the rest of the nodes one at a time, adding at the tail of new list
    for (source_ptr = source_ptr->link_field; source_ptr != NULL; source_ptr = source_ptr->link_field)
    {
        list_insert(tail_ptr, source_ptr->data_field);
        tail_ptr = tail_ptr->link_field;
    }
}

template <typename value_type>
void list_piece(Node<value_type>* start_ptr, Node<value_type>* end_ptr, Node<value_type>*& head_ptr, Node<Sequence::value_type>*& tail_ptr)
// Library facilities used: stdlib.h
{
    head_ptr = NULL;
    tail_ptr = NULL;

    // Handle the case of the empty list
    if (start_ptr == NULL)
        return;
    
    // Make the head node for the newly created list, and put data in it
    list_head_insert(head_ptr, start_ptr->data_field);
    tail_ptr = head_ptr;
    if (start_ptr == end_ptr)
        return;
    
    // Copy the rest of the nodes one at a time, adding at the tail of new list
    for (start_ptr = start_ptr->link_field; start_ptr != NULL; start_ptr = start_ptr->link_field)
    {
        list_insert(tail_ptr, start_ptr->data_field);
        tail_ptr = tail_ptr->link_field;
        if (start_ptr == end_ptr) 
            return;
    }
}

void list_clear(Node<Sequence::value_type>*& head_ptr)
// Library facilities used: stdlib.h
{
    while (head_ptr != NULL)
        list_head_remove<long>(head_ptr);
}


//CONSTRUCTOR, COPY CONSTRUCTOR, & DESTRUCTOR
Sequence::Sequence()
{
	head_ptr = NULL;
	tail_ptr = NULL;
	cursor = NULL;
	precursor = NULL;
	many_nodes = 0;
}

Sequence::Sequence(const Sequence& source)
{
	if (source.cursor == NULL) {
		//Source is empty
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = NULL;
		precursor = NULL;
	} else if (source.cursor == source.head_ptr){
		//Source does not have a mid-Sequence current item
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = head_ptr;
		precursor = NULL;
	} else {
		//Source's current item is mid-Sequence
		//NOTE: See modified Node class for added list_piece function
		list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
		list_piece(source.cursor, NULL, cursor, tail_ptr);
		precursor->set_link(cursor);
	}
	many_nodes = source.many_nodes;
}

Sequence::~Sequence( )
{
	list_clear(head_ptr);
	many_nodes = 0;
}

//ASSIGNMENT OPERATOR
void Sequence::operator =(const Sequence& source)
{
	if (this == &source) //Self-assignment test
		return;

	list_clear(head_ptr); //Clear calling Sequence
	many_nodes = 0;

	if (source.cursor == NULL) {
		//No current item in source
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = NULL;
		precursor = NULL;			
	} else if (source.cursor == source.head_ptr) {
		//Current item is head of the list in source
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		cursor = head_ptr;
		precursor = NULL;
	} else {
		//Current item is mid-Sequence in source
		//Source's current item is mid-Sequence
		//NOTE: See modified Node class for added list_piece function
		list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
		list_piece(source.cursor, NULL, cursor, tail_ptr);
		precursor->set_link(cursor);
	}
	many_nodes = source.many_nodes;
}

//MODIFIERS
void Sequence::start( )
{
	precursor = NULL;
	cursor = head_ptr;
}

void Sequence::advance( )
{
	if (cursor == NULL) //No current item
		return;

	precursor = cursor; //Now at head_ptr if previously NULL
	cursor = cursor->link();

	//If the cursor falls off the tail, the precursor resets too
	if (cursor == NULL)
		precursor = NULL;
}

void Sequence::insert(const value_type& entry)
{
	if (many_nodes == 0)
	//Empty list, add first Node
	{      
		// to be completed
	}
	else if (cursor == NULL || cursor == head_ptr)
	//Non-emtpy list without a current item or with current item at head
	{
		list_head_insert(head_ptr, entry);
		cursor = head_ptr; 
		//Precursor already NULL in this case;
	}
	else
	//Must add between precursor and cursor     
	{
	// to be completed
	}
	++many_nodes;
}

void Sequence::attach(const value_type& entry)
{
	if (many_nodes == 0)
	//Empty list, add first Node
	{
		Node<value_type>* newNode = new Node<value_type>(entry, NULL);
		initSequence(newNode);

	//Precursor already NULL in this case
	}
	else if (cursor == NULL || cursor == tail_ptr)
	//Non-empty list without a current item or with current item at tail
	{
		list_insert(tail_ptr, entry);
		precursor = tail_ptr;
		tail_ptr = tail_ptr->link();
		cursor = tail_ptr;
	}
	else 
	//Attach new Node after cursor
	{
		Node<value_type>* newNode = new Node<value_type>(entry, NULL);
		list_insert(newNode, entry);
	}
	++many_nodes;
}

void Sequence::remove_current( )
{

	assert(is_item());
	if (cursor == head_ptr)
	{
		list_head_remove(head_ptr);
	}
	else
	{
		cursor = cursor->link();
		//advance function ensures precursor is never at the tail Node
		list_remove(precursor); 
	}
	--many_nodes;
}

Sequence::value_type Sequence::current() const
{
	assert(is_item());
	return cursor->data();

}

void Sequence::initSequence(Node<value_type>* newNode){
	head_ptr = newNode;
	tail_ptr = newNode;
	cursor = newNode;
	precursor = NULL;
}

