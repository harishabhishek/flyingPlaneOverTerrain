//
//  main.cpp
//  CS 418 MP2
//
//  Created by Abhishek Harish on 3/9/14.
//  Copyright (c) 2014 Abhishek Harish. All rights reserved.
//


#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Vector.h"
#include "Camera_Update.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

/*
 *Defined Macros for the various numbers
 */
#define increment 0.005
#define sea_increment 0.005
#define DEG 60
#define TOL 0.0001


// The default Camera
Camera_Update camera;

// The default camera direction as a vector for call to gluLookAt()
double direction_default[3] = {1.0,0.0,0.0};

// Up direction for the Camera
double up_direction[3]  = {0.0,0.0,1.0};


//Given Globals from the mountain calss
float sealevel;
float polysize;







/*
 * Given code in the Mountain class
 */
int seed(float x, float y) {
	static int a = 1588635695, b = 1117695901;
	int xi = *(int *)&x;
	int yi = *(int *)&y;
	return ((xi * a) % b) - ((yi * b) % a);
}

/*
 *Given code in the Mountain class
 *Nothing fancy done here
 */
void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s)
{
	float x01,y01,z01,x12,y12,z12,x20,y20,z20;
    
	glShadeModel(GL_SMOOTH);
	if (s < polysize) {
		x01 = x1 - x0;
		y01 = y1 - y0;
		z01 = z1 - z0;
        
		x12 = x2 - x1;
		y12 = y2 - y1;
		z12 = z2 - z1;
        
		x20 = x0 - x2;
		y20 = y0 - y2;
		z20 = z0 - z2;
        
		float nx = y01*(-z20) - (-y20)*z01;
		float ny = z01*(-x20) - (-z20)*x01;
		float nz = x01*(-y20) - (-x20)*y01;
        
		float den = sqrt(nx*nx + ny*ny + nz*nz);
        
		if (den > 0.0) {
			nx /= den;
			ny /= den;
			nz /= den;
		}
        
		glNormal3f(nx,ny,nz);
		glBegin(GL_TRIANGLES);
		glVertex3f(x0,y0,z0);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glEnd();
        
		return;
        
	}
    
	x01 = 0.5*(x0 + x1);
	y01 = 0.5*(y0 + y1);
	z01 = 0.5*(z0 + z1);
    
	x12 = 0.5*(x1 + x2);
	y12 = 0.5*(y1 + y2);
	z12 = 0.5*(z1 + z2);
    
	x20 = 0.5*(x2 + x0);
	y20 = 0.5*(y2 + y0);
	z20 = 0.5*(z2 + z0);
    
	s *= 0.5;
    
	srand(seed(x01,y01));
	z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x12,y12));
	z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x20,y20));
	z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    
	mountain(x0,y0,z0,x01,y01,z01,x20,y20,z20,s);
	mountain(x1,y1,z1,x12,y12,z12,x01,y01,z01,s);
	mountain(x2,y2,z2,x20,y20,z20,x12,y12,z12,s);
	mountain(x01,y01,z01,x12,y12,z12,x20,y20,z20,s);
}


//Rolling up the camera
void update_roll_camera(){
	Vector vector = camera.rotation * Vector(0.0,1.0,0.0);
    up_direction[1] = vector.z;
	up_direction[2] = vector.y;
    up_direction[0] = vector.x;
    
    
}

//THe direction of the camera
void update_direction_camera(){
    Vector vector = camera.rotation * Vector(1.0,0.0,0.0);
    direction_default[1] = vector.z;
	direction_default[2] = vector.y;
	direction_default[0] = vector.x;
    
}



/*
 *The function to update the Vectors and
 Rotate and Updatet eh direction Accordingly
 */
void updateVectors() {
    //Click the time clock
	camera.tick(0.05);
    
	//THe direction of the camera
    update_direction_camera();
    
    //Rolling up the camera
    update_roll_camera();
    
}
/*
 *Given code in the Mountain class
 */
void init(void)
{
    
	glClearColor (0.5, 0.5, 1.0, 0.0);
	/* glShadeModel (GL_FLAT); */
	glEnable(GL_DEPTH_TEST);
    
	gluLookAt(0.0,0.0,0.0,
			  1.0,0.0,0.0,
			  0.0,0.0,1.0);
	sealevel = 0.0;
	polysize = 0.01;
}


/*
 *Given code in the Mountain class
 *Has modifications so that the lookat matrix is updated 
 *Also has the code for changing the lightings on the terrain
 */
