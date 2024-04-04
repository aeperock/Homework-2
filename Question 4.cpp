#include <GL/glut.h>
#include <cmath>

// Parameters
const float rho = 1.225; // Air density (kg/m^3)
const float S = 10.0;    // Wing area (m^2)
const float CL = 1.2;    // Lift coefficient
const float startVelocity = 0.0; // Start velocity
const float endVelocity = 100.0; // End velocity
const float velocityStep = 1.0;  // Velocity step

// Function to calculate lift force
float calculateLift(float velocity) {
    return 0.5 * rho * velocity * velocity * S * CL;
}

// Function to plot the graph
void plotGraph() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Draw x and y axis
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1500.0);
    glEnd();

    // Plot the lift equation
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    glBegin(GL_LINE_STRIP);
    for (float v = startVelocity; v <= endVelocity; v += velocityStep) {
        float lift = calculateLift(v);
        glVertex2f(v, lift);
    }
    glEnd();

    glFlush();
}

// Initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 100.0, 0.0, 1500.0); // Set the range of x and y axis
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Lift Equation Graph"); // Set window title

    init(); // Initialize OpenGL parameters
    glutDisplayFunc(plotGraph); // Call the function to plot the graph

    glutMainLoop();
    return 0;
}
