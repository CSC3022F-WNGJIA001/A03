# Assignment 3 CSC3022F, 2021
## Author: WNGJIA001


## Source Files
### cmdlineParser.cpp
Contains functions to parse the command line options 

### ConnectedComponent.cpp
Contains class ConnectedComponent which stores pixels of a connected component as a vector of 
integers representing the position of a pixel in a 1-dimension array of the input PGM image data; 
Each ConnectedComponent is uniquely identified by comp_id; 
The total number of pixels in a ConnectedComponent is stored as a private class member.


### PGMimageProcessor.cpp
Contains function to read data from an input PGM file and extract ConnectedComponents above a certain 
threshold from the input data; each ConnectedComponent is stored as an element in a set which orders 
the components based on number of pixels in an ascending order; 
A filtering funtction was implemented to filter out ConnectedComponents in the set which contain pixel 
number less than a minimum size as well as that above a maximum size; 
The ConnectedComponent data contained in the set can be printed to the output console in a formatted way; 
And lastly PGMimageProcessor class has a function to write the extracted components to an output PGM file.


### driver.cpp
Contains main function that calls functions to parse command line options and creates a single 
PGMimageProcessor object which is then used to perform the extraction of components and generate 
output PGM image.


## Code Structure
The driver controls the work flow of the program by first calling functions from cmdlineParser to 
parse the command line options and then instantiating an object of PGMimageProcessor by calling the 
custom constructor with the input PGM filename; 
PGMimageProcessor object will read the image width and height as well as the pixel values into a char 
pointer pointing to an array of chars; 
Based on the command line input, the values of minimum and maximum component sizes and the threshold 
are then assigned, defaults are assigned if no command line flags passed; 
The PGMimageProcessor object functions will then be called to extract the components based on the 
threshold and minimum size; 
The extracted component set is then filtered to remove any component with size greater than the maximum 
size; 
If a p flag was passed as command line option, the data of the components remaining in the set will be 
printed to the output console as well as the sizes of smallest and largest components; 
Finally, to write the output PGM image, a function will be called to iterate through the set of components 
and add pixels to a char pointer pointing to an array of chars with which the output PGM image was written.

### Mastery Work
std::set<ConnectedComponents> was implemented as the container of components in PGMimageProcessor class.

Colour coded output was not implemented.

Boundary count and image was not implemented.


## Makefile

```sh
$ make clean
```
Removes binary object files and pgm files from bin/ and executable file 'findcomp' as well as 'testsuite' 
from build/ directory

```sh
$ make
```
Compiles source files and store object files as bin/%.o; 
Links object files and store the executable file as build/findcomp

```sh
$ make test
```
Compiles and links files for unit testing as well run the unit tests


## Execute the Code
The following command line structure should be used to execute the program:
```sh
./build/findcomp [options] <inputPGMfile>
```
<inputPGMfile> is the file name of input PGM file (including .pgm)

### Available Options
```sh
$ -s <int> <int>
```
Specifies min max (minimum and maximum valid components size); 
Only one -s flag should be specified

```sh
$ -t <int>
```
Specifies threshold (foreground component will have intensity above this threshold); 
Only one -t flag should be specified

```sh
$ -w <outPGMfile>
```
Specifies output PGM file (including .pgm); 
Only one -w flag should be specified

```sh
$ -p
```
Specifies flag to print out all the component data as well as the total component number and 
the sizes of the smallest and largest components; 
Only one -p flag should be specified 

### Example
```sh
$ ./build/findcomp -s 3 7000 -t 200 -p -w example.pgm chess.pgm 
```
The above example will generate an output PGM image as example.pgm with foreground components extracted from 
chess.pgm; 
Foreground components are pixels in the input PGM image which have a intensity greater than 200; 
Components with number of pixels less than 3 and greater than 7000 will be excluded; 
The data of all components as well as the total number of components and the sizes of the smallest and 
largest components will be printed out.