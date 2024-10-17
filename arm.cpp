
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

    
