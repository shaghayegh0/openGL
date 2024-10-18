#include <GLUT/glut.h>
#include <thread>
#include <chrono>
//#include "QuadMesh.h"


// Initial angles for joint rotations
float leftArmAngle = 0.0f;
float rightArmAngle = 0.0f;
float cannonRotation = 0.0f;
float headRotation = 0.0f;   // New variable for head rotation

float hipAngle = 0.0f;  // Angle for the hip joint movement
float hipVerticalShift = 0.0f;  // Vertical shift for hip during walking

float hipShift = 0.0f; // Controls hip vertical movement
float leftLegAngle = 0.0f, rightLegAngle = 0.0f;
float leftKneeAngle = 180.0f, rightKneeAngle = 180.0f;
float hipIncrement = 0.5f; // Hip vertical shift increment
float legIncrement = 5.0f; // Leg rotation increment

float botPositionX = 0.0f;
float botPositionY = 0.0f;
float botPositionZ = 0.0f;
float stepSize = 0.1f;

bool cannonSpinning = false;  // Flag to track if the cannon is spinning
bool leftStep = true;  // Track which leg is stepping (true = left leg, false = right leg)
bool animating = true; // Toggle animation






// Function prototypes
void stepForward(int value);
void updateCannonRotation(int value);  // Function to update cannon rotation

