# GG1-C5-Implementing-Improved-Perlin-Noise
From GPU Gems book 1, part 1, chapter 5; Implementing Improved Perlin Noise.

From [GPU Gems book 1, part 1, chapter 5.](https://developer.nvidia.com/gpugems/gpugems/part-i-natural-effects/chapter-5-implementing-improved-perlin-noise)
 Ken Perlin, New York University

## Concepts Implemented
* Improved Perlin noise
* Noise-displaced superquadric

## Visuals
![superquadric](https://user-images.githubusercontent.com/42471346/183014562-8590d277-5879-4289-b722-9d74d5918c7e.png)
| Lumpy | Marbled | Crinkled |
| ------------- | ------------- | ------------- |
| ![Lumpy sphere](https://user-images.githubusercontent.com/42471346/183234567-4909b99b-523c-4097-ba27-0406dab23166.png) | ![Marbled sphere](https://user-images.githubusercontent.com/42471346/183234169-68529d26-26f5-44b0-adf9-9da85ca1d55a.png)  | ![Crinkled sphere](https://user-images.githubusercontent.com/42471346/183234371-7ec37b62-7bda-4712-aef1-80fdedf2d21b.png) |
| ![Lumpy superquadric](https://user-images.githubusercontent.com/42471346/183234544-a8311367-fc26-4d5e-84e9-91baeaf63428.png) | ![Marbled superquadric](https://user-images.githubusercontent.com/42471346/183234267-7e4b58a7-f188-4c48-bfad-082053497d10.png) | ![Crinkled superquadric](https://user-images.githubusercontent.com/42471346/183234414-dfe76c26-4411-4bf9-9427-635f20990f57.png) |

## Concepts Reimagined
* TBD

## Concepts explored/reimplemented in other repositories
* TBD

## Compilation and installation instructions
The graphics for this engine are handled using OpenGL, and the following instructions are for setting up the code in Windows. 

### Required packages
Compiler used:
* Minimalist GNU for Windows ([MinGW](https://sourceforge.net/projects/mingw/))
  * A GCC Compiler

Libraries required for default program compilation and installed under dependency folder:
* [OpenGL](https://github.com/KhronosGroup/OpenGL-Registry)
* The OpenGL Extension Wrangler Library ([GLEW](https://github.com/nigels-com/glew))
* Simple DirectMedia Layer ([SDL](https://github.com/libsdl-org/SDL))
  * SDL Image

### Instructions
* All dependencies except Assimp are stored within the repository. Once MinGW is installed, make sure you add ~\MinGW\bin to the PATH environment variable using these [instructions](http://www.mingw.org/wiki/Getting_Started/). You can compile Assimp following the instructions indicated on their [GitHub page](https://github.com/assimp/assimp/blob/master/Build.md), using the polly toolchain. Make sure compilation produces static libraries rather than shared. Make sure to compile Assimp using 32 bit MinGW. 
* Once setup, make can be called, and the executable ./EWS.exe ran with no additional parameters.
  * Note that you may have to adjust the name of the MinGW make executable. The executable may exist as mingw32-make, but can be renamed to make as necessary. However, you may or may not want to follow through with this action depending on the compilers that you have installed previously.

## License
[MIT License](https://choosealicense.com/licenses/mit/)
