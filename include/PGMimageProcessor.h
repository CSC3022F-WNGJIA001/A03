/**
* PGMimageProcessor.h 
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#ifndef __PGMIMAGEPROCESSOR__
#define __PGMIMAGEPROCESSOR__

#include <fstream> 
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <queue>
#include <memory>

namespace WNGJIA001
{
    class ConnectedComponent;

    class PGMimageProcessor
    {   // read in a PGM image and apply a connected component analysis to that image
        public:
        // the Big 6 for PGMimageProcessor class
        PGMimageProcessor(); // Default constructor
        PGMimageProcessor(std::string filename); // Custom constructor
        ~PGMimageProcessor(); // Destructor
        PGMimageProcessor(const PGMimageProcessor& ip); // Copy constructor
        PGMimageProcessor(PGMimageProcessor && ip); // Move constructor
        PGMimageProcessor& operator=(const PGMimageProcessor& rhs); // Copy assignment operator
        PGMimageProcessor& operator=(PGMimageProcessor&& rhs); // Move assignment operator

        // other functions
        /*  process the input image to extract all the connected components,
            based on the supplied threshold (0...255) and excluding any components
            of less than the minValidSize. The final number of components that
            you store in your container (after discarding undersized one)
            must be returned.
        */
        int extractComponents(unsigned char threshold, int minValidSize);

        /*  iterate - with an iterator - through your container of connected
            components and filter out (remove) all the components which do not
            obey the size criteria pass as arguments. The number remaining
            after this operation should be returned.
        */
        int filterComponentsBySize(int minSize, int maxSize);

        /*  create a new PGM file which contains all current components
            (255=component pixel, 0 otherwise) and write this to outFileName as a
            valid PGM. the return value indicates success of operation
        */
        bool writeComponents(const std::string & outFileName);

        // return number of components
        int getComponentCount(void) const;

        // return number of pixels in largest component
        int getLargestSize(void) const;
        
        // return number of pixels in smallest component
        int getSmallestSize(void) const;
        
        /*  print the data for a component to std::cout
            see ConnectedComponent class;
            print out to std::cout: component ID, number of pixels
        */
        void printComponentData(const ConnectedComponent & theComponent) const;

        // order components from smallest to largest by size
        static bool compareComponents(const std::unique_ptr<ConnectedComponent> & lhs, const std::unique_ptr<ConnectedComponent> & rhs);

        // read input file
        void readPGMfile(std::string filename);

        // get width and height of input PGM image
        int getWidth(void) const;
        int getHeight(void) const;

        // clear up memory of img_arr
        void clearMemory(void);

        /*  iterate through the container to print data for each component as well as
            the total component number and the sizes of the smallest and largest components
        */
        void printData(void) const;

        private:
        // class member variable declaration
        int img_width; // width of input PGM image
        int img_height; // height of input PGM image
        char *in_img; // pointer to char array which stores binary data of input PGM file
        std::multiset<std::unique_ptr<ConnectedComponent>, decltype(&PGMimageProcessor::compareComponents)> cc_set;
    };
}
#endif