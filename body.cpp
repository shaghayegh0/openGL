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

    
    
    
