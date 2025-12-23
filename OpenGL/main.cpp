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
bool isLightOn = true; // Trạng thái đèn (Mặc định là Bật)

CeilingLamp* myLamp = nullptr; // Đối tượng đèn
TransformShape* myCoffeeTable = nullptr;
TransformShape* myGlassCabinet = nullptr;

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

    // --- ÁNH SÁNG BLINN-PHONG ---
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

// ================ DI CHUYỂN CAMERA ==================
void updateCameraMovement() {
    vec3 front = camera.getFront();
    vec3 right = normalize(cross(front, vec3(0.0f, 1.0f, 0.0f)));

    float walkSpeed = 0.05f;
    float runSpeed = 0.20f;
    bool isShiftHeld = (GetAsyncKeyState(VK_SHIFT) & 0x8000);

    // Tốc độ di chuyển
    float currentSpeed = isShiftHeld ? runSpeed : walkSpeed;

	// Phím A, S, D, W
    if (GetAsyncKeyState('W') & 0x8000)        camera.position += currentSpeed * front;
    if (GetAsyncKeyState('S') & 0x8000)        camera.position -= currentSpeed * front;
    if (GetAsyncKeyState('A') & 0x8000)        camera.position -= currentSpeed * right * 0.8f;
    if (GetAsyncKeyState('D') & 0x8000)        camera.position += currentSpeed * right * 0.8f;

    // Phím Space (Lên) - VK_SPACE là mã phím Space
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)   camera.position.y += currentSpeed * 0.5f;

    // Phím C (Xuống)
    if (GetAsyncKeyState('C') & 0x8000)        camera.position.y -= currentSpeed *0.5f;
}

// ================== DISPLAY ==================
void display() {
	updateCameraMovement(); // Cập nhật di chuyển

    // --- Xử lý logic Reset vị trí cửa sổ (Delay 1 frame) ---
    if (needToResetPos) {
        int screenW = glutGet(GLUT_SCREEN_WIDTH);
        int screenH = glutGet(GLUT_SCREEN_HEIGHT);
        glutPositionWindow((screenW - FIXED_W) / 2, (screenH - FIXED_H) / 2);
        needToResetPos = false; // Tắt cờ sau khi đã xử lý
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --- Gửi ánh sáng dựa trên trạng thái ---
    if (isLightOn) {
        color4 light_ambient(0.3f, 0.3f, 0.3f, 1.0f);
        color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
        color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);
        glUniform4fv(glGetUniformLocation(program, "LightAmbient"), 1, light_ambient);
        glUniform4fv(glGetUniformLocation(program, "LightDiffuse"), 1, light_diffuse);
        glUniform4fv(glGetUniformLocation(program, "LightSpecular"), 1, light_specular);
    }
    else {
        color4 light_ambient(0.05f, 0.05f, 0.05f, 1.0f); 
        color4 light_diffuse(0.1f, 0.1f, 0.1f, 1.0f);    
        color4 light_specular(0.0f, 0.0f, 0.0f, 1.0f);   
        glUniform4fv(glGetUniformLocation(program, "LightAmbient"), 1, light_ambient);
        glUniform4fv(glGetUniformLocation(program, "LightDiffuse"), 1, light_diffuse);
        glUniform4fv(glGetUniformLocation(program, "LightSpecular"), 1, light_specular);
    }

	// Camera & Projection
    mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
    float aspect = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

    mat4 projection = Perspective(45.0f, aspect, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

    // Vẽ vật thể 
    if (scene)  scene->draw(model);
    if (myLamp) {
        mat4 lampModel = model * Translate(0.0f, 5.0f, 0.0f);
        myLamp->draw(lampModel, isLightOn);
    }
    if (myCoffeeTable) myCoffeeTable->draw(model);
    if (myGlassCabinet) myGlassCabinet->draw(model);

    glutSwapBuffers();
}

// ================== TIMER (TỐI ƯU FPS) ==================
void timer(int value) {
    glutPostRedisplay();                
    glutTimerFunc(1000 / FPS, timer, 0); 
}

// ================== CALLBACKS ==================
void reshape(int width, int height) {   glViewport(0, 0, width, height);    }

void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27) exit(0); // ESC thoát
	if (key == 'l' || key == 'L') { isLightOn = !isLightOn; } // Bật/tắt đèn
	if (key == '9') { g_trainMove = !g_trainMove; } // Bật/tắt di chuyển tàu
    if (key == 'q') { if (!(rolledDoor >= 1.0f)) rolledDoor += 0.05f; }
    if (key == 'Q') { if (!(rolledDoor <= 0.0f)) rolledDoor -= 0.05f; }
    if (key == '/') { if (!(drag >= 0.5f)) drag += 0.05f; }
    if (key == '?') { if (!(drag <= 0.05f)) drag -= 0.05f;}
}

void keyboardUp(unsigned char key, int x, int y) { keys[key] = false; }

void mouseMotion(int x, int y) {
    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    if (x == cx && y == cy) return;

    float dx = (float)(x - cx) * camera.sensitivity;
    float dy = (float)(cy - y) * camera.sensitivity; // Đảo trục Y

    camera.yaw += dx;
    camera.pitch += dy;

    if (camera.pitch > 89.0f)  camera.pitch = 89.0f;
    if (camera.pitch < -89.0f) camera.pitch = -89.0f;

    camera.updateCameraVectors();
    glutWarpPointer(cx, cy);
}

