# Sketcher

Sketcher is an After Effects Plug-in that uses OpenGL to render lines & polygons over a footage's target color input to give it a sketch effect.


![Optional Text](../master/Images/cars.gif)
Sketcher effect on [Build Our McQueen](https://www.adobe.io/apis/creativecloud/aftereffects.html) Footage


## After Effects - Getting Started

Download/clone the repository. Locate the After Effects file location locally & place Sketcher.aex in Plug-ins > Effects. 

### Prerequisites

* [GLEW](http://glew.sourceforge.net/)
* [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
* [GLFW](http://www.glfw.org/download.html)

Download the following source files and place their .dll files in the System32 folder. In the Sketcher.sln file, set the Header Locations in Properties -> C/C++ -> General to the directory of these header files.

* [AE SDK](https://www.adobe.io/apis/creativecloud/aftereffects.html)

You will also need the AE SDK to run the files. Place the After Effects Plug-in folder in the Templates folder.


### Modifying the Code

The sketcher algorithm is kept in the Sketcher.cpp & Sketcher_Helper.cpp files. To complile the plug-in, build the Sketcher.sln file in After Effects Plug-in -> Win.

### Using the Plug-in

Sketcher comes with many parameters for customization.

* Segments: number of points to draw.
* Length: number of points per consecutive line.
* Range: distance consecutive points of the same line can be from each other.
* Straightness: length in degrees each angle of a line can make.
* Drawing Mode: renders points, lines, or fills.
* Line Color: color of the output.
* Color Detector: input color.
* Detector Range: range of acceptable input color
* Spread: [debug-feature] how far apart lines would be.
* Grid Selection: [debug-feature] selecting points in grid manner rather than at random.
* Gap Selection: allowing lines to cross over gaps.
* Random Seed: random seed.
* Subject Layer: layer to apply the effect on.

For optimal performance, use an edge detection filter on the footage before applying Sketcher on a seperate adjustment layer

## Processing - Getting Started

In SketcherApp.pde, insert the dimensions and name of the image. Be sure to place the image in the same directory of the .pde files.

```
  size(800,800);
 
  wth = width;
  hgt = height;
  String file = "flower";
  String filetype = ".jpg";
```

For batch processing, make sure your images are labled in ascending order with the number trailing the file name. For example, if you have 200 images of flowers, your images should be labled flowers0.jpg, flowers1.jpg, ..., flowers200.jpg. Change the indicies of the for loop to include all 200 images.

```
for(int i = 0; i < 1; i++) {
    String k = "0" + str(i);
    background(255);
    
    PImage img = loadImage(file + k + filetype);
  }
```

When drawing an image, you can choose between Path Forward & Point Forward point selection. 

* Path Forward - Finds first point on a line, searching for next point within radius of dist parameter.
* Point Forward - Finds points at random, making sure the dist between points on the same line satisfies distance parameter.

To declare an instance, specify the point selection algoritm & include the image, number of points, distance between points, and scale (always 1).

```
PathForward p = new PathForward(img, 3000, 25, 1);
PointForward p = new PointForward(img, 3000, 25, 1);
```

![Optional Text](../master/Images/flower_comparison.png)

