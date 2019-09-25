/*******************************************************
 * Homework 1: Rasterization                           *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method you derived in the written portion of the    *
 * homework.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.

// I changed variable to sie to imageSize due to ambiguity errors with Visual Studio code.
int imageSize;
bool **image;

void renderPixel(int x, int y)
{
	assert(x >= 0 && y >= 0 && x <= imageSize && y <= imageSize);
	
	// Then we ensure that while x is less than or equal to y (so that the arc's middle pixel maps),
	// we render the pixels at (x, y) and its symmetrical pixel at (y, x).
	// So, the arc is being rendered from two points: from (0, radius) and from (radius, 0).

	if(x <= y){
		image[x][y] = 1;
		image[y][x] = 1;	
	}
}

void rasterizeArc(int radius)
{

	// We initialize the initial value of x to 0 and y to the radius / imageSize accepted from the argument line.
	// We also set our argument, d, to 0 which will be used to determine if we choose to render the next pixel
	// East or Southeast of our current pixel.
	
	int x = 0;
	int y = radius;
	int d = 0;

	// We create a while function for x to be less than the radius, for we are only trying to draw one quadrant
	// of an arc.

	while(x < radius){

		// If d is less than 0, then we render the pixel East of our current pixel:
		// we increment d by our East function: 2x + 3,
		// increment x by 1, and pass x and y into RenderPixel.

		if(d < 0){ // moving East
			d += (2*x) + 3;
			x += 1;
			renderPixel(x, y);
		}

		// If d is less than 0, then we render the pixel Southeast of our current pixel:
		// we increment d by our East function: 2x - 2y +5,
		// increment x by 1, decrement y by 1, and pass x and y into RenderPixel.

		else if(0 <= d){ // moving SouthEast
			d += (2*x) - (2*y) + 5;
			x += 1;
			y -= 1;
			renderPixel(x, y);
		}
	}
	
}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " circleimageSize\n";
		return 0;
	}

#ifdef _WIN32
	sscanf_s(argv[1], "%d", &imageSize);
#else
	sscanf(argv[1], "%d", &imageSize);
#endif
	if (imageSize <= 0)
	{
		cout << "Image must be of positive imageSize.\n";
		return 0;
	}

	// reserve image as 2d array
	image = new bool *[imageSize + 1];
	for (int i = 0; i <= imageSize; i++)
		image[i] = new bool[imageSize + 1];
		
	// pixelTest(imageSize);	

	rasterizeArc(imageSize);

	char filename[50];
#ifdef _WIN32
	sprintf_s(filename, 50, "circle%d.ppm", imageSize);
#else
	sprintf(filename, "circle%d.ppm", imageSize);
#endif

	ofstream outfile(filename);
	outfile << "P3\n# " << filename << "\n";
	outfile << imageSize + 1 << ' ' << imageSize + 1 << ' ' << 1 << endl;

	for (int i = 0; i <= imageSize; i++)
		for (int j = 0; j <= imageSize; j++)
			outfile << image[imageSize - i][j] << " 0 0\n";

	// delete image data
	for (int i = 0; i <= imageSize; i++)
		delete[] image[i];
	delete[] image;

	return 0;
}
