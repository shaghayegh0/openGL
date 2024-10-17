// Draw the left arm (long and thin)
    glPushMatrix();
    glTranslatef(-0.75, 0.5, 0.0);  // Position on the left side
    glRotatef(leftArmAngle, 1, 0, 0);  // Rotate the arm around its joint
    glRotatef(90, 0, 1, 0);        // Align the cylinder
    GLUquadric* leftArm = gluNewQuadric();
    gluCylinder(leftArm, 0.1, 0.1, 2.0, 20, 20);  // Draw a long, thin cylinder
    glPopMatrix();

    // Draw the right arm (long and thin)
    glPushMatrix();
    glTranslatef(0.75, 0.5, 0.0);   // Position on the right side
    glRotatef(rightArmAngle, 1, 0, 0);  // Rotate the arm around its joint
    glRotatef(-90, 0, 1, 0);       // Align the cylinder
    GLUquadric* rightArm = gluNewQuadric();
    gluCylinder(rightArm, 0.1, 0.1, 2.0, 20, 20);  // Draw a long, thin cylinder
    glPopMatrix();
