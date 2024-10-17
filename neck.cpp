// Draw the neck (a small cylinder)
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);  // Position the neck above the body
    glRotatef(90, 1.0, 0.0, 0.0);
    GLUquadric* neck = gluNewQuadric();
    gluCylinder(neck, 0.05, 0.1, 0.25, 20, 20);  // Small neck cylinder
    glPopMatrix();
