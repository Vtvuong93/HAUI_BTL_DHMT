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
bool isLightOn = true; 
float glassCabinetOpen = 0.0f; 
float mainDoorOpen = 0.0f;         

std::vector<GlassCabinet*> cabinetList;     
std::vector<TransformShape*> cabinetDrawList;

CeilingLamp* myLamp = nullptr; // Đối tượng đèn
TransformShape* myGlassCoffeeTable = nullptr;
SlidingGlassDoor* myMainDoor = nullptr; // Con trỏ quản lý cửa chính


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

    float walkSpeed = 0.04f;
    float runSpeed = 0.2f;
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
        mat4 lampPos3 = model * Translate(4.5f, 4.0f, 0.0f);
		mat4 lampPos2 = model * Translate(4.5f, 4.0f, 4.0f);
		mat4 lampPos1 = model * Translate(4.5f, 4.0f, 8.0f);
		mat4 lampPos4 = model * Translate(-4.5f, 10.5f, 3.0f) * RotateY(180);
		mat4 lampPos5 = model * Translate(-4.5f, 10.5f, -3.0f) * RotateY(180);
        myLamp->draw(lampPos1, isLightOn);
		myLamp->draw(lampPos2, isLightOn);
		myLamp->draw(lampPos3, isLightOn);
		myLamp->draw(lampPos4, isLightOn);
		myLamp->draw(lampPos5, isLightOn);
    }
    if (myGlassCoffeeTable) myGlassCoffeeTable->draw(model);
	// Vẽ tủ kính
    for (auto cab : cabinetList) { cab->openAngle = glassCabinetOpen; }
    for (auto cabDraw : cabinetDrawList) { cabDraw->draw(model); }

    if (myMainDoor) {
        myMainDoor->openFactor = mainDoorOpen;
        mat4 doorPos1 = model * Translate(0.0f, 0.0f, 10.0f);
		mat4 doorPos2 = model * Translate(0.0f, 6.0f, 10.0f);
        myMainDoor->draw(doorPos1);
		myMainDoor->draw(doorPos2);
    }

	glutSwapBuffers();
}

// ================== TIMER (TỐI ƯU FPS) ==================
void timer(int value) {
    glutPostRedisplay();                
    glutTimerFunc(1000 / FPS, timer, 0); 
}

// ================== CALLBACKS ==================
void reshape(int width, int height) {   glViewport(0, 0, width, height);    }

bool isMouseCaptured = true;
void captureMouse() {
    isMouseCaptured = true;
    glutSetCursor(GLUT_CURSOR_NONE);

    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    glutWarpPointer(cx, cy);
}

void releaseMouse() {
    isMouseCaptured = false;
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}
void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == 27) exit(0); // ESC thoát
	if (key == 'l' || key == 'L') { isLightOn = !isLightOn; } // Bật/tắt đèn

	if (key == '1') { 
        g_trainMove = !g_trainMove;
        if (g_trainMove) {
			g_TrainMove1 = false;
			g_TrainMove2 = false;
        }
    } 
    if (key == '2') { 
        g_TrainMove1 = !g_TrainMove1; 
        if (g_TrainMove1) { 
            g_TrainMove2 = false;
		    g_trainMove = false;
        }

    }
    if (key == '3') { 
        g_TrainMove2 = !g_TrainMove2; 
        if (g_TrainMove2) {
			g_TrainMove1 = false;
			g_trainMove = false;
        }
    }

	// Mở đóng cửa cuốn
    if (key == 'Q') { if (!(rolledDoor >= 1.0f)) rolledDoor += 0.05f; }
    if (key == 'q') { if (!(rolledDoor <= 0.0f)) rolledDoor -= 0.05f; }
    // Kéo trượt ngăn kéo
    if (key == '/') { if (!(drag >= 0.5f)) drag += 0.05f; }
    if (key == '?') { if (!(drag <= 0.05f)) drag -= 0.05f;}
    // Xoay chìa khoá
    if (key == '=') { if (!(twistKey >= 90.0f)) twistKey += 5.0f; }
    if (key == '+') { if (!(twistKey <= 0.0f)) twistKey -= 5.0f; }
	// Mở kính tủ
    if (key == '-') { if (!(glassCabinetOpen >= 0.65f)) glassCabinetOpen += 0.05f; }
	if (key == '_') { if (!(glassCabinetOpen <= 0.05f)) glassCabinetOpen -= 0.05f; }
	// Mở cửa chính
    if (key == 'o') { if (mainDoorOpen < 1.0f) mainDoorOpen += 0.05f; }
    if (key == 'O') { if (mainDoorOpen > 0.0f) mainDoorOpen -= 0.05f; }

    if (key == 'm' || key == 'M') {
        if (isMouseCaptured)
            releaseMouse();
        else
            captureMouse();
    }
}

