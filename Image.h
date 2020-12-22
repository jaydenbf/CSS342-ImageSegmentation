// Image.h
// Author:	Jayden Fullerton
// Info:	This class stores an image that is
//			represented as an array of pixels
//			with individual red green blue values
//			for each pixel using the ImageLib
//			library.
#pragma once

#include <iostream>
#include <string>
#include "ImageLib.h"
using namespace std;

class Image
{
public:
	// Image(string filename)
	// Constructs an Image object based on a filename
	// Preconditions:	filename must be the name of a valid GIF file
	// Postconditions:	Image object will be created based on GIF file
	Image(string filename);

	// Image(int rows, int cols)
	// Constructs an Image object with all black pixels with rows rows and cols columns
	// Preconditions:	rows and cols must be greater than 0
	// Postconditions:	Image object will be created with all black pixels with rows rows
	//					and cols columns
	Image(int rows, int cols);

	// Image(const Image& img)
	// Copy constructor for Image class
	// Preconditions:	none (compiler calls automatically when neccessary)
	// Postconditions:	copy is created of img
	Image(const Image& img);

	// ~Image
	// Destructor for Image class
	// Preconditions:	none (compiler calls automatically when neccessary)
	// Postconditions:	memory is deallocated from the current Image object (this)
	~Image();

	// =
	// Overloads the assignment operator
	// Preconditions:	right operand must be an Image object
	// Postconditions:	left operand now points to the same memory address as the right operand
	const Image& operator=(const Image& img);

	// int getCols() const
	// Gets the number of rows of pixels in the Image
	// Preconditions:	none
	// Postconditions:	number of rows in the Image is returned
	int getRows() const;

	// int getCols() const
	// Gets the number of columns of pixels in the Image
	// Preconditions:	none
	// Postconditions:	number of columns in the Image is returned
	int getCols() const;

	// int getPixelColor(int row, int col, string color) const
	// Gets the red, green, or blue value at a specified pixel and returns it
	// Preconditions:	row and col must refer to a pixel within the image
	// Postconditions:	returns the value of the color on the pixel requested
	int getPixelColor(int row, int col, string color) const;

	// void setPixelColor(int row, int col, string color, int val)
	// Changes the value of the red, green, and blue pixels within the image
	// Preconditions:	row and col must refer to a pixel within the image
	// Postconditions:	pixel in the image is changed based on color and number provided
	void setPixelColor(int row, int col, string color, int val);

	// void writeToDisk(const string filename) const
	// Writes current image to disk based on a specified file name
	// Preconditions:	none
	// Postconditions:	this Image object is written to the disk with the name filename
	void writeToDisk(const string filename) const;

	// ==
	// Overloads the equals operator
	// Equal if every pixel is the same
	// Preconditions:	right operand must also be a valid Image object
	// Postconditions:	true if all pixels are the same, otherwise false
	bool operator==(const Image& img) const;

	// !=
	// Overloads the not-equals operator
	// Not-equal if there are any different pixels within the image
	// Preconditions:	right operand must also be a valid Image object
	// Postconditions:	false if all pixels are the same, otherwise true
	bool operator!=(const Image& img) const;

	// <
	// Overloads the less-than operator
	// Preconditions:	right operand must be a valid Image object
	// Postconditions:	true if there are less pixels in the image, false otherwise
	bool operator<(const Image& img) const;

	// >
	// Overloads the less-than operator
	// Preconditions:	right operand must be a valid Image object
	// Postconditions:	true if there are more pixels in the image, false otherwise
	bool operator>(const Image& img) const;

	// <<
	// Overloads the output operator
	// Preconditions:	this must be a valid Image
	// Postconditions:	number of rows and columns are output to the console in the fashion
	//					"x rows y columns"
	friend ostream& operator<<(ostream& ostream, const Image& img);

	// const Image mirror()
	// Creates and returns a mirror image
	// Preconditions:	this must be a valid Image
	// Postconditions:	returns a new Image with left and right side reversed
	const Image mirror();
private:
	// The image object from ImageLib.h
	image thisImage;
		
	// void swapPixel(pixel& p1, pixel& p2)
	// Swaps two pixels
	// Preconditions:	p1 and p2 must be valid pixels
	// Postconditions:	p1 and p2 are now swapped
	void swapPixel(pixel& p1, pixel& p2);
};

