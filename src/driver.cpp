/**
* driver.cpp containing main function
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#include <fstream>  
#include <iostream> 
#include <sstream>  
#include <string>
#include <vector>

#include "cmdlineParser.h"
#include "ConnectedComponent.h"
#include "PGMimageProcessor.h"

int main(int argc, char *argv[]) {
    using namespace WNGJIA001;
    // call function to parse command line options
    parseCmdline(argc, argv);
    
    // instantiate image processor class
    PGMimageProcessor myProcessor(in_PGM_file);

    // assign default values if not passed as command line options 
    if ((min_size == -1) && (max_size == -1)) { // no -s flag parsed: default min = 3; max = img_width * img_height
        min_size = 3;
        max_size = myProcessor.getWidth()*myProcessor.getHeight();
    }
    if (threshold == -1) { // no -t flag parsed: default threshold = 128
        threshold = 128;
    }

    // extract components
    std::cout << std::endl;
    int cc_num = myProcessor.extractComponents((unsigned char)threshold, min_size);
    std::cout << "Connected component extraction completed: " << cc_num << " components extracted" << std::endl;

    // filter
    if ((min_size != -1) && (max_size != -1)) { // custom min and max sizes: do filter
        std::cout << std::endl;
        int i = myProcessor.filterComponentsBySize(min_size, max_size);
        std::cout << "Filtering completed: " << i << " components remaining" << std::endl;
    }
    
    // print
    if (p_flag) {
        std::cout << std::endl;
        myProcessor.printData();
    }

    // write out
    std::cout << std::endl;
    if (myProcessor.writeComponents(out_PGM_file)) {
        std::cout << "Output PGM image has been successful generated as bin/" << out_PGM_file << "\n" << std::endl;
    }
    return 0;
}