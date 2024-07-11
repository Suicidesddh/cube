#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float rotationAngle = 0.0f;

void drawCube() {
    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom-left
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-right
    glVertex3f(1.0f, 1.0f, 1.0f);   // Top-right
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top-left

    // Back face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-left
    glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom-right
    glVertex3f(1.0f, 1.0f, -1.0f);   // Top-right
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-left

    // Left face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-back
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom-front
    glVertex3f(-1.0f, 1.0f, 1.0f);   // Top-front
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-back

    // Right face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(1.0f, -1.0f, -1.0f); // Bottom-back
    glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-front
    glVertex3f(1.0f, 1.0f, 1.0f);   // Top-front
    glVertex3f(1.0f, 1.0f, -1.0f);  // Top-back

    // Top face
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Front-left
    glVertex3f(1.0f, 1.0f, 1.0f);   // Front-right
    glVertex3f(1.0f, 1.0f, -1.0f);  // Back-right
    glVertex3f(-1.0f, 1.0f, -1.0f); // Back-left

    // Bottom face
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(-1.0f, -1.0f, -1.0f); // Back-left
    glVertex3f(1.0f, -1.0f, -1.0f);  // Back-right
    glVertex3f(1.0f, -1.0f, 1.0f);   // Front-right
    glVertex3f(-1.0f, -1.0f, 1.0f);  // Front-left

    glEnd();
}

void setupProjection(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float) width / (float) height;
    float fovY = 60.0f; // Field of view angle, in degrees
    float zNear = 0.1f; // Near clipping plane
    float zFar = 100.0f; // Far clipping plane

    // Calculate the perspective projection matrix
    float f = 1.0f / tanf((fovY / 2.0f) * (M_PI / 180.0f));
    float projectionMatrix[] = {
        f / aspectRatio, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), -1.0f,
        0.0f, 0.0f, (2.0f * zFar * zNear) / (zNear - zFar), 0.0f
    };

    glMultMatrixf(projectionMatrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Rotating Cube Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up projection matrix and viewport
        setupProjection(width, height);

        // Setup modelview matrix
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        
        // Rotate the cube around Y axis
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

        // Draw a cube
        drawCube();

        // Increase rotation angle for the next frame
        rotationAngle += 0.5f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

