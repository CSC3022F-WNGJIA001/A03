/**
* ConnectedComponent.h 
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#ifndef __CONNECTEDCOMPONENT__
#define __CONNECTEDCOMPONENT__

#include <string>
#include <vector>
#include <iostream> 

namespace WNGJIA001
{
    class ConnectedComponent
    {   // helper class - encapsulates information about a connected component
        private:
        friend class PGMimageProcessor;
        // local variables
        int pix_num; // number of pixels in the component
        int comp_id; // unique integer identifier for a component
        std::vector<int> comp_pix; // position of pixels from the input image
        
        public:
        // the Big 6 for ConnectedComponent class
        ConnectedComponent(); // Default constructor
        ConnectedComponent(int id); // Custom constructor
        ~ConnectedComponent(); // Destructor
        ConnectedComponent(const ConnectedComponent& cc); // Copy constructor
        ConnectedComponent(ConnectedComponent && cc); // Move constructor
        ConnectedComponent& operator=(const ConnectedComponent& rhs); // Copy assignment operator
        ConnectedComponent& operator=(ConnectedComponent&& rhs); //Move assignment operator
        // other methods
        void addPixel(int p); // add a new pixel to component
        int getID(void) const; // return component id
        int& getIDr(void); // return reference of component id
        int getSize(void) const; // return number of pixels in component
        int emptyComponent(void) const; // return 0 if comp_pix empty else return the size of comp_pix
    };
}
#endif