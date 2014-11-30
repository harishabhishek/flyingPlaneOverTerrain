//
//  Camera_Update.h
//  CS 418 MP2
//
//  Created by Abhishek Harish on 3/9/14.
//  Copyright (c) 2014 Abhishek Harish. All rights reserved.
//

#ifndef CS_418_MP2_Camera_Update_h
#define CS_418_MP2_Camera_Update_h
#include "Rotation.h"
/*
 * Camera class
 *
 * For tracking locations and directions without
 * the chance for gimbal lock and other
 * annoyances that occur from other rotation systems
 */
class Camera_Update {
public:
    
    //The position of the rotation vector
	Vector position;
    //The speed for moving forward
	double speed;
    //The direction for the rotation
    //Has a member relationship to the Quaternian_Rotation
	Rotation rotation;

    
    //Update the camera to the default camera for this world
	Camera_Update() {
		position = Vector(0,0.05,0);
		rotation = Rotation(1.0,0.0,0.0,0.0);
		rotation.normalise();
		speed = 0.01;
	}
    
    //Helper function
    void turnRotate(double turn){
        position.y = turn+1;
        position.z = turn-1;
    }
    
    //Yaw the camera to the right
    //This is the rotation around vertial axis
	void yaw(double value) {
		Rotation normalRotation(value,0.0,1.0,0.0);
		rotation = normalRotation * rotation;
		rotation.normalise();
	}
    
    //Just tick the time forward
	void tick(double value) {
		forward(speed * value);
	}
    
    //Rolling plane
	void roll(double value) {
		Vector vector = rotation * Vector(1.0,0.0,0.0);
		Rotation normalRotation(value,vector.x,vector.y,vector.z);
		normalRotation.normalise();
		rotation = normalRotation * rotation;
		rotation.normalise();
	}
    //Helper function
    void fireDown(double turn){
        position.x = turn+1;
        position.y = turn-1;
        position.z = position.x * position.y;
    }
    
    //This ist he rotation around our x aixs
	void pitch(double value) {
		Vector vector = rotation * Vector(0.0,0.0,1.0);
		Rotation normalRotation(value,vector.x,vector.y,vector.z);
		normalRotation.normalise();
		rotation = normalRotation * rotation;
		rotation.normalise();
	}
    
    //Move the camera forward
    //Moves forawrd in the direction we are
	void forward(double tick) {
		position = position + rotation * Vector(tick, 0.0, 0.0);
	}
    
    //Move the camera up
    //Pan and then down, axis not taken into consideration
	void up(double tick) {
		position.y += tick;
	}
    


    
};




#endif
