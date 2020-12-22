/*	Container.cpp
	Jayden Fullerton

	This file contains the implementation of a linked list designed to store
	pixels with red green blue values at a specific row and column. The
	implementation of the Container class is done using a standard singly
	linked list.	*/
#include "Container.h"

	/*	creates an iterator for container c
		@param	container to create an iterator on
		@pre	none
		@post	iterator is initialized for c */
Container::Iterator::Iterator(const Container& c) : super(c)
{
	if (c.head == nullptr)
		pos = nullptr;
	else
		pos = c.head;
}

/*	increments the iterator
	@pre	iterator must not already be at the end of the container
	@post	iterator is at the next item in the container */
Container::Iterator Container::Iterator::operator++(int)
{
	pos = pos->next;
	return *this;
}

/*	is the iterator at the end of the container
	@pre	none
	@post	true is returned if iterator is at the end of container, false otherwise */
bool Container::Iterator::atEnd()
{
	if (pos == nullptr)
		return true;
	return false;
}

/*	returns the data at the current spot of the iterator
	@pre	iterator must not be at the end of the container
	@post	returns data at current position of iterator */
PixelData Container::Iterator::getData()
{
	return pos->data;
}

/*	Container constructor
	@pre	none
	@post	an instance of Container is created	*/
Container::Container()
{
	head = nullptr;
	size = 0;
}

/*	Container copy constructor
	NOTE	doesn't have to be called explicitly
	@param	Container to be copied
	@pre	c must be a valid Container
	@post	a deep copy of the linked list of c
			is created and put into this Container	*/
Container::Container(const Container& c)
{
	size = 0;

	deallocate();
	// Reallocate c into this
	if (c.head == nullptr)
	{
		head = nullptr;
		return;
	}
	head = new Node;
	head->data = c.head->data;
	Node* cur1 = c.head;
	Node* cur2 = head;

	while (true)
	{
		size++;
		cur2->data = cur1->data;
		if (cur1->next == nullptr)
		{
			cur2->next = nullptr;
			return;
		}
		else
		{
			cur2->next = new Node;
			cur2 = cur2->next;
			cur1 = cur1->next;
		}
	}
}

/*	Container assignment operator (=)
	@param	right hand side of assignment
	@pre	c must be a valid Container
	@post	a deep copy of the linked list of c
			is created and put into this container
			unless it is self-assignment	*/
Container& Container::operator=(const Container& c)
{
	// Check for self-assignment
	if (this == &c)
		return *this;

	deallocate();
	// Reallocate c into this
	if (c.head == nullptr)
	{
		head = nullptr;
		return *this;
	}
	head = new Node;
	head->data = c.head->data;
	Node* cur1 = c.head;
	Node* cur2 = head;

	while (true)
	{
		cur2->data = cur1->data;
		if (cur1->next == nullptr)
		{
			cur2->next = nullptr;
			return *this;
		}
		else
		{
			cur2->next = new Node;
			cur2 = cur2->next;
			cur1 = cur1->next;
		}
	}

	return *this;
}

/*	Container destructor
	@pre	none
	@post	dynamic memory associated with this Container is now deallocated	*/
Container::~Container()
{
	deallocate();
}

/*	deallocation helper function
	@pre	none
	@post	linked list associated with this container is now deallocated */
void Container::deallocate()
{
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

/*	Add node to the end of the linked list
	@param	red value for the pixel
	@param	green value for the pixel
	@param	blue value for the pixel
	@param	row the pixel is in
	@param	column the pixel is in
	@pre	none
	@post	a new node with values given in the paramaters
			is added after the head onto the linked list	*/
void Container::addPixel(PixelData p)
{
	size++;
	if (head == nullptr)
	{
		head = new Node;
		head->data = p;
		head->next = nullptr;
		return;
	}

	Node* temp = head->next;
	head->next = new Node;
	head->next->next = temp;
	head->next->data = p;
}

/*	returns the size of this
	@pre	none
	@post	size of this is returned */
int Container::getSize() const
{
	return size;
}

/*	returns data from specific index
	@param	index to get data from
	@pre	container must be non-empty
	@post	returns PixelData from the beginning of the container */
PixelData Container::getFirst() const
{
	return head->data;
}

/*	Append c to this Container
	@param	container to merge with
	@pre	c must be a valid Container
	@post	the linked list associated with c is deep copied
			and appended to this Container	*/
void Container::merge(const Container& c)
{
	size += c.size;
	if (c.size == 0) // nothing to add
		return;
	Node* oldHead = head;
	head = new Node;
	head->data = c.head->data;
	Node* cur1 = c.head;
	Node* cur2 = head;

	while (true)
	{
		cur2->data = cur1->data;
		if (cur1->next == nullptr)
		{
			cur2->next = oldHead;
			return;
		}
		else
		{
			cur2->next = new Node;
			cur2 = cur2->next;
			cur1 = cur1->next;
		}
	}
	return;
}