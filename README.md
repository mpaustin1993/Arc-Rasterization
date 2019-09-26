# HW1
First homework for COSC 4370

I used Microsoft Visual Code with a WSL Extension to my personal Linux server in Ubuntu to develop and compile my homework in C++.

I compiled the program in my WSL Extension via the following commands:

  g++ hw1.cpp

  ./a.out 100


Program Description:

First, I read through the provided homework material analyzing and explaining rasterizing a circle via MidPoint lines.

It took me a while to understand the arguments needed to properly rasterize the arc in the RasterizeArc function.
Once, I understood how to obtain the coordinates of the needed East and Southeast neighboring pixels, I then devised the formulas for deciding if the next pixel rendered should be East or Southeast of the current pixel.

It took some time to find an application to display my .ppm file, because the 'display' function for Linux would not work. I ended up using GIMP which I used to export my .ppm files to .bmp files.

After rendering a 200x200 arc, it didn't look right, so I finally had to change the RenderPixel function, discovering that the arc is actually rendering from two separate origins: when (x = 0, y = radius) and when (x = radius, y = 0).

I then obtained the desired single quadrant arc.

I greatly enjoyed steppping through and really understanding the math behind arc rasterization, and overall enjoyed this project.
