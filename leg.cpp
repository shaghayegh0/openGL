// Draw the left leg (thigh) with hip joint
    glPushMatrix();
    // Move the left leg and hip up slightly during a left step
    glColor3f(0.4, 0.4, 0.4);  // Set color to gray for the leg
    if (leftStep) {
        glTranslatef(0.0, 0.1, 0.0);  // Shift left hip up
    }
    glTranslatef(-0.3, -1.0, 0.0);  // Position below the body

    // Add hip joint (small black sphere)
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.5);  // Move to the hip position
    glColor3f(0.0, 0.0, 0.0);  // Set color to black for the hip joint
    glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the hip joint
    glPopMatrix();

    glRotatef(leftLegAngle, 1, 0, 0); // Rotate leg for stepping
    glScalef(0.4, 1.0, 0.2);         // Make the leg long and thin
    glutSolidCube(1.0);              // Draw a cube representing the thigh

    // Draw the left knee joint (small ball)
    glPushMatrix();
    glTranslatef(0.0, -0.6, 0.0);   // Move to the knee position
    glColor3f(0.0, 0.0, 0.0);  // Set color to black for the knee joint
    glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the knee joint
    glPopMatrix();

    // Draw the left lower leg (attached to the thigh)
    glPushMatrix();
    glTranslatef(0.0, -1.2, 0.0);   // Move down to the knee
    glColor3f(0.4, 0.4, 0.4);  // Set color to gray for the knee joint
    glRotatef(leftKneeAngle, 1, 0, 0); // Rotate lower leg at the knee
    glutSolidCube(1.0);             // Draw a cube representing the lower leg
    glPopMatrix();

    glPopMatrix();

    // Draw the right leg (thigh) with hip joint
    glPushMatrix();
    // Move the right leg and hip up slightly during a right step
    glColor3f(0.4, 0.4, 0.4);  // Set color to gray for the thigh
    if (!leftStep) {
        glTranslatef(0.0, 0.1, 0.0);  // Shift right hip up
    }
    glTranslatef(0.3, -1.0, 0.0);   // Position below the body

    // Add hip joint (small black sphere)
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.5);  // Move to the hip position
    glColor3f(0.0, 0.0, 0.0);  // Set color to black for the hip joint
    glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the hip joint
    glPopMatrix();

    glRotatef(rightLegAngle, 1, 0, 0); // Rotate leg for stepping
    glScalef(0.4, 1.0, 0.2);         // Make the leg long and thin
    glutSolidCube(1.0);              // Draw a cube representing the thigh

    // Draw the right knee joint (small ball)
    glPushMatrix();
    glTranslatef(0.0, -0.6, 0.0);   // Move to the knee position
    glColor3f(0.0, 0.0, 0.0);  // Set color to black for the knee joint
    glutSolidSphere(0.2, 20, 20);  // Draw a small sphere for the knee joint
    glPopMatrix();

    // Draw the right lower leg (attached to the thigh)
    glPushMatrix();
    glTranslatef(0.0, -1.2, 0.0);   // Move down to the knee
    glColor3f(0.4, 0.4, 0.4);  // Set color to gray for the knee joint
    glRotatef(rightKneeAngle, 1, 0, 0); // Rotate lower leg at the knee
    glutSolidCube(1.0);             // Draw a cube representing the lower leg
    glPopMatrix();

    glPopMatrix();
