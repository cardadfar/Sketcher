# Sketcher

Sketcher is an After Effects Plug-in that uses OpenGL to render lines & polygons over a footage's target color input to give it a sketch effect.

## Getting Started

Download/clone the repository. Locate the After Effects file location locally & place Sketcher.aex in Plug-ins > Effects. 

### Prerequisites

* [GLEW](http://glew.sourceforge.net/)
* [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
* [GLFW](http://www.glfw.org/download.html)

Download the following source files and place their .dll files in the System32 folder. In the Sketcher.sln file, set the Header Locations in Properties > C/C++ > General to the directory of these header files.

* [AE SDK](http://glew.sourceforge.net/)

You will also need the AE SDK to run the files. Place the After Effects Plug-in folder in the Templates folder.


### Modifying the Code

The sketcher algorithm is kept in the Sketcher.cpp & Sketcher_Helper.cpp files. To complile the plug-in, build the Sketcher.sln file in After Effects Plug-in > Win.
