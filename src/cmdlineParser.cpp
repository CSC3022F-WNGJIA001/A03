/**
* cmdlineParser.cpp source file for cmdlineParser.h
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <string>

#include "cmdlineParser.h"

namespace WNGJIA001 {
    // variables declaration
    std::string in_PGM_file; 
    int min_size = -1;
    int max_size = -1;
    int threshold = -1; 
    bool p_flag = false; 
    std::string out_PGM_file;

    // display help messages
    void getHelp() {
        std::cout << "Usage:\t\t\t./build/findcomp [options] <inputPGMfile>\n\nOptions are:" << std::endl;
		std::cout << "-s <int> <int>\t\t# set the minimum and maximum valid components size" << std::endl;
        std::cout << "-t <int>\t\t# set the threshold for component detection (default=128, limit to [0. . . 255])" << std::endl;
        std::cout << "-p \t\t\t# print out all the component data as well as the total component number "
            "and the sizes of the smallest and largest components" << std::endl;
        std::cout << "-w <outPGMfile>\t\t# write out all retained components to a new PGMfile, <outPGMfile>" << std::endl;
    }

    // parse command line options
    void parseCmdline(int argc, char *argv[]) {
        if(argc == 1) { // no command line flags: error
            std::cerr << "ERROR: No command line options found. Type in --help or -h for help." << std::endl;
            exit(1);
        } else if (argc == 2) { // -h or --help flag: show flag options; otherwise: error
            std::string command = argv[1];
            if ((command == "-h") || (command == "--help")) {
			    getHelp();
			    exit(0);
            } else {
                std::cerr << "ERROR: Undefined command line option" << std::endl;
            }
        } else { // parse command line arguments
            // parse command line flags
            int last_item = argc - 1;
            int i = 1;
            while (i < last_item) {
                std::string flag = argv[i];
                if (flag == "-s") {
                    if ((min_size != -1) && (max_size != -1)) { // multiple -s flags: error
                        std::cerr << "ERROR: Multiple declaration of -s flags" << std::endl;
                        exit(1);
                    } else if ((argc - i) < 3 || !isInteger(argv[i+1]) || !isInteger(argv[i+2])) { // if any pram not int: error
                        std::cerr << "ERROR: Incorrect format of -s flags" << std::endl;
                        exit(1);
                    } else { // parse -s flags
                        min_size = std::stoi(argv[++i]);
                        max_size = std::stoi(argv[++i]);
                        std::cout << "s flags parsed: " << min_size << "; " << max_size << std::endl;
                    }
                } else if (flag == "-t") {
                    if (threshold != -1) { // multiple -t flags: error
                        std::cerr << "ERROR: Multiple declaration of -t flags" << std::endl;
                        exit(1);
                    } else if ((argc - i) < 2 || !isInteger(argv[i+1])) { // if the following pram not int: error
                        std::cerr << "ERROR: Incorrect format of -t flags" << std::endl;
                        exit(1);
                    } else { // parse threshold
                        threshold = std::stoi(argv[++i]);
                        std::cout << "t flags parsed: " << threshold << std::endl;
                    }
                } else if (flag == "-p") {
                    if (p_flag) { // multiple -p flags: error 
                        std::cerr << "ERROR: Multiple declaration of -t flags" << std::endl;
                        exit(1);
                    } else {
                        p_flag = true;
                        std::cout << "p flags parsed" << std::endl;
                    }
                } else if (flag == "-w") {
                    if ((argc - i) < 2) { // require at least 1 param follow -w
                        std::cerr << "ERROR: Incorrect format of -w flags" << std::endl;
                        exit(1);
                    } else {
                        out_PGM_file = argv[++i];
                        checkFilename(out_PGM_file);
                        std::cout << "w flags parsed: " << out_PGM_file << std::endl;
                    }
                } else {
                    std::cerr << "ERROR: Undefined command line flags" << std::endl;
                    exit(1);
                }
                ++i;
            }
            if (missingFlag()) {
                std::cerr << "ERROR: Missing compulsory -w flag" << std::endl;
                exit(1);
            }
            // parse input PGM filename
            in_PGM_file = argv[last_item];
            checkFilename(in_PGM_file);
        }
    }

    // check if the pgm file name is valid
    void checkFilename(const std::string s) {
        std::string filename = s;
        int filename_size = filename.size();
        if (filename_size < 5) { // minimum requirement is 5 chars, e.g: a.pgm
            std::cerr << "ERROR: Invalid PGM filename: " << s << std::endl;
            exit(1);
        } else if (filename.find('.') != std::string::npos) { // find the position where extension starts
            std::string extension = filename.substr(filename.find('.')+1);
            if (extension != "pgm") { // incorrect extension
                std::cerr << "ERROR: Invalid PGM filename: " << s << std::endl;
                exit(1);
            }
        } else { // size > 4 but no extension
            std::cerr << "ERROR: Invalid PGM filename: " << s << std::endl;
            exit(1);
        }
    }

    // return true if string s can be converted to an integer
    bool isInteger(const std::string& s) {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    // return true if the threshold falls within the limit [0. . . 255]
    bool validThreshold(const int i) {
        return (i >= 0) && (i <= 255); 
    }

    // return true if a necessary flag missing
    bool missingFlag() {
        return out_PGM_file.empty();
    }
}
