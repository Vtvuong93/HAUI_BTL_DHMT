#include "Cylinder.h"
#include "Globals.h"
#include <cmath>

Cylinder::Cylinder() {
    material = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.8, 0.8, 0.8, 1.0),
        color4(1.0, 1.0, 1.0, 1.0),
        64.0f
    };
    generateGeometry();
    initGPUBuffers();
}

void Cylinder::draw(const mat4& modelMatrix) const {
    glBindVertexArray(vao);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, CYLINDER_VERTICES);
    glBindVertexArray(0);
}

void Cylinder::generateGeometry() {
    float radius = 0.5f;
    float height = 1.0f;
    float halfH = height / 2.0f;

    int index = 0;
    float angleStep = 2.0f * M_PI / CYLINDER_SLICES;

    for (int i = 0; i < CYLINDER_SLICES; i++) {
        float a0 = i * angleStep;
        float a1 = (i + 1) * angleStep;

        float x0 = radius * cos(a0);
        float z0 = radius * sin(a0);
        float x1 = radius * cos(a1);
        float z1 = radius * sin(a1);

        // ===== MẶT BÊN =====
        vec3 normal0 = normalize(vec3(x0, 0, z0));
        vec3 normal1 = normalize(vec3(x1, 0, z1));

        // Triangle 1
        points[index] = point4(x0, -halfH, z0, 1.0); normals[index] = normal0; colors[index++] = color4(0.7, 0.7, 0.7, 1);
        points[index] = point4(x1, -halfH, z1, 1.0); normals[index] = normal1; colors[index++] = color4(0.7, 0.7, 0.7, 1);
        points[index] = point4(x1, halfH, z1, 1.0); normals[index] = normal1; colors[index++] = color4(0.7, 0.7, 0.7, 1);

        // Triangle 2
        points[index] = point4(x0, -halfH, z0, 1.0); normals[index] = normal0; colors[index++] = color4(0.7, 0.7, 0.7, 1);
        points[index] = point4(x1, halfH, z1, 1.0); normals[index] = normal1; colors[index++] = color4(0.7, 0.7, 0.7, 1);
        points[index] = point4(x0, halfH, z0, 1.0); normals[index] = normal0; colors[index++] = color4(0.7, 0.7, 0.7, 1);

        // ===== NẮP TRÊN =====
        vec3 topNormal(0, 1, 0);
        points[index] = point4(0, halfH, 0, 1.0); normals[index] = topNormal; colors[index++] = color4(0.8, 0.8, 0.8, 1);
        points[index] = point4(x1, halfH, z1, 1.0); normals[index] = topNormal; colors[index++] = color4(0.8, 0.8, 0.8, 1);
        points[index] = point4(x0, halfH, z0, 1.0); normals[index] = topNormal; colors[index++] = color4(0.8, 0.8, 0.8, 1);

        // ===== NẮP DƯỚI =====
        vec3 bottomNormal(0, -1, 0);
        points[index] = point4(0, -halfH, 0, 1.0); normals[index] = bottomNormal; colors[index++] = color4(0.6, 0.6, 0.6, 1);
        points[index] = point4(x0, -halfH, z0, 1.0); normals[index] = bottomNormal; colors[index++] = color4(0.6, 0.6, 0.6, 1);
        points[index] = point4(x1, -halfH, z1, 1.0); normals[index] = bottomNormal; colors[index++] = color4(0.6, 0.6, 0.6, 1);
    }
}

void Cylinder::initGPUBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(colors) + sizeof(normals),
        NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);

    GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc_vPosition);
    glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc_vColor);
    glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(sizeof(point4) * CYLINDER_VERTICES));

    GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(loc_vNormal);
    glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(sizeof(point4) * CYLINDER_VERTICES + sizeof(color4) * CYLINDER_VERTICES));

    glBindVertexArray(0);
}
