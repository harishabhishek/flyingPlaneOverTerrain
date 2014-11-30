//
//  Rotation.h
//  CS 418 MP2
//
//  Created by Helios on 3/11/14.
//  Copyright (c) 2014 Helios. All rights reserved.
//

#ifndef CS_418_MP2_Rotation_h
#define CS_418_MP2_Rotation_h

/*
 * Quaternion Multiplication implementation
 * for rotation
 */
class Rotation {
public:
    //Data Members which make the vector
	double w, x, y, z;
    
    //Parameterized constructor for the Rotation Class
	Rotation(double a, double b, double c, double d) {
		w = a; x = b; y = c; z = d;
	}
    
    //Default Constructor for the rotation
	Rotation() {
        w =0;
        x =0;
        y =0;
        z =0;
    }
    
    //The function to rotate the given vector in the direction
    //Quaternian
	Vector operator*(const Vector &param_vec) const {
		Vector normal(param_vec.x,param_vec.y,param_vec.z);
		normal.normalize();
		Rotation initialRotated, finalRotatedVec;
        initialRotated.z = normal.z;
        initialRotated.y = normal.y;
		initialRotated.w = 0.0;
		initialRotated.x = normal.x;
        
		finalRotatedVec = initialRotated * conjugate();
		finalRotatedVec = *this * finalRotatedVec;
		return Vector(finalRotatedVec.x,finalRotatedVec.y,finalRotatedVec.z);
	}
    

    
    //THe function to find the rotational conjugate of the vector
	Rotation conjugate() const {
		return Rotation(w,-x,-y,-z);
	}
    
	//The function to multiply Rotation Vector with a given vector
	Rotation operator*(const Rotation &rot_q) const {
		return Rotation(  w * rot_q.w - x * rot_q.x - y * rot_q.y - z * rot_q.z,
                          w * rot_q.x + x * rot_q.w + y * rot_q.z - z * rot_q.y,
                          w * rot_q.y + y * rot_q.w + z * rot_q.x - x * rot_q.z,
                          w * rot_q.z + z * rot_q.w + x * rot_q.y - y * rot_q.x
                          );
	}
    
    //Normalizing the unit rotation Quaternians
	void normalise() {
		double squared = pow(w,2)+ pow(x,2)+pow(y,2)+pow(z,2);
			double magnitude = sqrt(squared);
			w /= magnitude;
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
	};
    
    

};


#endif
