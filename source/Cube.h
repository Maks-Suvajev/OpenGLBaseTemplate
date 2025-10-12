#ifndef CUBE_H
#define CUBE_H


namespace gfx {

// This only worked without using indices.
//
// float cubeVertices[] = {
//     // positions         // texture coords
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0: left-bottom-back
//      0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1: right-bottom-back
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2: right-top-back
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3: left-top-back
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4: left-bottom-front
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5: right-bottom-front
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6: right-top-front
//     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f  // 7: left-top-front
// };

// unsigned int cubeIndices[] = {
//     // back face
//     0, 1, 2,
//     2, 3, 0,
//     // front face
//     4, 5, 6,
//     6, 7, 4,
//     // left face
//     0, 3, 7,
//     7, 4, 0,
//     // right face
//     1, 5, 6,
//     6, 2, 1,
//     // bottom face
//     0, 1, 5,
//     5, 4, 0,
//     // top face
//     3, 2, 6,
//     6, 7, 3
// };

    float cubeVertices[] = {
        // positions        // texture coords
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3

        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7

        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 8
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // 9
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 10
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 11

        // Right face
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 12
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // 13
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 14
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 15

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 19

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, // 20
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, // 21
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 22
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f  // 23
    };

    unsigned int cubeIndices[] = {
        0, 1, 2, 2, 3, 0,       // back
        4, 5, 6, 6, 7, 4,       // front
        8, 9, 10, 10, 11, 8,    // left
        12, 13, 14, 14, 15, 12, // right
        16, 17, 18, 18, 19, 16, // bottom
        20, 21, 22, 22, 23, 20  // top
    };



    //TODO: Needs to be done without indexing for now, this seems to be breaking awesomeface and i cant figure out why immediately
    // float cubeVertices[] = {
    //     // positions           // texcoords
    //     // +X face
    //     0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    //     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,

    //     // -X face
    //     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    //     -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,

    //     // +Y face
    //     -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,
    //     0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

    //     // -Y face
    //     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    //     0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

    //     // +Z face
    //     0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,

    //     // -Z face
    //     -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    //     0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f,   1.0f, 0.0f
    // };

    // unsigned int cubeIndices[] = {
    //     0,  1,  2,   0,  2,  3,   // +X
    //     4,  5,  6,   4,  6,  7,   // -X
    //     8,  9, 10,   8, 10, 11,   // +Y
    //     12, 13, 14,  12, 14, 15,   // -Y
    //     16, 17, 18,  16, 18, 19,   // +Z
    //     20, 21, 22,  20, 22, 23    // -Z
    // };



    
}

#endif