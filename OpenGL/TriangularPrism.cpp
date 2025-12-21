#include "TriangularPrism.h"
#include "Globals.h"

TriangularPrism::TriangularPrism() {
    material = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.8, 0.8, 0.8, 1.0),
        color4(1.0, 1.0, 1.0, 1.0),
        64.0f
    };
    generateGeometry();
    initGPUBuffers();
}

void TriangularPrism::draw(const mat4& modelMatrix) const {
    glBindVertexArray(vao);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 54);
    glBindVertexArray(0);
}

void TriangularPrism::generateGeometry() {
    // ===== 6 đỉnh cơ bản =====
    point4 vertices[6] = {
        // Tam giác trước (z = 0.5)
        point4(-0.5, -0.5,  0.5, 1.0), // 0
        point4(0.5, -0.5,  0.5, 1.0), // 1
        point4(0.0,  0.5,  0.5, 1.0), // 2

        // Tam giác sau (z = -0.5)
        point4(-0.5, -0.5, -0.5, 1.0), // 3
        point4(0.5, -0.5, -0.5, 1.0), // 4
        point4(0.0,  0.5, -0.5, 1.0)  // 5
    };

    color4 faceColor(0.7, 0.7, 0.7, 1.0);
    int index = 0;

    auto triangle = [&](int a, int b, int c) {
        vec4 u = vertices[b] - vertices[a];
        vec4 v = vertices[c] - vertices[a];
        vec3 normal = normalize(cross(u, v));

        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[a]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[b]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[c]; index++;
        };

    auto quad = [&](int a, int b, int c, int d) {
        vec4 u = vertices[b] - vertices[a];
        vec4 v = vertices[c] - vertices[b];
        vec3 normal = normalize(cross(u, v));

        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[a]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[b]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[c]; index++;

        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[a]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[c]; index++;
        normals[index] = normal; colors[index] = faceColor; points[index] = vertices[d]; index++;
        };

    // ===== 2 mặt tam giác =====
    triangle(0, 1, 2); // trước
    triangle(5, 4, 3); // sau (đảo chiều để normal ra ngoài)

    // ===== 3 mặt chữ nhật =====
    quad(0, 1, 4, 3); // đáy
    quad(1, 2, 5, 4); // phải
    quad(2, 0, 3, 5); // trái
}

void TriangularPrism::initGPUBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(colors) + sizeof(normals),
        NULL,
        GL_STATIC_DRAW
    );

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(colors),
        sizeof(normals),
        normals
    );

    GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
    if (loc_vPosition != -1) {
        glEnableVertexAttribArray(loc_vPosition);
        glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    }

    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    if (loc_vColor != -1) {
        glEnableVertexAttribArray(loc_vColor);
        glVertexAttribPointer(
            loc_vColor, 4, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(sizeof(point4) * 54)
        );
    }

    GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
    if (loc_vNormal != -1) {
        glEnableVertexAttribArray(loc_vNormal);
        glVertexAttribPointer(
            loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(sizeof(point4) * 54 + sizeof(color4) * 54)
        );
    }

    glBindVertexArray(0);
}
