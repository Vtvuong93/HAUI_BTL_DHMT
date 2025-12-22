#pragma once
#include "Material.h"

namespace Materials {

    // ================== WOOD ==================
    const Material Wood = {
        color4(0.2, 0.1, 0.05, 1.0),   // ambient
        color4(0.6, 0.3, 0.1, 1.0),    // diffuse
        color4(0.3, 0.3, 0.3, 1.0),    // specular
        32.0f
    };

    // ================== METAL ==================
    const Material Metal = {
        color4(0.1, 0.1, 0.1, 1.0),
        color4(0.4, 0.4, 0.4, 1.0),
        color4(0.9, 0.9, 0.9, 1.0),
        128.0f
    };

    // ================== PLASTIC ==================
    const Material Plastic = {
        color4(0.1, 0.1, 0.1, 1.0),
        color4(0.2, 0.6, 0.9, 1.0),
        color4(0.5, 0.5, 0.5, 1.0),
        64.0f
    };

    // ================== WALL (SƠN TƯỜNG) ==================
    const Material WallPaint = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.85, 0.85, 0.85, 1.0),
        color4(0.05, 0.05, 0.05, 1.0),
        8.0f
    };

    // ================== CEILING (TRẦN NHÀ) ==================
    const Material Ceiling = {
        color4(0.25, 0.25, 0.25, 1.0),
        color4(0.95, 0.95, 0.95, 1.0),
        color4(0.02, 0.02, 0.02, 1.0),
        4.0f
    };

    // ================== FLOOR / TILE ==================
    const Material FloorTile = {
        color4(0.15, 0.15, 0.15, 1.0),
        color4(0.7, 0.7, 0.7, 1.0),
        color4(0.2, 0.2, 0.2, 1.0),
        24.0f
    };

    // ================== CONCRETE ==================
    const Material Concrete = {
        color4(0.2, 0.2, 0.2, 1.0),
        color4(0.5, 0.5, 0.5, 1.0),
        color4(0.1, 0.1, 0.1, 1.0),
        16.0f
    };

    
    const Material ConcreteSage = {
    color4(0.20, 0.24, 0.22, 1.0),
    color4(0.55, 0.65, 0.60, 1.0),   // xanh xám nhạt
    color4(0.12, 0.14, 0.13, 1.0),
    20.0f
    };

    // ===== CONCRETE BLUE =====
    const Material ConcreteBlue = {
        color4(0.20, 0.22, 0.25, 1.0),
        color4(0.55, 0.60, 0.70, 1.0),   // xanh ghi
        color4(0.12, 0.13, 0.15, 1.0),
        22.0f
    };

    // ===== CONCRETE BEIGE =====
    const Material ConcreteBeige = {
        color4(0.26, 0.25, 0.23, 1.0),
        color4(0.70, 0.68, 0.62, 1.0),
        color4(0.15, 0.14, 0.13, 1.0),
        20.0f
    };

    // ===== CONCRETE DARK =====
    const Material ConcreteDark = {
        color4(0.15, 0.15, 0.15, 1.0),
        color4(0.35, 0.35, 0.35, 1.0),   // xám đậm
        color4(0.1, 0.1, 0.1, 1.0),
        18.0f
    };

    // ================== LEAF GREEN ==================
    const Material LeafGreen = {
        color4(0.05f, 0.15f, 0.05f, 1.0f),
        color4(0.20f, 0.60f, 0.25f, 1.0f),
        color4(0.20f, 0.30f, 0.20f, 1.0f),
        24.0f
    };

    const Material Sidewalk = {
        color4(0.55f, 0.55f, 0.5f, 1.0f),   // ambient
        color4(0.75f, 0.75f, 0.7f, 1.0f),   // diffuse (xám be sáng)
        color4(0.2f, 0.2f, 0.2f, 1.0f),     // specular
        16.0f
    };


    // ================== TOY RED ==================
    const Material ToyRed = {
        color4(0.20f, 0.05f, 0.05f, 1.0f),   // ambient
        color4(0.75f, 0.15f, 0.15f, 1.0f),   // diffuse
        color4(0.40f, 0.40f, 0.40f, 1.0f),   // specular
        32.0f
    };

    // ================== TOY BLUE ==================
    const Material ToyBlue = {
        color4(0.05f, 0.08f, 0.20f, 1.0f),
        color4(0.20f, 0.35f, 0.75f, 1.0f),
        color4(0.30f, 0.30f, 0.40f, 1.0f),
        28.0f
    };

    // ================== METAL GRAY ==================
    const Material MetalGray = {
        color4(0.20f, 0.20f, 0.20f, 1.0f),
        color4(0.55f, 0.55f, 0.55f, 1.0f),
        color4(0.75f, 0.75f, 0.75f, 1.0f),
        64.0f
    };

    // ================== METAL DARK ==================
    const Material MetalDark = {
        color4(0.05f, 0.05f, 0.05f, 1.0f),
        color4(0.20f, 0.20f, 0.20f, 1.0f),
        color4(0.30f, 0.30f, 0.30f, 1.0f),
        16.0f
    };

    // ================== RUBBER BLACK ==================
    const Material RubberBlack = {
        color4(0.02f, 0.02f, 0.02f, 1.0f),
        color4(0.10f, 0.10f, 0.10f, 1.0f),
        color4(0.05f, 0.05f, 0.05f, 1.0f),
        8.0f
    };

    const Material ToyGreen = {
    color4(0.05f, 0.15f, 0.10f, 1.0f),
    color4(0.20f, 0.60f, 0.35f, 1.0f),
    color4(0.25f, 0.25f, 0.25f, 1.0f),
    32.0f
    };

    const Material ToyYellow = {
        color4(0.25f, 0.20f, 0.05f, 1.0f),
        color4(0.90f, 0.75f, 0.25f, 1.0f),
        color4(0.30f, 0.30f, 0.30f, 1.0f),
        24.0f
    };

    const Material TireBlack = {
    color4(0.02f, 0.02f, 0.02f, 1.0f),
    color4(0.08f, 0.08f, 0.08f, 1.0f),
    color4(0.3f, 0.3f, 0.3f, 1.0f),
    32.0f
    const Material Glass = {
        color4(0.1f, 0.1f, 0.1f, 1.0f),   // ambient (màu gần trong suốt)
        color4(0.9f, 0.9f, 0.9f, 0.3f),   // diffuse (màu gần như trong suốt với độ mờ nhẹ)
        color4(1.0f, 1.0f, 1.0f, 1.0f),   // specular (phản chiếu sáng mạnh)
        128.0f                            // Shininess (giá trị cao, giúp tạo độ bóng cho kính)
    };
}
