#include "Cone.h"
#include "Globals.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Cone::Cone() {
    material = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.8, 0.8, 0.8, 1.0),
        color4(1.0, 1.0, 1.0, 1.0),
        64.0f
    };
    generateGeometry();
    initGPUBuffers();
}

void Cone::draw(const mat4& modelMatrix) const {
    glBindVertexArray(vao);
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, CONE_VERTICES);
    glBindVertexArray(0);
}

void Cone::generateGeometry() {
    float radius = 0.5f;
    float height = 1.0f;
    float halfH = height / 2.0f;

    point4 apex(0.0f, halfH, 0.0f, 1.0f);
    point4 center(0.0f, -halfH, 0.0f, 1.0f);

    int index = 0;
    float angleStep = 2.0f * M_PI / CONE_SLICES;

    for (int i = 0; i < CONE_SLICES; i++) {
        float a0 = i * angleStep;
        float a1 = (i + 1) * angleStep;

        point4 p0(
            radius * cos(a0),
            -halfH,
            radius * sin(a0),
            1.0f
        );

        point4 p1(
            radius * cos(a1),
            -halfH,
            radius * sin(a1),
            1.0f
        );

        // ===== MẶT BÊN =====
        vec4 t1 = p1 - apex;
        vec4 t2 = p0 - apex;

        vec3 u(t1.x, t1.y, t1.z);
        vec3 v(t2.x, t2.y, t2.z);

        vec3 nSide = normalize(cross(u, v));

        points[index] = apex;
        normals[index] = nSide;
        colors[index] = color4(0.8, 0.8, 0.8, 1.0);
        index++;

        points[index] = p1;
        normals[index] = nSide;
        colors[index] = color4(0.8, 0.8, 0.8, 1.0);
        index++;

        points[index] = p0;
        normals[index] = nSide;
        colors[index] = color4(0.8, 0.8, 0.8, 1.0);
        index++;

        // ===== ĐÁY =====
        vec3 nBottom(0.0f, -1.0f, 0.0f);

        points[index] = center;
        normals[index] = nBottom;
        colors[index] = color4(0.6, 0.6, 0.6, 1.0);
        index++;

        points[index] = p0;
        normals[index] = nBottom;
        colors[index] = color4(0.6, 0.6, 0.6, 1.0);
        index++;

        points[index] = p1;
        normals[index] = nBottom;
        colors[index] = color4(0.6, 0.6, 0.6, 1.0);
        index++;
    }
}

void Cone::initGPUBuffers() {
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
        glVertexAttribPointer(
            loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)
        );
    }

    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    if (loc_vColor != -1) {
        glEnableVertexAttribArray(loc_vColor);
        glVertexAttribPointer(
            loc_vColor, 4, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(sizeof(point4) * CONE_VERTICES)
        );
    }

    GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
    if (loc_vNormal != -1) {
        glEnableVertexAttribArray(loc_vNormal);
        glVertexAttribPointer(
            loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(
                sizeof(point4) * CONE_VERTICES +
                sizeof(color4) * CONE_VERTICES
            )
        );
    }

    glBindVertexArray(0);
}
