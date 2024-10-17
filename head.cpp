// Draw the head (a larger sphere) with rotation
    glPushMatrix();
    glTranslatef(0.0, 1.75, 0.0);  // Move the head above the neck
    glRotatef(headRotation, 0, 1, 0);  // Rotate the head around the neck
    glScalef(1.0, 1.2, 1.0);
    glutSolidSphere(0.75, 20, 20); // Draw a bigger sphere for the head

    
