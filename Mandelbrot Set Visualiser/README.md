# mandel-wut
mandel-wut? --> Mandelbrot

OpenGL based Mandelbrot Set visualizer in C++ , using basic vertex and fragment shaders , with the ability to zoom and pan.

Controls :
```
	SPACE-BAR   	--  ZOOM IN

	LEFT-SHIFT  	--  ZOOM OUT

	WASD	    	--  Move around

	UP ARROW	-- Increase Max Iterations 

	DOWN ARROW	-- Decrease Max Iterations

	LEFT ARROW	-- Increase Max Iterations counter

	RIGHT ARROW	-- Decrease Max Iterations counter
```



Instructions for setting up in your Visual Studio 2019 : -- 

For Addidtional Include Directories in C++ -> General

	$(SolutionDir)dependencies\GLM\include
	$(SolutionDir)dependencies\GLFW\include
	$(SolutionDir)dependencies\GLEW\include

For Addidtional Library Directories in Linker -> General

	$(SolutionDir)dependencies\GLEW\lib
	$(SolutionDir)dependencies\GLM\lib
	$(SolutionDir)dependencies\GLFW\lib

For Addidtional Dependencies in Linker -> Input

	opengl32.lib
	glfw3.lib
	glew32.lib


If you get the error -- 
```
The code execution cannot proceed because glew32.dll was not found, try reinstalling ....
``` 
put 

```python 
glew32.dll
``` 
in 
```python 
mandel-wut\Debug
``` 
(for debug mode) or 
```python 
mandel-wut\Release
``` 
(if using in release mode).

<img src = "https://github.com/mahir29/PONDEL/tree/master/Mandelbrot Set Visualiser/img/1.jpg" >
<img src = "/img/11.jpg" >
<img src = "/img/3.jpg" >
<img src = "/img/4.jpg" >
<img src = "/img/5.jpg" >
<img src = "/img/6.jpg" >
<img src = "/img/10.jpg" >


## TO-DO
Improve coloring, rendering quality, max-zoom level