void terrain_display(void)
{
	/*
     *Loading an identitiy Matrix
     *Then updating the vectors 
     *finally updating the lookat vector
     *The modification in the given code
     */
	glLoadIdentity ();
	updateVectors();
    
	gluLookAt (camera.position.x,
               camera.position.z,
               camera.position.y,
			   camera.position.x + direction_default[0],
			   camera.position.z + direction_default[1],
			   camera.position.y + direction_default[2],
			   up_direction [0],
               up_direction [1],
               up_direction [2]);
    
    
    /*
     *The lighting options in OpenGL
     */
    //Light Color and light position
    GLfloat white[] = {0.8,0.8,0.8,1.0};
	GLfloat lpos[] = {2.5,2.5,2,5,0.0};
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    /*
     *Given code
     *just changed it a bit here or there
     */
	GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
	GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
    
	GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
	GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
	GLfloat seaspec[] = {0.5,0.5,1.0,1.0};
    
    
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glTranslatef (-0.5, -0.5, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tandiff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    /*
     * The call to create default maountains
     */
	mountain(0.0,0.0,0.0, 1.0,0.0,0.0, 0.0,1.0,0.0, 1.0);
	mountain(1.0,1.0,0.0, 0.0,1.0,0.0, 1.0,0.0,0.0, 1.0);
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
	glNormal3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
	glVertex3f(0.0,0.0,sealevel);
	glVertex3f(1.0,0.0,sealevel);
	glVertex3f(1.0,1.0,sealevel);
	glVertex3f(0.0,1.0,sealevel);
	glEnd();
    
	glutSwapBuffers();
	glFlush ();
    
    
	glutPostRedisplay();
}

/*
 *The function to repain and reshape the changes that we have encountered with the
 */
void reshape_repaint_re (int width, int height)
{
	glViewport (0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90.0,(double)width / (double)height,0.0001,10.0);
	glMatrixMode (GL_MODELVIEW);
}

/*
 *The function to handle the keyboard keys
 *Used from the mountain code and added new key assignments
 */
void keyboard_handler(unsigned char key, int x, int y)
{
    float finer = 0.5;
    float coarse = 2.0;
	switch (key) {
            
        /*
         *Functions manipulating the terrain
         */
            //Change the dea level down
		case '1':
			sealevel -= sea_increment;
			break;
            
            //Change the sea level up
		case '2':
			sealevel += sea_increment;
			break;
            
            //Make the terrain finer
		case '3':
			polysize *= finer;
			break;
            
            //Make the terrain coarse
		case '4':
			polysize *= coarse;
			break;
        /*
         *Fuctions to move the plane
         */
            //Move the plane down
		case 'q':
			camera.up(-increment);
			break;
            
            //Move the plane up
		case 'e':
			camera.up(increment);
			break;
            
            //Spped up the plane
		case 'w':
			camera.speed += increment;
			break;
            
            //Slow down the place
		case 's':
			camera.speed -= increment;
			break;
            
            //Yaw left
		case 'a':
			camera.yaw(-DEG);
			break;
            
            //Yaw Right
		case 'd':
			camera.yaw(DEG);
			break;
            
            //if exc key, exit
        case 27:
			exit(0);
			break;
	}
}


/* 
 * The function to handle the arrow keys
 * The function uses the default callback function from OpenGL
 */
void arrowkeys_handler(int key, int x, int y) {
	switch (key) {
            
            //Roll left
		case GLUT_KEY_LEFT:
			camera.roll(DEG);
			break;
            
            //Roll right
		case GLUT_KEY_RIGHT:
			camera.roll(-DEG);
			break;
            
            // pitch up
		case GLUT_KEY_UP:
			camera.pitch(-DEG);
			break;
            
            //Pitch down
		case GLUT_KEY_DOWN:
			camera.pitch(DEG);
			break;
	}
}


/**
 *The main function for the MP
 *This function initializez all the handlers
 *Creates a new window and calls
 *the main game loop to continue
 **/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50, 50);
	glutInitWindowSize (1000, 1000);
	glutCreateWindow (argv[0]);
	init ();
    glutSpecialFunc(arrowkeys_handler);
	glutReshapeFunc(reshape_repaint_re);
	glutDisplayFunc(terrain_display);
	glutKeyboardFunc(keyboard_handler);
	glutMainLoop();
	return 0;
}

