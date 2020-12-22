// Image.cpp
// Author:	Jayden Fullerton
// Info:	This class stores an image that is
//			represented as an array of pixels
//			with individual red green blue values
//			for each pixel using the ImageLib
//			library.
#include "Image.h"

// Image(string filename)
// Constructs an Image object based on a filename
// Preconditions:	filename must be the name of a valid GIF file
// Postconditions:	Image object will be created based on GIF file
Image::Image(string filename)
{
	thisImage = ReadGIF(filename);
	if (thisImage.rows == 0)
		cout << "Invalid filename, please try again.";
}

// Image(int rows, int cols)
// Constructs an Image object with all black pixels with rows rows and cols columns
// Preconditions:	rows and cols must be greater than 0
// Postconditions:	Image object will be created with all black pixels with rows rows
//					and cols columns
Image::Image(int rows, int cols)
{
	thisImage = CreateImage(rows, cols);
}

// Image(const Image& img)
// Copy constructor for Image class
// Preconditions:	none (compiler calls automatically when neccessary)
// Postconditions:	copy is created of img
Image::Image(const Image& img)
{
	thisImage = CopyImage(img.thisImage);
}

// ~Image
// Destructor for Image class
// Preconditions:	none (compiler calls automatically when neccessary)
// Postconditions:	memory is deallocated from the current Image object (this)
Image::~Image()
{
	DeallocateImage(thisImage);
}

// =
// Overloads the assignment operator
// Preconditions:	right operand must be an Image object
// Postconditions:	left operand now points to the same memory address as the right operand
const Image& Image::operator=(const Image& img)
{
	if (*this != img)
	{
		DeallocateImage(thisImage);
		thisImage = CopyImage(img.thisImage);
	}
	return *this;
}

// int getCols() const
// Gets the number of rows of pixels in the Image
// Preconditions:	none
// Postconditions:	number of rows in the Image is returned
int Image::getRows() const
{
	return thisImage.rows;
}

// int getCols() const
// Gets the number of columns of pixels in the Image
// Preconditions:	none
// Postconditions:	number of columns in the Image is returned
int Image::getCols() const
{
	return thisImage.cols;
}

// int getPixelColor(int row, int col, string color) const
// Gets the red, green, or blue value at a specified pixel and returns it
// Preconditions:	row and col must refer to a pixel within the image
// Postconditions:	returns the value of the color on the pixel requested
int Image::getPixelColor(int row, int col, string color) const
{
	if (color == "red")
		return thisImage.pixels[row][col].red;
	if (color == "blue")
		return thisImage.pixels[row][col].blue;
	return thisImage.pixels[row][col].green;
}

// void setPixelColor(int row, int col, string color, int val)
// Changes the value of the red, green, and blue pixels within the image
// Preconditions:	row and col must refer to a pixel within the image
// Postconditions:	pixel in the image is changed based on color and number provided
void Image::setPixelColor(int row, int col, string color, int val)
{
	if (color == "red")
		thisImage.pixels[row][col].red = val;
	else if (color == "blue")
		thisImage.pixels[row][col].blue = val;
	else
		thisImage.pixels[row][col].green = val;
}

// void writeToDisk(const string filename) const
// Writes current image to disk based on a specified file name
// Preconditions:	none
// Postconditions:	this Image object is written to the disk with the name filename
void Image::writeToDisk(const string filename = "output.gif") const
{
	WriteGIF(filename, thisImage);
}

// ==
// Overloads the equals operator
// Equal if every pixel is the same
// Preconditions:	right operand must also be a valid Image object
// Postconditions:	true if all pixels are the same, otherwise false
bool Image::operator==(const Image& img) const
{
	if (thisImage.cols != img.thisImage.cols ||
		thisImage.rows != img.thisImage.rows)
		return false;
	for (int row = 0; row < thisImage.rows; row++)
	{
		for (int col = 0; col < thisImage.cols; col++) // nested loops to reach all pixels
		{
			if (!(thisImage.pixels[row][col].red == img.thisImage.pixels[row][col].red ||
				thisImage.pixels[row][col].blue == img.thisImage.pixels[row][col].blue || 
				thisImage.pixels[row][col].green == img.thisImage.pixels[row][col].green))
				// if left and right operand's pixel at row and col are not the same
			{
				return false;
			}
		}
	}
	return true; // if it never returned false all pixels are the same
}

// !=
// Overloads the not-equals operator
// Not-equal if there are any different pixels within the image
// Preconditions:	right operand must also be a valid Image object
// Postconditions:	false if all pixels are the same, otherwise true
bool Image::operator!=(const Image& img) const
{
	return !(*this == img);
}

// <
// Overloads the less-than operator
// Preconditions:	right operand must be a valid Image object
// Postconditions:	true if there are less pixels in the image, false otherwise
bool Image::operator<(const Image& img) const
{
	return (thisImage.rows * thisImage.cols) < (img.thisImage.rows * img.thisImage.cols);
}

// >
// Overloads the less-than operator
// Preconditions:	right operand must be a valid Image object
// Postconditions:	true if there are more pixels in the image, false otherwise
bool Image::operator>(const Image& img) const
{
	return (thisImage.rows * thisImage.cols) > (img.thisImage.rows * img.thisImage.cols);
}

// <<
// Overloads the output operator
// Preconditions:	this must be a valid Image
// Postconditions:	number of rows and columns are output to the console in the fashion
//					"x rows y columns"
ostream& operator<<(ostream& ostream, const Image& img)
{
	ostream << img.thisImage.rows << " rows by " << img.thisImage.cols << " columns. ("
		<< img.thisImage.rows * img.thisImage.cols << " total pixels)";
	return ostream;
}

// const Image mirror()
// Creates and returns a mirror image
// Preconditions:	this must be a valid Image
// Postconditions:	returns a new Image with left and right side reversed
const Image Image::mirror()
{
	Image img = *this; // copy constructor is called here
	for (int row = 0; row < img.thisImage.rows; row++)
	{
		for (int col = 0; col < img.thisImage.cols / 2; col++)
			// nested loops only reach the left side of the image because
			// they will be swapped with the appropriate pixel on the right
			// side of the image
		{
			swapPixel(img.thisImage.pixels[row][col], 
				img.thisImage.pixels[row][img.thisImage.cols - col - 1]);
		}
	}
	return img;
}

// void swapPixel(pixel& p1, pixel& p2)
// Swaps two pixels
// Preconditions:	p1 and p2 must be valid pixels
// Postconditions:	p1 and p2 are now swapped
void Image::swapPixel(pixel& p1, pixel& p2)
{
	pixel temp = p1;
	p1 = p2;
	p2 = temp;
}