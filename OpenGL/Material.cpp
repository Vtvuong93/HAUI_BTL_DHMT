// Material.cpp
#include "Material.h"
#include "Globals.h"

void Material::apply() const {
    glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient);
    glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse);
    glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular);
    glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
}
