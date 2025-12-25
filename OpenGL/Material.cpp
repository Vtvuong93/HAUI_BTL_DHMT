// Material.cpp
#include "Material.h"
#include "Globals.h"

void Material::apply() const {
    // 1. Tính toán tích số màu sắc
    color4 ambient_product = current_light_ambient * ambient;
    color4 diffuse_product = current_light_diffuse * diffuse;
    color4 specular_product = current_light_specular * specular;

    // --- KHẮC PHỤC LỖI THỦY TINH (QUAN TRỌNG) ---
    // Ép độ trong suốt (Alpha/w) của kết quả bằng đúng độ trong suốt của vật liệu gốc.
    // Điều này đảm bảo dù đèn tắt hay bật, kính vẫn giữ độ trong suốt vốn có.
    ambient_product.w = ambient.w;
    diffuse_product.w = diffuse.w;
    specular_product.w = specular.w;
    // ---------------------------------------------

    // 2. Gửi xuống Shader
    glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
    glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
    glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
    glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, current_light_position);
    glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
    glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
}
