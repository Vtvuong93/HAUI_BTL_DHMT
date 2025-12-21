// ================== THƯ VIỆN TỔNG ==================
#include "Globals.h"

// ================== GLOBAL VARIABLES ==================
mat4 model = mat4(1.0f);   // Ma trận model gốc
Scene* scene = nullptr;
Camera camera;

// Cấu hình cửa sổ cố định
const int FIXED_W = 1440;
const int FIXED_H = 900;
const int FPS = 60;

// Trạng thái
bool keys[256]; 
bool isFullScrn = false;
bool needToResetPos = false;

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

// ================ DI CHUYỂN ==================
void updateCameraMovement() {
    vec3 front = camera.getFront();
    vec3 right = normalize(cross(front, vec3(0.0f, 1.0f, 0.0f)));

    // ===== LOGIC TỐC ĐỘ (SỬA LẠI) =====
    float walkSpeed = 0.05f;
    float runSpeed = 0.20f;

    // Kiểm tra trực tiếp phím Shift có đang được giữ hay không
    // 0x8000 là bit kiểm tra trạng thái "Đang nhấn"
    bool isShiftHeld = (GetAsyncKeyState(VK_SHIFT) & 0x8000);

    // Tốc độ di chuyển
    float currentSpeed = isShiftHeld ? runSpeed : walkSpeed;

    // Phím W
    if (GetAsyncKeyState('W') & 0x8000)
        camera.position += currentSpeed * front;

    // Phím S
    if (GetAsyncKeyState('S') & 0x8000)
        camera.position -= currentSpeed * front;

    // Phím A
    if (GetAsyncKeyState('A') & 0x8000)
        camera.position -= currentSpeed * right * 0.8f;

    // Phím D
    if (GetAsyncKeyState('D') & 0x8000)
        camera.position += currentSpeed * right * 0.8f;

    // Phím Space (Lên) - VK_SPACE là mã phím Space
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        camera.position.y += currentSpeed * 0.5f;

    // Phím C (Xuống)
    if (GetAsyncKeyState('C') & 0x8000)
        camera.position.y -= currentSpeed *0.5f;
}

// ================== DISPLAY ==================
void display() {
    // Cập nhật di chuyển
	updateCameraMovement();

    // Xử lý logic Reset vị trí cửa sổ (Delay 1 frame)
    if (needToResetPos) {
        int screenW = glutGet(GLUT_SCREEN_WIDTH);
        int screenH = glutGet(GLUT_SCREEN_HEIGHT);
        glutPositionWindow((screenW - FIXED_W) / 2, (screenH - FIXED_H) / 2);
        needToResetPos = false; // Tắt cờ sau khi đã xử lý
    }

	// 2. Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera View
    mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);

    // Projection (FIX: theo aspect ratio)
    float aspect = (float)glutGet(GLUT_WINDOW_WIDTH) /
        (float)glutGet(GLUT_WINDOW_HEIGHT);

    mat4 projection = Perspective(45.0f, aspect, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	// Draw Scene
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
    if (scene)
        scene->draw(model);

    glutSwapBuffers();
}

// ================== TIMER (TỐI ƯU FPS) ==================
void timer(int value) {
    glutPostRedisplay();                 // Yêu cầu vẽ lại khung hình
    glutTimerFunc(1000 / FPS, timer, 0); 
}

// ================== RESHAPE ==================
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

// ================== KEYBOARD ==================
// Hàm khi nhấn phím
void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27) exit(0); // ESC thoát
}

// Hàm khi thả phím 
void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

// ================== MOUSE ==================
void mouseMotion(int x, int y) {
    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    // Nếu vị trí chuột chính là tâm (do WarpPointer gây ra), bỏ qua không tính toán
    if (x == cx && y == cy) return;

    float dx = (float)(x - cx); // Tính toán so với tâm màn hình luôn
    float dy = (float)(cy - y); // Đảo trục Y

    dx *= camera.sensitivity;
    dy *= camera.sensitivity;

    camera.yaw += dx;
    camera.pitch += dy;

    if (camera.pitch > 89.0f)  camera.pitch = 89.0f;
    if (camera.pitch < -89.0f) camera.pitch = -89.0f;

    camera.updateCameraVectors();

    // Đưa chuột về lại tâm
    glutWarpPointer(cx, cy);
}

// === HÀM XỬ LÝ PHÍM CHỨC NĂNG (F11) ===
void specialInput(int key, int x, int y) {
    if (key == GLUT_KEY_F11) {
        isFullScrn = !isFullScrn;

        if (isFullScrn) {
            glutFullScreen();
        }
        else {
            //Thay đổi kích thước ngay lập tức
            glutReshapeWindow(FIXED_W, FIXED_H);
			//Đặt cờ để reset vị trí trong hàm display
            needToResetPos = true;
        }
    }
}


// ================== MAIN ==================
int main(int argc, char** argv) {
    std::cout << "Starting program..." << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // --- CĂN GIỮA MÀN HÌNH LÚC KHỞI ĐỘNG ---
    int screenW = glutGet(GLUT_SCREEN_WIDTH);
    int screenH = glutGet(GLUT_SCREEN_HEIGHT);
    int posX = (screenW - FIXED_W) / 2;
    int posY = (screenH - FIXED_H) / 2;

    glutInitWindowSize(FIXED_W, FIXED_H);
    glutInitWindowPosition(posX, posY);

    glutCreateWindow("HAUI - BAI TAP LON - DO HOA MAY TINH - GROUP");

    // GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return EXIT_FAILURE;
    }

    shaderSetup();

    // ===== SCENE =====
    scene = new Scene();

    // ================== KHUNG CẢNH ==================
    scene->addShape(new House());
    scene->addShape(new TransformShape(Translate(15.0f, 0.0f, 0.0f), new HouseModern()));
    scene->addShape(new TransformShape(Translate(-15.0f, 0.0f, 0.0f), new HouseModern3F()));
    scene->addShape(new TransformShape(Translate(0.0f, -0.25f, 30.0f) *RotateY(90.0f),new RoadWithTrees()));

    // ================== TẦNG 1 – PHÒNG KHÁCH ==================


    // ===== CAMERA SETUP ===== 
    camera.position = vec3(0.0f, 2.0f, 30.0f); // X (giữa), Y (cao tầm mắt người)

    // ===== REGISTER CALLBACKS =====
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboardDown); // Nhấn phím
	glutKeyboardUpFunc(keyboardUp); // Thả phím
    glutSpecialFunc(specialInput); //F1
	glutPassiveMotionFunc(mouseMotion); // Chuột di chuyển

    glutTimerFunc(0, timer, 0); // set FPS

    glutSetCursor(GLUT_CURSOR_NONE);
    std::cout << "Entering GLUT main loop..." << std::endl;
    glutMainLoop();

    delete scene;
    return 0;
}