void keyboardUp(unsigned char key, int x, int y) { keys[key] = false; }






//void mouseMotion(int x, int y) {
//    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
//    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
//    if (x == cx && y == cy) return;
//
//    float dx = (float)(x - cx) * camera.sensitivity;
//    float dy = (float)(cy - y) * camera.sensitivity; // Đảo trục Y
//
//    camera.yaw += dx;
//    camera.pitch += dy;
//
//	if (camera.pitch > 89.0f)  camera.pitch = 89.0f;
//	if (camera.pitch < -89.0f) camera.pitch = -89.0f;
//
//    camera.updateCameraVectors();
//    glutWarpPointer(cx, cy);
//}

void mouseMotion(int x, int y) {
    if (!isMouseCaptured) return;

    int cx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int cy = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    if (x == cx && y == cy) return;

    float dx = (float)(x - cx) * camera.sensitivity;
    float dy = (float)(cy - y) * camera.sensitivity;

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

    // ================== KHUNG CẢNH & NGOẠI CẢNH ==================
    scene->addShape(new House());
    scene->addShape(new TransformShape(Translate(15.0f, 0.0f, 0.0f), new HouseModern()));
    scene->addShape(new TransformShape(Translate(-15.0f, 0.0f, 0.0f), new HouseModern3F()));
    scene->addShape(new TransformShape(Translate(0.0f, -0.25f, 30.0f) * RotateY(90.0f), new RoadWithTrees()));

    myLamp = new CeilingLamp();
	myMainDoor = new SlidingGlassDoor();

    // ================== TẦNG 1 (Ground Floor - Y ~ 0.0f -> 2.0f) ==================

    // --- Nội thất chính (Sofa, Bàn, Kệ) ---
    scene->addShape(new TransformShape(Translate(0.0f, 0.15f, 0.0f) * RotateY(90) * Scale(2.5f, 1.5f, 3.0f), new DisplayTable()));
    scene->addShape(new TransformShape(Translate(0.5f, 1.58f, 1.8f) *  RotateY(90), new ToyTrain1(0.2f)));      // Tàu mới 1
    scene->addShape(new TransformShape(Translate(-0.5f, 1.58f, 1.5f) * RotateY(90), new ToyLocomotive2(0.2f))); // Đầu tàu 2
    scene->addShape(new TransformShape(Translate(-0.5f, 1.58f, -1.0f) * RotateY(90), new ToyLocomotive3(0.2f))); // Đầu tàu 3
    scene->addShape(new TransformShape(Translate(0.5f, 1.58f, -1.5f) * RotateY(90), new ToyLocomotive4(0.2f))); // Đầu tàu 4

    scene->addShape(new TransformShape(Translate(0.5f, 1.45f, 2.3f) *Scale(1, 1, 1.3) * RotateY(90), new StraightRail()));       // Ray thẳng
    scene->addShape(new TransformShape(Translate(-0.5f, 1.45f, 2.3f)  * RotateY(90), new StraightRail()));       // Ray thẳng
    scene->addShape(new TransformShape(Translate(0.5f, 1.45f, -0.3f) * RotateY(90), new StraightRail()));       // Ray thẳng
    scene->addShape(new TransformShape(Translate(-0.5f, 1.45f, -0.3f)  * RotateY(90), new StraightRail()));       // Ray thẳng
    
    for (int i = 0; i < 3; i++) {
        float baseZ = 8.0f - i * 4.0f;
        mat4 cabinetMatrix = Translate(4.5f, 0.15f, baseZ) * RotateY(-90);

        // 2. Đặt tàu vào từng tầng 
        // --- Tầng 1 (Đáy tủ) ---
        scene->addShape(new TransformShape(
            cabinetMatrix * Translate(-0.2f, 0.1f, 0.0f) * Scale(1.0f),
            new ToyLocomotive2(0.2f)
        ));

        // --- Tầng 2 (Đợt kính giữa) ---
        scene->addShape(new TransformShape(
            cabinetMatrix * Translate(-0.2f, 0.8f, 0.0f) * Scale(1.2f),
            new ToyLocomotive3(0.2f)
        ));

        // --- Tầng 3 (Đợt kính cao) ---
        scene->addShape(new TransformShape(
            cabinetMatrix * Translate(-0.2f, 1.65f, 0.0f) * Scale(1.2f),
            new ToyLocomotive4(0.2f)
        ));
    }

    // ===== Tủ kính 1 =====
    GlassCabinet* cab1 = new GlassCabinet();
    TransformShape* cab1Pos = new TransformShape( Translate(4.4f, 0.1f, 8.0f) * RotateY(-90), cab1);
    cabinetList.push_back(cab1);   
    cabinetDrawList.push_back(cab1Pos); 

    // ===== Tủ kính 2 =====
    GlassCabinet* cab2 = new GlassCabinet();
    TransformShape* cab2Pos = new TransformShape( Translate(4.4f, 0.1f, 4.0f) * RotateY(-90) , cab2);
    cabinetList.push_back(cab2);
    cabinetDrawList.push_back(cab2Pos);

    // ===== Tủ kính 3 =====
    GlassCabinet* cab3 = new GlassCabinet();
    TransformShape* cab3Pos = new TransformShape(Translate(4.4f, 0.1f, 0.0f) * RotateY(-90), cab3);
    cabinetList.push_back(cab3);
    cabinetDrawList.push_back(cab3Pos);

     // --- 3. KHU KỆ GỖ (WALL OF TOYS) - TƯỜNG TRÁI ---
    // Mỗi kệ cách nhau 3.2m (vì kệ rộng 3m)
    float shelfZ[] = { -6.5f, -2.0f, 2.5f };

    for (int i = 0; i < 3; i++) {
        // Vẽ kệ
        scene->addShape(new TransformShape(Translate(-4.5f, 0.05f, shelfZ[i]) * RotateY(90), new WoodShelf()));
        // --- Tự động xếp đồ chơi lên kệ ---
        for (int floor = 0; floor <= 3; floor++) {
            float yToy = 0.15f + floor *1.18f;
            // Tầng lẻ: Xếp Robot
            if (floor % 2 == 0) {
                scene->addShape(new TransformShape(Translate(-4.4f, yToy, shelfZ[i] - 1.0f) * RotateY(90), new ToyRobot()));
                scene->addShape(new TransformShape(Translate(-4.4f, yToy , shelfZ[i] + 1.0f) * RotateY(90), new ToyRobot()));
            }
            // Tầng chẵn: Xếp Đầu tàu hỏa
            else {
                scene->addShape(new TransformShape(Translate(-4.4f, yToy, shelfZ[i] + 1.0f) * RotateY(90) * Scale(1.2f), new ToyTrain1(0.2f)));
            }
        }
    }


    // ================== TẦNG 2 (Upper Floor - Y ~ 4.0f -> 7.5f) ==================
    // --- Bàn tròn trung tâm tầng 2 (Y = 6.1f) ---
    scene->addShape(new TransformShape(Translate(0.0f, 6.1f, 4.5f), new RoundTable()));
    scene->addShape(new TransformShape(Translate(4.15f, 6.1f, -2.5f) * RotateY(-90) * Scale(2.5f, 1.5f, 2.0f), new Sofa()));
    scene->addShape(new TransformShape(Translate(1.0f, 6.1f, -6.0f) * Scale(1.5f, 1.5f, 2.0f), new Sofa()));
    myGlassCoffeeTable = new TransformShape(Translate(1.0f, 6.1f, -2.5f) * RotateY(-90) * Scale(2.5f, 1.5f, 2.0f), new CoffeeTable());
     
    // --- Set Tàu hỏa trên cao (Set 1 - Y ~ 7.4f) ---
    scene->addShape(new TransformShape(Translate(0.0f, 7.4f, 4.5f) * Scale(0.75f), new ToyTrain(0.2f)));
    scene->addShape(new TransformShape(Translate(0.0f, 7.35f, 4.5f) * Scale(0.75f), new CycleRail(3.0f, 100)));
    scene->addShape(new TransformShape(Translate(0.0f, 7.35f, 4.5f) * Scale(0.75f), new CityInside(2.2f)));

    // --- Biển hiệu & Trang trí tường (Y ~ 4.0f -> 6.75f) ---
    // ben ngoai
    scene->addShape(new TransformShape(Translate(0.0f, 11.25f, 10.2f) * Scale(2.4f, 1.0f, 1.0f), new BienHieu())); // to
    scene->addShape(new TransformShape(Translate(0.0f, 5.2f, 11.0f) * Scale(1.05f, 0.85f , 1.0f), new BienHieu()));
    scene->addShape(new TransformShape(Translate(3.5f, 4.0f, 10.2f) * Scale(0.8f, 0.8f, 1.0f), new PosterQuangCao()));
    scene->addShape(new TransformShape(Translate(-3.5f, 4.0f, 10.2f) * Scale(0.8f, 0.8f, 1.0f), new PosterQuangCao()));

    scene->addShape(new TransformShape(Translate(-1.5f, 2.5f, -9.8f) * Scale(1.5), new PosterQuangCao()));
    scene->addShape(new TransformShape(Translate(-5.0f, 9.0f, 3.0f) * RotateY(90)* Scale( 1.2f), new PosterQuangCao()));
    scene->addShape(new TransformShape(Translate(-5.0f, 9.0f, -3.0f) * RotateY(90) * Scale( 1.2f), new PosterQuangCao()));
    


    // ================== HỆ THỐNG ĐÈN (Trần nhà & Soi tranh) ==================
    // --- Đèn soi biển hiệu (Y = 5.9f) ---
    scene->addShape(new TransformShape(Translate(0.0f, 5.9f, 12.0f) * RotateX(180.0f), new DenChieuSang()));

    // --- Đèn âm trần (Chạy vòng lặp tạo lưới đèn) ---
    // Dàn 1 (Z = 0)
    for (float x = -4.0f; x <= 4.0f; x += 4.0f)
        scene->addShape(new TransformShape(Translate(x, 5.9f, 0.0f) * RotateX(180.0f), new DenChieuSang()));

    // Dàn 2 & 3 (Z = -6 và Z = 6)
    float zPositions[] = { -6.0f, 6.0f };
    for (float z : zPositions)
        for (float x = -4.0f; x <= 4.0f; x += 4.0f)
            scene->addShape(new TransformShape(Translate(x, 5.9f, z) * RotateX(180.0f), new DenChieuSang()));

    // --- Đèn âm trần (Chạy vòng lặp tạo lưới đèn) ---
    // Dàn 1 (Z = 0)
    for (float x = -4.0f; x <= 4.0f; x += 4.0f)
        scene->addShape(new TransformShape(Translate(x, 11.9f, 0.0f) * RotateX(180.0f), new DenChieuSang()));

    // Dàn 2 & 3 (Z = -6 và Z = 6
    for (float z : zPositions)
        for (float x = -4.0f; x <= 4.0f; x += 4.0f)
            scene->addShape(new TransformShape(Translate(x, 11.9f, z) * RotateX(180.0f), new DenChieuSang()));

    // ===== CAMERA SETUP ===== 
    camera.position = vec3(0.0f, 2.0f, 30.0f);

    // ===== REGISTER CALLBACKS =====
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardDown); 
	glutKeyboardUpFunc(keyboardUp); 
    glutSpecialFunc(specialInput); 
	glutPassiveMotionFunc(mouseMotion); 
    glutTimerFunc(0, timer, 0); // set FPS
    captureMouse();
	//glutSetCursor(GLUT_CURSOR_NONE);
	std::cout << "Entering GLUT main loop..." << std::endl;
	glutMainLoop();

	delete scene;
	return 0;
}