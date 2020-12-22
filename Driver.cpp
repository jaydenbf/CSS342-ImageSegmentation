/*	Driver.cpp
	Jayden Fullerton

	This file contains main(). This file uses image segmentation to seperate
	similar color groups using Container, and then writing the average color
	for that entire group. Images are implemented using the Image class.	*/
#include <iostream>
#include "Container.h"
#include "Image.h"

// forward declarations
void addToContainer(Container& c, Container& merged, int row, int col, const Image& in, Image& out);
PixelData generatePixelData(int row, int col, const Image& img);
void segmentContainer(const Container& c, Image& out);
int av(int num);

/*	main()
	@pre	none
	@post	image segmentation is used to group similar colors into
			the average of those colors and written to disk	*/
int main()
{
	int numOfContainers = 0;
	Container merged;

	// Read image from disk
	Image input = Image("test4.gif");

	// Create black image with same dimensions as input
	Image output = Image(input.getRows(), input.getCols());

	// Iterate through image
	for (int row = 0; row < input.getRows(); row++)
	{
		for (int col = 0; col < input.getCols(); col++)
		{
			// if the current pixel is black
			if (output.getPixelColor(row, col, "red") == 0 &&
				output.getPixelColor(row, col, "green") == 0 &&
				output.getPixelColor(row, col, "blue") == 0)
			{
				numOfContainers++;
				Container c;
				addToContainer(c, merged, row, col, input, output);
			}
		}
	}

	cout << "Total number of segments found: " << numOfContainers << endl;
	cout << "Total number of pixels in merged group: " << merged.getSize() << endl;

	// Calculate average by iterating through the merged container
	int red = 0;
	int green = 0;
	int blue = 0;
	Container::Iterator it = Container::Iterator(merged);
	while (!it.atEnd())
	{
		red += it.getData().red;
		green += it.getData().green;
		blue += it.getData().blue;
		it++;
	}
	red /= merged.getSize();
	green /= merged.getSize();
	blue /= merged.getSize();
	cout << "Average color of the merged group: " << red << "R, " << green << "G, " << blue << "B" << endl;

	output.writeToDisk("output.gif");
	system("pause");
	return 0;
}

/*	add pixels to container recursively
	@param	container to add pixels to
	@param	container containing all currently processed containers
	@param	row of pixel trying to add
	@param	column of pixel trying to add
	@param	image to draw pixels from
	@param	image to write containers to
	@pre	img must be a valid image object
	@post	image is segmented into similar color groups	*/
void addToContainer(Container& c, Container& merged, int row, int col, const Image& in, Image& out)
{
	// if row,col is already in this container
	if (out.getPixelColor(row, col, "red") == 255 &&
		out.getPixelColor(row, col, "green") == 255 &&
		out.getPixelColor(row, col, "blue") == 255)
		return;

	// if row,col is already in another container
	if (!(out.getPixelColor(row, col, "red") == 0 &&
		out.getPixelColor(row, col, "green") == 0 &&
		out.getPixelColor(row, col, "blue") == 0))
		return;

	PixelData seed;
	if (c.getSize() == 0)
		seed = generatePixelData(row, col, in);
	else
		seed = c.getFirst();

	// if this pixel is similar enough to the seed, add it to c
	if ((av(seed.red - in.getPixelColor(row, col, "red")) +
		av(seed.green - in.getPixelColor(row, col, "green")) +
		av(seed.blue - in.getPixelColor(row, col, "blue"))) < 100)
	{
		c.addPixel(generatePixelData(row, col, in));
		out.setPixelColor(row, col, "red", 255);
		out.setPixelColor(row, col, "green", 255);
		out.setPixelColor(row, col, "blue", 255);

		if (row + 1 < in.getRows())
			addToContainer(c, merged, row + 1, col, in, out);
		if (col + 1 < in.getCols())
			addToContainer(c, merged, row, col + 1, in, out);
		if (row - 1 >= 0)
			addToContainer(c, merged, row - 1, col, in, out);
		if (col - 1 >= 0)
			addToContainer(c, merged, row , col - 1, in, out);
	}
	else
		return;

	if (row == seed.row && col == seed.col)
	{
		segmentContainer(c, out);
		merged.merge(c);
	}
}

/*	generates a PixelData struct as defined in Container.h
	@param	row of pixel
	@param	col of pixel
	@param	image to draw pixel from
	@pre	row,col must be a pixel within img
	@post	a PixelData struct is returned with the corresponding pixel data */
PixelData generatePixelData(int row, int col, const Image& img)
{
	PixelData p;
	p.red = img.getPixelColor(row, col, "red");
	p.green = img.getPixelColor(row, col, "green");
	p.blue = img.getPixelColor(row, col, "blue");
	p.row = row;
	p.col = col;
	return p;
}

/*	set container equal to its average color in the image
	@param	container to be segmented
	@param	output for image to be segmented into
	@pre	container must refer to pixels within the dismensions of image
	@post	all pixels in c are now the average of the pixels in the previous image	*/
void segmentContainer(const Container& c, Image& out)
{
	int red = 0;
	int green = 0;
	int blue = 0;
	Container::Iterator it = Container::Iterator(c);
	while (!it.atEnd())
	{
		red += it.getData().red;
		green += it.getData().green;
		blue += it.getData().blue;
		it++;
	}
	red /= c.getSize();
	green /= c.getSize();
	blue /= c.getSize();


	// Iterate through the container again
	Container::Iterator it2 = Container::Iterator(c);
	while (!it2.atEnd())
	{
		PixelData pixel = it2.getData();

		// Set the color at row, col equal to the average
		out.setPixelColor(pixel.row, pixel.col, "red", red);
		out.setPixelColor(pixel.row, pixel.col, "green", green);
		out.setPixelColor(pixel.row, pixel.col, "blue", blue);
		it2++;
	}
}

/*	calculates absolute value
	@param	number to calculate
	@pre	none
	@post	return absolute value of input */
int av(int num)
{
	if (num < 0)
		return num * -1;
	return num;
}