#include <cstdlib>
#include <iostream>
#include <algorithm>   

#include "Angel.h"
#include "Globals.h"

#include "Scene.h"
#include "camera.h"

#include "house.h"
#include "HouseModern.h"
#include "HouseModern3F.h"
#include "Road.h"

#include "ToyTrain.h"
#include "ToyTrain1.h"
#include "CycleRail.h"
#include "CityInside.h"
// ================== CAMERA ==================
Camera camera;
int lastX = 800, lastY = 800;
bool firstMouse = true;

// ================== GLOBAL ==================
mat4 model = mat4(1.0f);   // Ma trận model gốc
Scene* scene = nullptr;

// ================== SHADER ==================
void shaderSetup() {
    std::cout << "Loading shaders..." << std::endl;

    program = InitShader("vshader1.glsl", "fshader1.glsl");
    if (program == 0) {
        std::cerr << "ERROR: Shader program failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glUseProgram(program);

    model_loc = glGetUniformLocation(program, "Model");
    view_loc = glGetUniformLocation(program, "View");
    projection_loc = glGetUniformLocation(program, "Projection");

    // ===== ÁNH SÁNG BLINN-PHONG =====
    point4 light_position(0.0f, 3.0f, 5.0f, 1.0f);
    color4 light_ambient(0.3f, 0.3f, 0.3f, 1.0f);
    color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);

    glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
    glUniform4fv(glGetUniformLocation(program, "LightAmbient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "LightDiffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "LightSpecular"), 1, light_specular);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// ================== DISPLAY ==================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // View
    mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);

    // Projection (FIX: theo aspect ratio)
    float aspect = (float)glutGet(GLUT_WINDOW_WIDTH) /
        (float)glutGet(GLUT_WINDOW_HEIGHT);

    mat4 projection = Perspective(45.0f, aspect, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

    // Model gốc
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

    if (scene)
        scene->draw(model);

    glutSwapBuffers();
}

// ================== RESHAPE ==================
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

// ================== KEYBOARD ==================
void keyboard(unsigned char key, int, int) {
    vec3 front = camera.getFront();
    vec3 right = normalize(cross(front, vec3(0.0f, 1.0f, 0.0f)));

    switch (key) {
    case 'w': camera.position += camera.speed * front; break;
    case 's': camera.position -= camera.speed * front; break;
    case 'a': camera.position -= camera.speed * right; break;
    case 'd': camera.position += camera.speed * right; break;

    case ' ': camera.position.y += camera.speed; break;
    case 'c': camera.position.y -= camera.speed; break;
    case '9':
        g_trainMove = !g_trainMove;   // bật / tắt chuyển động
        break;

    case 27: exit(EXIT_SUCCESS); // ESC
    }

    glutPostRedisplay();
}

// ================== MOUSE ==================
void mouseMotion(int x, int y) {
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float dx = (float)(x - lastX);
    float dy = (float)(lastY - y); // đảo trục Y

    lastX = x;
    lastY = y;

    dx *= camera.sensitivity;
    dy *= camera.sensitivity;

    // Chuột trái/phải → quay ngang (quay ra sau)
    camera.yaw += dx;

    // Chuột lên/xuống → ngẩng / cúi
    camera.pitch += dy;

    // ❗ Giới hạn pitch – KHÔNG cho lật
    if (camera.pitch > 89.0f)  camera.pitch = 89.0f;
    if (camera.pitch < -89.0f) camera.pitch = -89.0f;

    // CẬP NHẬT vector camera
    camera.updateCameraVectors();

    glutPostRedisplay();
    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    glutWarpPointer(cx, cy);
    lastX = cx;
    lastY = cy;
}


// ================== MAIN ==================
int main(int argc, char** argv) {
    std::cout << "Starting program..." << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Blinn-Phong Table - Hierarchical Model");

    // GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return EXIT_FAILURE;
    }

    shaderSetup();

    // ===== SCENE =====
    scene = new Scene();

    // ================== NHÀ ==================
    scene->addShape(new House());
    scene->addShape(
        new TransformShape(
            Translate(15.0f, 0.0f, 0.0f),
            new HouseModern()
        )
    );
    scene->addShape(
        new TransformShape(
            Translate(-15.0f, 0.0f, 0.0f),
            new HouseModern3F()
        )
    );
    scene->addShape(
        new TransformShape(
            Translate(0.0f, -0.25f, 30.0f) *
            RotateY(90.0f),
            new RoadWithTrees()
        )
    );

    // ================== TẦNG 1 – PHÒNG KHÁCH ==================

    //mô hình tàu tầng 2
    scene->addShape(
        new TransformShape(
            Translate(0.0f, 6.0f + 0.15f, 5.0f),
            new ToyTrain(0.2f)
        )
    );
    scene->addShape(
        new TransformShape(
            Translate(0.0f, 6.0f + 0.1f, 5.0f),
            new CycleRail(3.0f, 100)
        )
    );
    scene->addShape(
        new TransformShape(
            Translate(0.0f, 6.0f + 0.1f, 5.0f),
            new CityInside(2.2f)   // < bán kính rail
        )
    );

    //tàu mới 1 
    scene->addShape(
        new TransformShape(
            Translate(0.0f, 0.15f, 8.0f),
            new ToyTrain1(0.2f)
        )
    );


    // ===== CALLBACK =====
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMotion);

    glutSetCursor(GLUT_CURSOR_NONE);

    std::cout << "Entering GLUT main loop..." << std::endl;
    glutMainLoop();

    delete scene;
    return 0;
}