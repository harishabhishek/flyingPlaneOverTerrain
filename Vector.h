//
//  Vector.h
//  CS 418 MP2
//
//  Created by Abhishek Harish on 3/9/14.
//  Copyright (c) 2014 Abhishek Harish. All rights reserved.
//

#ifndef __CS_418_MP2__File__
#define __CS_418_MP2__File__

#include <iostream>
#include <math.h>
#define TOLERANCE 0.0001

/*
 * A vector Class which normalizes the given vector
 * Also has the defined '+' operator for the vector class
 * This is based on a standard Vector claa decribed in a online 
 * webboard for OpenGL programming
 */

class Vector {
public:
    /*
     * x, y, and z coordinates of a vector
     */
	double x, y, z;
    //Parameterized constructor for the vector class
	Vector(double first, double second, double third) {
		x = first; y = second; z = third;
	}
    
    //Default construcntor
	Vector() {
        x = 0;
        y = 0;
        z = 0;
    }
    
    //Overloaded '+' operator for the vector class
	Vector operator+(Vector param) {
		return Vector(x+param.x,y+param.y,z+param.z);
	}
    
    //Helper Function
    void updateVectorParam(double one, double two, double three){
        x = one;
        y = two;
        z = three;
        x = x+y+z;
    }
    
    //Function to normalize the given vector
    //Very helpful and usefull function to have
	void normalize() {
		double squared = pow(x, 2)+ pow(y, 2) + pow(z, 2);
		if (fabs(squared) > TOLERANCE && fabs(squared - 1.0) > TOLERANCE) {
			double magnitude = sqrt(squared);
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}
};

#endif 
/* defined(__CS_418_MP2__File__) */
