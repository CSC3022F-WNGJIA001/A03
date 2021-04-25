/**
* ConnectedComponent.cpp
* CSC3022F Assignment 3 2021
* Author: WNGJIA001
*/

#include <algorithm> // std::find_if

#include "ConnectedComponent.h"

namespace WNGJIA001
{
    // Default constructor
    ConnectedComponent::ConnectedComponent() : pix_num(0), comp_id(0)
    {}

    // Custom constructor
    ConnectedComponent::ConnectedComponent(int id) : pix_num(0)
    {
        this->comp_id = id;
    }

    // Destructor
    ConnectedComponent::~ConnectedComponent()
    {
        if (!this->comp_pix.empty()) {
            this->comp_pix.clear();
        }
    }

    // Copy constructor
    ConnectedComponent::ConnectedComponent(const ConnectedComponent & cc) : pix_num(cc.pix_num), comp_id(cc.comp_id), comp_pix(cc.comp_pix)
    {}

    // Move constructor
    ConnectedComponent::ConnectedComponent(ConnectedComponent && cc) : pix_num(cc.pix_num), comp_id(cc.comp_id), comp_pix(std::move(cc.comp_pix))
    {
        cc.pix_num = 0;
        cc.comp_id = 0;
        cc.comp_pix.clear();
    }

    // Copy assignment operator
    ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& rhs)
    {
        if(this != &rhs) { // protect against self-assignment
            this->pix_num = rhs.pix_num;
            this->comp_id = rhs.comp_id;
            this->comp_pix = rhs.comp_pix;
        }
        return *this;
    }

    //Move assignment operator
    ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& rhs)
    {
        if(this != &rhs) { // protect against self-assignment
            this->pix_num = rhs.pix_num;
            rhs.pix_num = 0;
            this->comp_id = rhs.comp_id;
            rhs.comp_id = 0;
            this->comp_pix = std::move(rhs.comp_pix);
            rhs.comp_pix.clear();
        }
        return *this;
    }

    // add a new pair into comp_pix
    void ConnectedComponent::addPixel(int p)
    {
        int new_pix = p;
        comp_pix.push_back(new_pix);
        pix_num += 1;
    }

    // return component id
    int ConnectedComponent::getID(void) const { return this->comp_id; }

    // return reference of component id
    int& ConnectedComponent::getIDr(void) { return this->comp_id; }
        
    // return number of pixels in component
    int ConnectedComponent::getSize(void) const { return this->pix_num; }

    // return 0 if comp_pix empty else return the size of comp_pix
    int ConnectedComponent::emptyComponent(void) const { return this->comp_pix.size(); }
}