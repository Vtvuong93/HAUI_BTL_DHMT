#include "Cube.h"
#include "Globals.h"  

Cube::Cube() {
    material = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.8, 0.8, 0.8, 1.0),
        color4(1.0, 1.0, 1.0, 1.0),
        64.0f
    };
    generateGeometry();
    initGPUBuffers();
}

void Cube::draw(const mat4& modelMatrix) const {
    glBindVertexArray(vao);

    // KHÔNG setup attribute ở đây nữa đã làm ở initGPUBuffers

    glUniformMatrix4fv(model_loc, 1, GL_TRUE, modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36); 
}

void Cube::generateGeometry() {
    point4 vertices[8] = {
        point4(-0.5, -0.5, 0.5, 1.0),
        point4(-0.5, 0.5, 0.5, 1.0),
        point4(0.5, 0.5, 0.5, 1.0),
        point4(0.5, -0.5, 0.5, 1.0),
        point4(-0.5, -0.5, -0.5, 1.0),
        point4(-0.5, 0.5, -0.5, 1.0),
        point4(0.5, 0.5, -0.5, 1.0),
        point4(0.5, -0.5, -0.5, 1.0)
    };
    color4 vertex_colors[8] = {
        color4(0.0, 0.0, 0.0, 1.0), // black
        color4(1.0, 0.0, 0.0, 1.0), // red
        color4(1.0, 1.0, 0.0, 1.0), // yellow
        color4(0.0, 1.0, 0.0, 1.0), // green
        color4(0.0, 0.0, 1.0, 1.0), // blue
        color4(1.0, 0.0, 1.0, 1.0), // magenta
        color4(1.0, 0.5, 0.0, 1.0), // orange
        color4(0.0, 1.0, 1.0, 1.0) // cyan
    };
    int index = 0;
    auto quad = [&](int a, int b, int c, int d) {
        vec4 u = vertices[b] - vertices[a];
        vec4 v = vertices[c] - vertices[b];
        vec3 normal = normalize(cross(u, v));
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[a]; index++;
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[b]; index++;
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[c]; index++;
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[a]; index++;
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[c]; index++;
        normals[index] = normal; colors[index] = vertex_colors[a]; points[index] = vertices[d]; index++;
        };
    quad(1, 0, 3, 2);
    quad(2, 3, 7, 6);
    quad(3, 0, 4, 7);
    quad(6, 5, 1, 2);
    quad(4, 5, 6, 7);
    quad(5, 4, 0, 1);
}

void Cube::initGPUBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);

    // Setup attribute NGAY SAU KHI BIND VAO → chỉ một lần
    GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
    if (loc_vPosition != -1) {
        glEnableVertexAttribArray(loc_vPosition);
        glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    }

    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    if (loc_vColor != -1) {
        glEnableVertexAttribArray(loc_vColor);
        glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * 36));
    }

    GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
    if (loc_vNormal != -1) {
        glEnableVertexAttribArray(loc_vNormal);
        glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * 36 + sizeof(color4) * 36));
    }

    glBindVertexArray(0);  // Unbind an toàn
}