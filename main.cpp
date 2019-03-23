//
//  main.cpp
//  1
//
//  Created by Mariya Masud on 17.03.19.
//  Copyright © 2019 Mariya Masud. All rights reserved.
//

#include <iostream>
#include <Glut/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN         (-1.0+r)
#define MAX         ( 1.0-r)
#define abs(i)      ((i<0.0)?-i:i)
#define NBALLS      20
#define randf()     ((float)rand()/(float)RAND_MAX)

int rt=0;
float px[NBALLS], py[NBALLS], pz[NBALLS], vx[NBALLS], vy[NBALLS], vz[NBALLS];
float tm,th;
const float g = 9.8;
const float r = 0.05;
const float dt = 0.001;
const float cor = 0.6;

void init() {
    int i;
    srand(time(NULL));
    for (i=0;i<NBALLS;i++) {
        px[i] = MIN + randf()*(MAX-MIN);
        py[i] = MIN + randf()*(MAX-MIN);
        pz[i] = 0.9;
        vx[i] = -1.5+randf()*3.0;
        vy[i] = -1.5+randf()*3.0;
        vz[i] = -1.0+randf()*2.0;
    }
    tm = 0.0;
    
    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,1.0,1.0,50.0);
    glTranslatef(0.0,0.0,-3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update() {
    int i;
    tm += dt;
    for (i=0;i<NBALLS;i++) {
        vz[i] += -g*dt;
        px[i] += vx[i]*dt;
        py[i] += vy[i]*dt;
        pz[i] += vz[i]*dt;
        
        if (abs(px[i]) >= MAX) {
            vx[i] *= -cor;
            px[i] = (px[i]<0)?MIN:MAX;
        }
        if (abs(py[i]) >= MAX) {
            vy[i] *= -cor;
            py[i] = (py[i]<0)?MIN:MAX;
        }
        if (abs(pz[i]) >= MAX) {
            vz[i] *= -cor;
            pz[i] = (pz[i]<0)?MIN:MAX;
        }
        
    }
    
    if (rt) {
        th += 0.2;
        if (th>360.0) th -= 360.0;
    }
    
    glutPostRedisplay();
}

void draw() {
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(th,0.0,1.0,0.0);
    glRotatef(90.0,-1.0,0.0,0.0);
    glutWireCube(2.0);
    for (i=0;i<NBALLS;i++) {
        glPushMatrix();
        glTranslatef(px[i],py[i],pz[i]);
        glutSolidSphere(r,50,50);
        glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            rt = !state;
            break;
        case GLUT_RIGHT_BUTTON:
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bouncing Ball");
    glutIdleFunc(update);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
