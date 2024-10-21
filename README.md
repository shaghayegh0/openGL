# Bot 3D design - openGL

## I made the files in Xcode and compiled them in terminal

## How to run/compile in terminal:
- brew install glfw
- brew install freeglut  
- g++ -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION -o bot main.cpp QuadMesh.cpp
- ./bot

## Functionality:
- c => Start cannon spinning
- C => Stop cannon spinning
- l => Rotate left arm
- L => Rotate left arm in the opposite direction
- r => Rotate right arm
- R => Rotate right arm in the opposite direction
- h => Rotate hip joint
- H => Rotate hip joint in the opposite direction
- n => Rotate head
- N => Rotate head in the opposite direction
- w => Take one steo
- W => Reset animation and move to initial position
- t => Start walking

<img width="795" alt="Screenshot 2024-10-21 at 1 33 07 AM" src="https://github.com/user-attachments/assets/b8c8389c-e0dc-4e49-87fe-b90e51ae6e22">

