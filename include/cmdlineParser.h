/**
* cmdlineParser.h 
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#ifndef _CMDLINEPARSER
#define _CMDLINEPARSER

#include <iostream>
#include <string>
#include <vector>

namespace WNGJIA001 {
    // external variables
    extern std::string pgm_filename; // PGM image file name
    extern int min_size; // minimum valid components size [min default = 3, max = image width*img height i.e. unlimited]
    extern int max_size;// maximum valid components size
    extern int threshold; // threshold for component detection (default=128, limit to [0. . . 255])
    extern bool p; // option flag to print data
    extern std::string out_filename; // output PGM image file name

    // methods
    // display help messages
    void getHelp();
    // parse command line options
    void parseCmdline(int argc, char *argv[]);
    // check if the pgm file name is valid
    void checkFilename(const std::string s);
    // return true if string s can be converted to an integer
    bool isInteger(const std::string& s);
    // return true if the threshold falls within the limit [0. . . 255]
    bool validThreshold(const int i);
    // return true if a necessary flag missing
    bool missingFlag();
}

#endif