// Function to set up the display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera view
    gluLookAt(0.0, 5.0, 10.0,  // Eye position
              0.0, 0.0, 0.0,   // Look-at point
              0.0, 1.0, 0.0);  // Up direction
    
    
    
    
    // Set body color to metal gray
    glColor3f(0.5, 0.5, 0.5);  // Metallic gray

    // Draw the body (an uneven trapezoidal body)
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);  // Move to the origin
        glTranslatef(botPositionX, botPositionY, botPositionZ);
        // Use GL_QUADS to draw the trapezoid-like body
        glBegin(GL_QUADS);

        // Front face (trapezoidal)
        glVertex3f(-0.8, -0.5, 0.5);  // Bottom-left
        glVertex3f(0.8, -0.5, 0.5);   // Bottom-right
        glVertex3f(0.5, 0.5, 0.5);    // Top-right (smaller top width)
        glVertex3f(-0.5, 0.5, 0.5);   // Top-left (smaller top width)

        // Back face (trapezoidal)
        glVertex3f(-0.8, -0.5, -0.5);  // Bottom-left
        glVertex3f(0.8, -0.5, -0.5);   // Bottom-right
        glVertex3f(0.5, 0.5, -0.5);    // Top-right (smaller top width)
        glVertex3f(-0.5, 0.5, -0.5);   // Top-left (smaller top width)

        // Left face (rectangular)
        glVertex3f(-0.8, -0.5, 0.5);  // Front-bottom-left
        glVertex3f(-0.8, -0.5, -0.5); // Back-bottom-left
        glVertex3f(-0.5, 0.5, -0.5);  // Back-top-left
        glVertex3f(-0.5, 0.5, 0.5);   // Front-top-left

        // Right face (rectangular)
        glVertex3f(0.8, -0.5, 0.5);   // Front-bottom-right
        glVertex3f(0.8, -0.5, -0.5);  // Back-bottom-right
        glVertex3f(0.5, 0.5, -0.5);   // Back-top-right
        glVertex3f(0.5, 0.5, 0.5);    // Front-top-right

        // Top face (smaller rectangle)
        glVertex3f(-0.5, 0.5, 0.5);   // Front-top-left
        glVertex3f(0.5, 0.5, 0.5);    // Front-top-right
        glVertex3f(0.5, 0.5, -0.5);   // Back-top-right
        glVertex3f(-0.5, 0.5, -0.5);  // Back-top-left

        // Bottom face (larger rectangle)
        glVertex3f(-0.8, -0.5, 0.5);  // Front-bottom-left
        glVertex3f(0.8, -0.5, 0.5);   // Front-bottom-right
        glVertex3f(0.8, -0.5, -0.5);  // Back-bottom-right
        glVertex3f(-0.8, -0.5, -0.5); // Back-bottom-left

        glEnd();
    

    
    
    
    
        // Draw the neck (a small cylinder)
        glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);  // Position the neck above the body
            glRotatef(90, 1.0, 0.0, 0.0);
            GLUquadric* neck = gluNewQuadric();
            gluCylinder(neck, 0.05, 0.1, 0.25, 20, 20);  // Small neck cylinder
        glPopMatrix();

        // Draw the head (a larger sphere) with rotation
        glPushMatrix();
            glTranslatef(0.0, 1.75, 0.0);  // Move the head above the neck
            glRotatef(headRotation, 0, 1, 0);  // Rotate the head around the neck
            glScalef(1.0, 1.1, 1.0);
        glutSolidSphere(0.75, 20, 20); // Draw a bigger sphere for the head

        // Draw the eyes (two green spheres)
        glColor3f(0.0, 1.0, 0.0);  // Set color to green
            glPushMatrix();
            glTranslatef(-0.35, 0.3, 0.7);  // Left eye position in front of head
            glutSolidSphere(0.2, 20, 20);   // Draw left eye
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.35, 0.3, 0.7);   // Right eye position in front of head
            glutSolidSphere(0.2, 20, 20);   // Draw right eye
        glPopMatrix();

        // Draw the cannon (cylinder on top of the head with rotation)
        glColor3f(0.0, 0.0, 0.0);  // Set color to black
        glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);  // Place the cannon directly on top of the head
            glRotatef(90, 1, 0, 0);  // Rotate 90 degrees around the x-axis to make it vertical
            glRotatef(cannonRotation, 0, 0, 1);  // Apply the rotation around the z-axis for spinning
            GLUquadric* cannon = gluNewQuadric();
            gluCylinder(cannon, 0.08, 0.1, 0.3, 20, 20);  // Draw the cannon cylinder

            // Add small sub-part to the cannon (small sphere)
            glColor3f(1.0, 0.0, 0.0);  // Set color to red for sub-part
                glPushMatrix();
                    glTranslatef(0.08, 0.1, 0.0);  // Position a small sphere on the side of the cannon
                    glutSolidSphere(0.05, 10, 10);  // Draw a small sphere
                glPopMatrix();
        
            glPopMatrix();  // End cannon drawing

        glPopMatrix();  // End head drawing

       
        // Draw left arm
        glPushMatrix();
            glTranslatef(-0.65, 0.6, 0.0); // Position on the left side

        // Shoulder joint
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);  // Set color to black for the shoulder joint
                glutSolidSphere(0.2, 20, 20); // Shoulder joint sphere
            glPopMatrix();

        // Rotate arm outward for "V" shape
            glRotatef(-30, 0, 0, 1);

            glRotatef(leftArmAngle, 1, 0, 0); // Rotate arm at shoulder
            glTranslatef(0.0, -0.5, 0.0); // Move down for upper arm

        // Upper arm
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);  // Set color to black for the upper arm
                glScalef(0.2, 0.8, 0.2);  // Thin and long upper arm
                glutSolidCube(1.0);
            glPopMatrix();

        // Elbow joint
            glPushMatrix();
                glTranslatef(0.0, -0.5, 0.0); // Move to elbow position
                glColor3f(0.5, 0.5, 0.5);  // Set color to black for the elbow joint
                glutSolidSphere(0.15, 20, 20); // Elbow joint sphere
            glPopMatrix();

        // Lower arm
            glPushMatrix();
                glTranslatef(0.0, -1.0, 0.0);  // Move down to lower arm position
                glColor3f(0.0, 0.0, 0.0); // Set color to black for the lower arm
                glScalef(0.2, 0.8, 0.2);  // Thin lower arm
                glutSolidCube(1.0);
            glPopMatrix();

        // Palm
            glPushMatrix();
                glTranslatef(0.0, -1.5, 0.0);  // Move to the palm position
                glColor3f(0.4, 0.4, 0.4);  // Gray palm
                glutSolidSphere(0.25, 20, 20);  // Palm sphere
            glPopMatrix();

        glPopMatrix();

        // Draw right arm
        glPushMatrix();
            glTranslatef(0.65, 0.6, 0.0); // Position on the right side

        // Shoulder joint
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);  // Set color to black for the shoulder joint
                glutSolidSphere(0.2, 20, 20); // Shoulder joint sphere
            glPopMatrix();

        // Rotate arm outward for "V" shape
            glRotatef(30, 0, 0, 1); // Rotate around z-axis for a "V" angle

            glRotatef(rightArmAngle, 1, 0, 0); // Rotate arm at shoulder
            glTranslatef(0.0, -0.5, 0.0); // Move down for upper arm

        // Upper arm
            glPushMatrix();
                glColor3f(0.0, 0.0, 0.0);  // Set color to black for the upper arm
                glScalef(0.2, 0.8, 0.2);  // Thin and long upper arm
                glutSolidCube(1.0);
            glPopMatrix();

        // Elbow joint
            glPushMatrix();
                glTranslatef(0.0, -0.5, 0.0); // Move to elbow position
                glColor3f(0.5, 0.5, 0.5);  // Set color to gray for the elbow joint
                glutSolidSphere(0.15, 20, 20); // Elbow joint sphere
            glPopMatrix();

        // Lower arm
            glPushMatrix();
                glTranslatef(0.0, -1.0, 0.0);  // Move down to lower arm position
                glColor3f(0.0, 0.0, 0.0); // Set color to black for the lower arm
                glScalef(0.2, 0.8, 0.2);  // Thin lower arm
                glutSolidCube(1.0);
            glPopMatrix();

        // Palm
            glPushMatrix();
                glTranslatef(0.0, -1.5, 0.0);  // Move to the palm position
                glColor3f(0.4, 0.4, 0.4);  // Gray palm
                glutSolidSphere(0.25, 20, 20);  // Palm sphere
            glPopMatrix();

        glPopMatrix();

        
        // Draw the hip joint (rectangle)
        glPushMatrix();
            // Apply vertical shift and hip rotation
            glTranslatef(0.0, -1 + hipVerticalShift, 0.0);  // Move hip under body, apply vertical shift
            glRotatef(hipAngle, 0, 1, 0);  // Rotate hip joint

            // ** Draw the legs before scaling the hip **
            // Left leg
            glPushMatrix();
                // Translate relative to the hip position
                glTranslatef(-0.3, -0.6, 0.0);  // Adjust leg translation
                glRotatef(leftLegAngle, 1, 0, 0); // Rotate leg at the hip joint
                glColor3f(0.0, 0.0, 0.0); // Black thigh
                glScalef(0.2, 1.0, 0.2);  // Scale for leg
                glutSolidCube(1.0);  // Thigh

                // Draw the knee and lower leg
                glPushMatrix();
                    glTranslatef(0.0, -0.6, 0.0); // Move to knee position
                    glColor3f(0.4, 0.4, 0.4); // Gray knee joint
                    glutSolidSphere(0.2, 20, 20); // Knee joint

                    // Lower leg
                    glPushMatrix();
                        glTranslatef(0.0, -0.6, 0.0); // Move down from knee
                        glRotatef(leftKneeAngle, 1, 0, 0); // Rotate at knee
                        glColor3f(0.0, 0.0, 0.0); // Black lower leg
                        glutSolidCube(1.0); // Lower leg
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

            // Right leg
            glPushMatrix();
                glTranslatef(0.3, -0.6, 0.0);  // Adjust right leg translation
                glRotatef(rightLegAngle, 1, 0, 0); // Rotate leg at hip joint
                glColor3f(0.0, 0.0, 0.0); // Black thigh
                glScalef(0.2, 1.0, 0.2);  // Scale for leg
                glutSolidCube(1.0);  // Thigh

                // Knee and lower leg
                glPushMatrix();
                    glTranslatef(0.0, -0.6, 0.0); // Move to knee position
                    glColor3f(0.4, 0.4, 0.4); // Gray knee joint
                    glutSolidSphere(0.2, 20, 20); // Knee joint

                    // Lower leg
                    glPushMatrix();
                        glTranslatef(0.0, -0.6, 0.0); // Move down from knee
                        glRotatef(rightKneeAngle, 1, 0, 0); // Rotate at knee
                        glColor3f(0.0, 0.0, 0.0); // Black lower leg
                        glutSolidCube(1.0); // Lower leg
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

            // Scale the hip at the end
            glColor3f(0.5, 0.0, 0.0); // Color for hip (reddish)
            glScalef(1.0, 0.2, 0.5);  // Scale to make hip rectangle
            glutSolidCube(1.0);       // Draw hip cube

        glPopMatrix();  // End of hip joint and leg assembly
    glPopMatrix(); // End of body
    
    glutSwapBuffers();
}

