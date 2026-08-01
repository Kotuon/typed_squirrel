#version 460 core

// uniform mat4 view;
// uniform mat4 proj;
// uniform vec3 cameraPos;
layout(std140, binding = 0) uniform PerFrameData {
  mat4 view;
  mat4 proj;
  vec4 cameraPos;
};

struct Vertex {
  float p[3];
  float n[3];
  float tc[2];
};

layout(std430, binding = 1) restrict readonly buffer Vertices {
  Vertex in_Vertices[];
};

layout(std430, binding = 2) restrict readonly buffer Matrices {
  mat4 in_ModelMatrices[];
};

// extents of grid in world coordinates
float gridSize = 100.0;

const vec3 pos[4] = vec3[4](vec3(-1.0, 0.0, -1.0), vec3(1.0, 0.0, -1.0),
                            vec3(1.0, 0.0, 1.0), vec3(-1.0, 0.0, 1.0));

const int indices[6] = int[6](0, 1, 2, 2, 3, 0);

layout(location = 0) out vec2 uv;
layout(location = 1) out vec2 out_camPos;

// normal vertice projection
void main() {
  mat4 MVP = proj * view;

  int idx = indices[gl_VertexID];
  vec3 position = pos[idx] * gridSize;

  position.x += cameraPos.x;
  position.z += cameraPos.z;

  out_camPos = cameraPos.xz;

  gl_Position = MVP * vec4(position, 1.0);
  uv = position.xz;
}