void specialInput(int key, int x, int y) {
    if (key == GLUT_KEY_F11) {
        isFullScrn = !isFullScrn;
        if (isFullScrn) glutFullScreen();
        else { glutReshapeWindow(FIXED_W, FIXED_H); needToResetPos = true; }
    }
}


// ================== MAIN ==================
int main(int argc, char** argv) {
    std::cout << "Starting program..." << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // --- Căn giữa màn hình lúc khởi động ---
    int screenW = glutGet(GLUT_SCREEN_WIDTH);
    int screenH = glutGet(GLUT_SCREEN_HEIGHT);
    int posX = (screenW - FIXED_W) / 2;
    int posY = (screenH - FIXED_H) / 2;
    glutInitWindowSize(FIXED_W, FIXED_H);
    glutInitWindowPosition(posX, posY);
    glutCreateWindow("HAUI - BAI TAP LON - DO HOA MAY TINH - GROUP");

    // --- GLEW ---
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return EXIT_FAILURE;
    }

    shaderSetup();

    scene = new Scene();
    myLamp = new CeilingLamp();

    // ================== KHUNG CẢNH ==================
    scene->addShape(new House());
    scene->addShape(new TransformShape(Translate(15.0f, 0.0f, 0.0f), new HouseModern()));
    scene->addShape(new TransformShape(Translate(-15.0f, 0.0f, 0.0f), new HouseModern3F()));
    scene->addShape(new TransformShape(Translate(0.0f, -0.25f, 30.0f) *RotateY(90.0f),new RoadWithTrees()));

    // ================== TẦNG 1 ==================
    // --- Bộ Sofa --- 
    scene->addShape(new TransformShape(Translate(0.0f, 0.0f, 0.0f) * RotateY(180), new Sofa()));

    // --- Hệ bàn ---
    scene->addShape(new TransformShape(Translate(2.5f, 0.0f, 2.0f), new DisplayTable()));

    myCoffeeTable = new TransformShape(Translate(0.0f, 0.0f, 1.5f), new CoffeeTable());

    myGlassCabinet = new TransformShape(Translate(4.0f, 0.0f, -8.0f) * RotateY(-45), new GlassCabinet());

    // --- Hệ kệ gỗ ---
    scene->addShape(new TransformShape(Translate(-4.5f, 0.0f, 0.0f) * RotateY(90), new WoodShelf()));

    // --- Hệ Robot --- 
    scene->addShape(new TransformShape(Translate(3.0f, 0.85f, 2.0f) * RotateY(-45),new ToyRobot()));

    // === MÔ HÌNH TÀU HOẢ & RAY ===
    scene->addShape(new TransformShape(Translate(0.0f, 7.4f, 4.0f) * Scale(0.75f), new ToyTrain(0.2f)));
    scene->addShape(new TransformShape(Translate(0.0f, 7.35f, 4.0f) * Scale(0.75f), new CycleRail(3.0f, 100)));
    scene->addShape(new TransformShape(Translate(0.0f, 7.35f, 4.0f) * Scale(0.75f), new CityInside(2.2f)));

    scene->addShape(new TransformShape(Translate(0.0f, 0.15f, 8.0f), new ToyTrain1(0.2f)));
    scene->addShape(new TransformShape(Translate(0.0f, 0.15f, 6.0f), new StraightRail()));

    // === BIỂN HIỆU & POSTER ===
    scene->addShape(new TransformShape(Translate(0.0f, 4.5f, 10.2f), new BienHieu()));
    scene->addShape(new TransformShape(Translate(3.5f, 4.0f, 10.2f) * Scale(0.8f, 0.8f, 1.0f), new PosterQuangCao()));
    scene->addShape(new TransformShape(Translate(-3.5f, 4.0f, 10.2f) * Scale(0.8f, 0.8f, 1.0f), new PosterQuangCao()));

    // === HỆ THỐNG ĐÈN ===
    scene->addShape(new TransformShape(Translate(0.0f, 5.9f, 11.0f) * RotateX(180.0f), new DenChieuSang())); // Đèn soi biển hiệu

    // Đèn âm trần (dàn 1)
    for (float x = -4.0f; x <= 4.0f; x += 4.0f)
        scene->addShape(new TransformShape(Translate(x, 5.9f, 0.0f) * RotateX(180.0f), new DenChieuSang()));

    // Đèn âm trần (dàn 2 & 3)
    float zPositions[] = { -6.0f, 6.0f };
    for (float z : zPositions)
        for (float x = -4.0f; x <= 4.0f; x += 4.0f)
            scene->addShape(new TransformShape(Translate(x, 5.9f, z) * RotateX(180.0f), new DenChieuSang()));

    // ===== BÀN TRÒN TRÊN TẦNG 2 =====
    scene->addShape(new TransformShape(Translate(0.0f, 6.1f, 4.0f),new RoundTable()));

    // ===== CAMERA SETUP ===== 
    camera.position = vec3(0.0f, 2.0f, 0.0f);

    // ===== REGISTER CALLBACKS =====
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardDown); 
	glutKeyboardUpFunc(keyboardUp); 
    glutSpecialFunc(specialInput); 
	glutPassiveMotionFunc(mouseMotion); 
    glutTimerFunc(0, timer, 0); // set FPS

    glutSetCursor(GLUT_CURSOR_NONE);
    std::cout << "Entering GLUT main loop..." << std::endl;
    glutMainLoop();

    delete scene;
    return 0;
}