// Timer function for cannon rotation
void updateCannonRotation(int value) {
    if (cannonSpinning) {
        cannonRotation += 5.0f;  // Increment the cannon rotation angle
        if (cannonRotation > 360.0f) {
            cannonRotation -= 360.0f;  // Keep the rotation angle within 360 degrees
        }
        glutPostRedisplay();  // Redraw the scene with the updated rotation
        glutTimerFunc(50, updateCannonRotation, 0);  // Continue rotating the cannon every 50ms
    }
}

// write a step forward function where it shows taking one step
void stepForward(int value) {
    if (animating) {
        // Step phase: right leg moves
        if (rightLegAngle > -30.0f) {
            // Right leg moves forward
            rightLegAngle -= legIncrement;
            // Right knee bends
            rightKneeAngle -= legIncrement;
            if (rightKneeAngle < 120.0f) rightKneeAngle = 120.0f;
            // Right side of the hip shifts up, left side shifts down
            hipVerticalShift += hipIncrement;
            if (hipVerticalShift > 0.3f) hipVerticalShift = 0.3f;  // Limit hip shift
            //Update the bot's position (moving in the z direction)
            botPositionZ += stepSize;
        } else if (rightLegAngle <= -30.0f && rightKneeAngle < 180.0f) {
            // Straighten the right knee
            rightKneeAngle += legIncrement;
            if (rightKneeAngle > 180.0f) rightKneeAngle = 180.0f;
            
            
            // Reset hip shift back down
            hipVerticalShift -= hipIncrement;
            if (hipVerticalShift < 0.0f) hipVerticalShift = 0.0f;
        }

        // Stop animation after one full step
        if (rightLegAngle <= -30.0f && rightKneeAngle == 180.0f && hipVerticalShift == 0.0f) {
            animating = false;
        }

        // Redraw the scene with updated leg and hip positions
        glutPostRedisplay();
        // Continue animation every 100ms
        glutTimerFunc(100, stepForward, 0);
    }
}




