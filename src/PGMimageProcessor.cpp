/**
* PGMimageProcessor.cpp
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

namespace WNGJIA001
{   
    // Default constructor
    PGMimageProcessor::PGMimageProcessor() : cc_set(&PGMimageProcessor::compareComponents)
    {}

    // Custom constructor
    PGMimageProcessor::PGMimageProcessor(std::string filename) : cc_set(&PGMimageProcessor::compareComponents)
    {
        in_img = nullptr;
        readPGMfile(filename);
    }

    // Destructor
    PGMimageProcessor::~PGMimageProcessor()
    {
        if (!this->cc_set.empty()) { 
            this->cc_set.clear(); 
        }
    }

    // Copy constructor
    PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& ip) : cc_set(ip.cc_set)
    {}

    // Move constructor
    PGMimageProcessor::PGMimageProcessor(PGMimageProcessor && ip) : cc_set(std::move(ip.cc_set))
    {
        ip.cc_set.clear();
    }

    // Copy assignment operator
    PGMimageProcessor& PGMimageProcessor::operator=(const PGMimageProcessor& rhs)
    {
        if(this != &rhs) { this->cc_set = rhs.cc_set; } // protect against self-assignment
        return *this;
    }

    // Move assignment operator
    PGMimageProcessor& PGMimageProcessor::operator=(PGMimageProcessor&& rhs)
    {
        if(this != &rhs) { // protect against self-assignment
            this->cc_set = std::move(rhs.cc_set);
            rhs.cc_set.clear();
        }
        return *this;
    }

    /*  process the input image to extract all the connected components,
        based on the supplied threshold (0...255) and excluding any components
        of less than the minValidSize. The final number of components that
        you store in your container (after discarding undersized one)
        must be returned.
    */
    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
    {
        std::cout << "Extracting connected components ..." << std::endl;
        std::queue<int> pix_q; // use queue to store neighbouring pixels
        for (int i = 0; i < img_width*img_height; ++i) { // iterate through input PGM pixels
            unsigned char value = (unsigned)in_img[i];
            if (value >= threshold) {   // if a pixel >= threshold -> add to queue
                pix_q.push(i);
                int cc_id = getComponentCount();
                cc_id += 1;
                ConnectedComponent new_cc(cc_id);
                while (!pix_q.empty()) { // while pix_q not empty
                    // add new neighbours of each pixel that's being processed;
                    int pos = pix_q.front();
                    unsigned char current_value = (unsigned)in_img[pos];
                    if (!(current_value >= threshold)) { 
                        pix_q.pop();
                        continue; 
                    }
                    int row = pos / img_width;
                    int col = pos - (row * img_width);
                    if (row == 0) { // check vertical neighbours N & S
                        int S = pos + img_width; 
                        if ((unsigned)in_img[S] >= threshold) { pix_q.push(S); }
                    } else if (row == (img_height - 1)) {
                        int N = pos - img_width; 
                        if ((unsigned)in_img[N] >= threshold) { pix_q.push(N); }
                    } else {
                        int S = pos + img_width;
                        if ((unsigned)in_img[S] >= threshold) { pix_q.push(S);}
                        int N = pos - img_width; 
                        if ((unsigned)in_img[N] >= threshold) { pix_q.push(N); }
                    }
                    if (col == 0) { // check horizontal neighbours W & E
                        int E = pos + 1; 
                        if ((unsigned)in_img[E] >= threshold) { pix_q.push(E); }
                    } else if (col == (img_width - 1)) { 
                        int W = pos - 1; 
                        if ((unsigned)in_img[W] >= threshold) { pix_q.push(W); }
                    } else { 
                        int E = pos + 1;
                        if ((unsigned)in_img[E] >= threshold) { pix_q.push(E); }
                        int W = pos - 1;
                        if ((unsigned)in_img[W] >= threshold) { pix_q.push(W); }
                    }
                    // and add new pixel to new_cc
                    new_cc.addPixel(pos);
                    pix_q.pop();
                    in_img[pos] = 0;
                }
                // insert new_cc to cc_set
                cc_set.insert(new_cc);
            } else { 
                continue; 
            }
        }
        return getComponentCount();
    }

    /*  iterate - with an iterator - through your container of connected
        components and filter out (remove) all the components which do not
        obey the size criteria pass as arguments. The number remaining
        after this operation should be returned.
    */
    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
    {
        std::cout << "Filtering out components with size less than " << minSize << " and greater than " << maxSize << " ..." << std::endl;
        std::set<ConnectedComponent, decltype(&PGMimageProcessor::compareComponents)>::const_iterator it = cc_set.begin();
        while (it != cc_set.end()){
            int size = it->getSize();
            if ((size < minSize) || (size > maxSize)) { 
                it = cc_set.erase(it); 
            } else { ++it; }
        }
        return getComponentCount();
    }

    /* create a new PGM file which contains all current components
       (255=component pixel, 0 otherwise) and write this to outFileName as a
       valid PGM. the return value indicates success of operation
    */
    bool PGMimageProcessor::writeComponents(const std::string & outFileName)
    {
        // generate out_img pointer to char array of the output image
        out_img = new char[img_width*img_height] {}; // pointer to array of zeros
        for (std::set<ConnectedComponent, decltype(&PGMimageProcessor::compareComponents)>::const_iterator 
             set_it = cc_set.begin(); set_it != cc_set.end(); ++set_it) { // loop through each component's comp_pix
            std::vector<int> pix_vec = set_it->comp_pix;
            for (std::vector<int>::const_iterator vec_it = pix_vec.begin(); vec_it != pix_vec.end(); ++vec_it) {
                int pos = *vec_it;
                out_img[pos] = (unsigned char)255;
            }
        }
        
        // write to output file
        std::string output_filename = "bin/" + outFileName;
        std::ofstream out_file(output_filename, std::ios_base::binary);
        out_file << "P5\n" << img_width << " " << img_height << "\n" <<  "255\n";
        out_file.write(out_img, img_width*img_height);
        out_file.close();
        // clean up memory of out_img
        delete [] out_img;

        return true;
    }

    // return number of components
    int PGMimageProcessor::getComponentCount(void) const
    {
        return cc_set.size();
    }

    // return number of pixels in largest component
    int PGMimageProcessor::getLargestSize(void) const
    {
        ConnectedComponent cc_large = *cc_set.rbegin();
        return cc_large.getSize();
    }
        
    // return number of pixels in smallest component
    int PGMimageProcessor::getSmallestSize(void) const
    {
        ConnectedComponent cc_small = *cc_set.begin();
        return cc_small.getSize();
    }
        
    /*  print the data for a component to std::cout
        see ConnectedComponent class;
        print out to std::cout: component ID, number of pixels
    */
    void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
    {
        std::cout << " \tComponent ID: " << theComponent.getID() << "; number of pixels: " << theComponent.getSize() << std::endl;
    }

    // order components from smallest to largest by size
    bool PGMimageProcessor::compareComponents(const ConnectedComponent & lhs, const ConnectedComponent & rhs)
    {
        // return true if lhs < rhs (based on size)
        return (lhs.getSize() < rhs.getSize()); 
    }

    // read input file
    void PGMimageProcessor::readPGMfile(std::string filename)
    {
        // open and read input PGM file
        std::ifstream in_file(filename, std::ios::binary);
        if (in_file) {
            std::string new_line;
            while (!in_file.eof()) { // read header lines of input PGM file
                std::getline(in_file, new_line);
                if (new_line == "P5") { continue; }
                else if (new_line.at(0) == '#') { continue; }
                else if (new_line == "255") { break; }
                else { // read width and height
                    std::istringstream line_ss(new_line);
                    line_ss >> img_width >> std::ws >> img_height >> std::ws;
                }
            }
            // read the binary data of the input PGM file
            clearMemory();
            in_img = new char[img_width*img_height];
            in_file.read(in_img, img_width*img_height);
        } else {
            std::cerr << "ERROR: " << filename << " can not be found" << std::endl;
        }
        // close input PGM file
        in_file.close();
    }

    // get width and height of input PGM image
    int PGMimageProcessor::getWidth(void) const { return this->img_width; }
    int PGMimageProcessor::getHeight(void) const { return this->img_height; }

    // clear up memory held by in_img
    void PGMimageProcessor::clearMemory(void)
    {
        if (this->in_img != nullptr) { 
            delete [] this->in_img; 
            std::cout << "Memory holding the input PGM image has been deallocated" << std::endl;
        }
    }

    /*  iterate through the container to print data for each component as well as
        the total component number and the sizes of the smallest and largest components
    */
    void PGMimageProcessor::printData(void) const
    {
        std::cout << "+----------------------------------------------------------------+" << std::endl;
        std::cout << " Printing out component data:" << std::endl;
        for (std::set<ConnectedComponent, decltype(&PGMimageProcessor::compareComponents)>::const_iterator it = cc_set.begin(); it != cc_set.end(); ++it) {
            printComponentData(*it);
        }
        std::cout << "+----------------------------------------------------------------+" << std::endl;
        std::cout << " Total component number: " << getComponentCount() << std::endl;
        std::cout << "+----------------------------------------------------------------+" << std::endl;
        std::cout << " Size of smallest component: " << getSmallestSize() << std::endl;
        std::cout << " Size of largest component: " << getLargestSize() << std::endl;
        std::cout << "+----------------------------------------------------------------+" << std::endl;
    }
}