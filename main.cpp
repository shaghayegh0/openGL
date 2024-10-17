#include <GLUT/glut.h>

// Initial angles for joint rotations
float leftArmAngle = 0.0f;
float rightArmAngle = 0.0f;
float cannonRotation = 0.0f;
float leftLegAngle = 0.0f;
float rightLegAngle = 0.0f;
float leftKneeAngle = 0.0f;   // Angle for left knee joint
float rightKneeAngle = 0.0f;  // Angle for right knee joint
float headRotation = 0.0f;   // New variable for head rotation
bool animating = false;
bool cannonSpinning = false;  // Flag to track if the cannon is spinning
bool leftStep = true;  // Track which leg is stepping (true = left leg, false = right leg)


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
    glPopMatrix();

    
    
    
    
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
        glScalef(1.0, 1.2, 1.0);
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

    
    
    // Draw the left leg (thigh) with hip joint
    glPushMatrix();
    // Move the left leg and hip up slightly during a left step
        glColor3f(0.0, 0.0, 0.0);
        if (leftStep) {
            glTranslatef(0.0, 0.1, 0.0);  // Shift left hip up
        }
        glTranslatef(-0.3, -1.0, 0.0);  // Position below the body

    // Add hip joint (small black sphere)
        glPushMatrix();
            glTranslatef(0.0, 0.5, 0.5);  // Move to the hip position
            glColor3f(0.0, 0.0, 0.0);
            glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the hip joint
        glPopMatrix();

        glRotatef(leftLegAngle, 1, 0, 0); // Rotate leg for stepping
        glScalef(0.2, 1.0, 0.2);
        glutSolidCube(1.0);              // Draw a cube representing the thigh

    // Draw the left knee joint (small ball)
        glPushMatrix();
            glTranslatef(0.0, -0.6, 0.0);   // Move to the knee position
            glColor3f(0.4, 0.4, 0.4);
            glutSolidSphere(0.4, 20, 20);  // Draw a small sphere for the knee joint
        glPopMatrix();

    // Draw the left lower leg (attached to the thigh)
        glPushMatrix();
            glTranslatef(0.0, -1.2, 0.0);   // Move down to the knee
            glColor3f(0.0, 0.0, 0.0);
            glRotatef(leftKneeAngle, 1, 0, 0); // Rotate lower leg at the knee
            glutSolidCube(1.0);             // Draw a cube representing the lower leg
        glPopMatrix();

    glPopMatrix();

    // Draw the right leg (thigh) with hip joint
    glPushMatrix();
    // Move the right leg and hip up slightly during a right step
        glColor3f(0.0, 0.0, 0.0);
        if (!leftStep) {
            glTranslatef(0.0, 0.1, 0.0);  // Shift right hip up
        }
        glTranslatef(0.3, -1.0, 0.0);   // Position below the body

    // Add hip joint (small black sphere)
        glPushMatrix();
            glTranslatef(0.0, 0.5, 0.5);  // Move to the hip position
            glColor3f(0.0, 0.0, 0.0);  //
            glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the hip joint
        glPopMatrix();

        glRotatef(rightLegAngle, 1, 0, 0); // Rotate leg for stepping
        glScalef(0.2, 1.0, 0.2);         // Make the leg long and thin
        glutSolidCube(1.0);              // Draw a cube representing the thigh

    // Draw the right knee joint (small ball)
        glPushMatrix();
            glTranslatef(0.0, -0.6, -0.5);   // Move to the knee position
            glColor3f(0.4, 0.4, 0.4);
            glutSolidSphere(0.4, 20, 20);
        glPopMatrix();

    // Draw the right lower leg (attached to the thigh)
        glPushMatrix();
            glTranslatef(0.0, -1.2, 0.0);   // Move down to the knee
            glColor3f(0.0, 0.0, 0.0);
            glRotatef(rightKneeAngle, 1, 0, 0); // Rotate lower leg at the knee
            glutSolidCube(1.0);             // Draw a cube representing the lower leg
        glPopMatrix();

    glPopMatrix();



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

// Timer function for leg animation (walking)
void stepForward(int value) {
    if (animating) {
        if (leftStep) {
            // Left leg steps forward
            leftLegAngle += 5.0f;
            rightLegAngle -= 5.0f;
            leftKneeAngle = -leftLegAngle / 2.0f; // Simulate bending the knee

            if (leftLegAngle >= 30.0f) {
                leftStep = false;  // Switch to right leg
            }
        } else {
            // Right leg steps forward
            leftLegAngle -= 5.0f;
            rightLegAngle += 5.0f;
            rightKneeAngle = -rightLegAngle / 2.0f; // Simulate bending the knee

            if (rightLegAngle >= 30.0f) {
                leftStep = true;  // Switch to left leg
            }
        }

        glutPostRedisplay();  // Redraw the scene with updated leg positions
        glutTimerFunc(100, stepForward, 0);  // Continue stepping every 100ms
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

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'l':  // Rotate left arm
            leftArmAngle += 5.0f;
            break;
        case 'r':  // Rotate right arm
            rightArmAngle += 5.0f;
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
        case 'n':  // Rotate head
            headRotation += 5.0f;
            break;
        case 'w':  // Start walking animation
            animating = true;
            glutTimerFunc(100, stepForward, 0);  // Start the timer for the animation
            break;
        case 'W':  // Reset walking animation
            leftLegAngle = 0.0f;
            rightLegAngle = 0.0f;
            leftKneeAngle = 0.0f;
            rightKneeAngle = 0.0f;
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
