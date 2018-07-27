# Sketcher

Sketcher is an After Effects Plug-in that uses OpenGL to render lines & polygons over a footage's target color input to give it a sketch effect.

## Getting Started

Download/clone the repository. Locate the After Effects file location locally & place Sketcher.aex in Plug-ins > Effects. 

### Prerequisites

* [GLEW](http://glew.sourceforge.net/)
* [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
* [GLFW](http://www.glfw.org/download.html)


### Modifying the Code

The sketcher algorithm is kept in the Skeleton.cpp & Skeleton_Helper.cpp files. To complile the plug-in, run the Skeleton.sln file in After Effects > Win
