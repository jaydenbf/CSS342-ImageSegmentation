/*	Container.h
	Jayden Fullerton

	This file contains the implementation of a linked list designed to store
	pixels with red green blue values at a specific row and column. The
	implementation of the Container class is done using a standard singly
	linked list.	*/
#pragma once

struct PixelData
{
	int red, green, blue, row, col;
};

class Container
{
	/*	Node struct

		Contains a standard node for a linked list with a next pointer. Stores data
		of a pixel within an image using the PixelData struct. Singly linked using a
		next pointer.	*/
	struct Node
	{
		PixelData data;
		Node* next;
	};

	/*	deallocation helper function
		@pre	none
		@post	dynamic memory associated with this Container is now deallocated	*/
	void deallocate();

	Node* head;
	int size;
public:
	/*	Container constructor
		@pre	none
		@post	an instance of Container is created	*/
	Container();

	/*	Container copy constructor
		NOTE	doesn't have to be called explicitly
		@param	Container to be copied
		@pre	c must be a valid Container
		@post	a deep copy of the linked list of c
				is created and put into this Container	*/
	Container(const Container& c);


	/*	Container assignment operator (=)
		@param	right hand side of assignment
		@pre	c must be a valid Container
		@post	a deep copy of the linked list of c
				is created and put into a new container
				unless it is self-assignment
		@return	the deep copy of the Container	*/
	Container& operator=(const Container& c);

	/*	Container destructor
		@pre	none
		@post	dynamic memory associated with this Container is now deallocated	*/
	~Container();

	/*	Add node to the end of the linked list
		@param	red value for the pixel
		@param	green value for the pixel
		@param	blue value for the pixel
		@param	row the pixel is in
		@param	column the pixel is in
		@pre	none
		@post	a new node with values given in the paramaters
				is added after the head onto the linked list	*/
	void addPixel(PixelData p);

	/*	returns the size of this
		@pre	none
		@post	size of this is returned */
	int getSize() const;

	/*	returns data from specific index
		@param	index to get data from
		@pre	container must be non-empty
		@post	returns PixelData from the beginning of the container */
	PixelData getFirst() const;

	/*	Append c to this Container
		@param	container to merge with
		@pre	c must be a valid Container
		@post	the linked list associated with c is deep copied
				and appended to this Container	*/
	void merge(const Container& c);

	class Iterator
	{
		const Container& super;
		Node* pos;
	public:
		/*	creates an iterator for container c
			@param	container to create an iterator on
			@pre	none
			@post	iterator is initialized for c */
		Iterator(const Container& c);

		/*	increments the iterator
			@pre	iterator must not already be at the end of the container
			@post	iterator is at the next item in the container */
		Iterator operator++(int);

		/*	is the iterator at the end of the container
			@pre	none
			@post	true is returned if iterator is at the end of container, false otherwise */
		bool atEnd();

		/*	returns the data at the current spot of the iterator
			@pre	iterator must not be at the end of the container
			@post	returns data at current position of iterator */
		PixelData getData();
	};
};

