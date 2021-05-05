// FILE: linkplus.cxx
// IMPLEMENTS: The 14 functions of the expanded linked list toolkit
// (see linkplus.h). The four new functions implemented at the bottom of
// the file were implemented by __________(your name and email address)____.

#include <assert.h>    // Provides assert
#include <stdlib.h>    // Provides NULL and size_t
#include "Node.h"
#include "linkplus.h"

size_t list_length(Node* head_ptr)
{
    size_t answer = 0;

    for (head_ptr = head_ptr; head_ptr != NULL; head_ptr = head_ptr->link_field)
        answer++;

    return answer;
}

void list_head_insert(Node*& head_ptr, const Node::value_type& entry)
{
    Node *insert_ptr;

    insert_ptr = new Node;
    insert_ptr->data_field = entry;
    insert_ptr->link_field = head_ptr;
    head_ptr = insert_ptr;
}

// 
void list_insert(Node* previous_ptr, const Node::value_type& entry) 
{
    Node *insert_ptr;
    
    insert_ptr = new Node;
    insert_ptr->data_field = entry;
    insert_ptr->link_field = previous_ptr->link_field;
    previous_ptr->link_field = insert_ptr;
}

Node* list_search(Node* head_ptr, const Node::value_type& target) 
// Library facilities used: stdlib.h
{
    Node *cursor;
   
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link_field)
        if (target == cursor->data_field)
            return cursor;
    return NULL;
}

Node* list_locate(Node* head_ptr, size_t position) 
// Library facilities used: assert.h, stdlib.h
{
    Node *cursor;
    size_t i;
    
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
        cursor = cursor->link_field;
    return cursor;
}

void list_head_remove(Node*& head_ptr)
{
    Node *remove_ptr;

    remove_ptr = head_ptr;
    head_ptr = head_ptr->link_field;
    delete remove_ptr;
}

void list_remove(Node* previous_ptr)
{
    Node *remove_ptr;

    remove_ptr = previous_ptr->link_field;
    previous_ptr->link_field = remove_ptr->link_field;
    delete remove_ptr;
}

void list_clear(Node*& head_ptr)
// Library facilities used: stdlib.h
{
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}

void list_copy(const Node* source_ptr, Node*& head_ptr, Node*& tail_ptr) 
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

void list_piece(Node* start_ptr, Node* end_ptr, Node*& head_ptr, Node*& tail_ptr)
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

size_t list_occurrences(Node* head_ptr, const Node::value_type& target)
{
    size_t answer = 0;

    for (head_ptr = list_search(head_ptr, target);
	 head_ptr != NULL;
	 head_ptr = list_search(head_ptr->link_field, target))
	answer++;
    
    return answer;
}

void list_insert_at(Node*& head_ptr, const Node::value_type& entry, size_t position)
{
    assert(position > 0);
    Node *precursor;
    
    if (position == 1)
	list_head_insert(head_ptr, entry);
    else
    {
	precursor = list_locate(head_ptr, position-1);
	assert(precursor != NULL);
	list_insert(precursor, entry);
    }
}

Node::value_type list_remove_at(Node*& head_ptr, size_t position)
{
    assert(position > 0);
    Node *precursor;
    Node::value_type answer;
    
    if (position == 1)
    {
	assert(head_ptr != NULL);
	answer = head_ptr->data_field;
	list_head_remove(head_ptr);
    }
    else
    {
	precursor = list_locate(head_ptr, position-1);
	assert(precursor != NULL);
	assert(precursor->link_field != NULL);
	answer = precursor->link_field->data_field;
	list_remove(precursor);
    }
    return answer;
}

Node* list_copy_segment(Node* head_ptr, size_t start, size_t finish)
{
    Node *start_ptr;
    Node *finish_ptr;
    Node *new_head;
    Node *new_tail;
    
    assert(start <= finish);
    start_ptr = list_locate(head_ptr, start);
    assert(start_ptr != NULL);
    finish_ptr = list_locate(start_ptr, finish-start+1);
    assert(finish_ptr != NULL);
    list_piece(start_ptr, finish_ptr, new_head, new_tail);
    return new_head;
}