// Function to handle reshaping the window
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void updateBotMovement() {
    float stepSize = 0.1f;  // Define the step size, adjust as needed
    stepForward(stepSize);  // Call the stepForward function with the step size
}


// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'l':  // Rotate left arm
            leftArmAngle += 5.0f;
            break;
        case 'L':  // Rotate left arm
            leftArmAngle -= 5.0f;
            break;
        case 'r':  // Rotate right arm
            rightArmAngle += 5.0f;
            break;
        case 'R':  // Rotate right arm
            rightArmAngle -= 5.0f;
            break;
        case 'c':  // Start cannon spinning
            if (!cannonSpinning) {
                cannonSpinning = true;
                glutTimerFunc(50, updateCannonRotation, 0);  // Start the timer for cannon rotation
            }
            break;
        case 'C':  // Stop cannon spinning
            cannonSpinning = false;
            break;
            
        case 'h':  // Rotate hip joint positively
            hipAngle += 5.0f;
            break;
        case 'H':  // Rotate hip joint negatively
            hipAngle -= 5.0f;
            break;
            
        
        case 'n':  // Rotate head
            headRotation += 5.0f;
            break;
            
        case 'w':  // Start stepForward animation
            animating = true;
            glutTimerFunc(100, stepForward, 0);  // Start the timer for the animation
            break;
        case 'W':  // Reset stepForward animation
            leftLegAngle = 0.0f;
            rightLegAngle = 0.0f;
            leftKneeAngle = 0.0f;
            rightKneeAngle = 0.0f;
            botPositionZ = 0.0f;
            animating = false;
            break;
    }
    glutPostRedisplay();  // Redisplay after change
}

// Initialization function for OpenGL settings
void initOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glEnable(GL_DEPTH_TEST);           // Enable depth testing
}



// Main function to initialize GLUT and create the window
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("CPS511 Assignment - 3D Bot with Knee Joints");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);  // Register keyboard handler

    glutMainLoop();
    return 0;
}
