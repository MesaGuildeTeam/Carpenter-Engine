precision mediump float;

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;
attribute vec2 a_Density;

uniform vec2 u_Window;
uniform mat4 u_Transform;
uniform mat4 u_Camera;

varying vec2 v_UV;
varying vec3 v_Normal;
varying vec3 v_Position;
varying vec2 v_Density;
varying mat3 v_TBN;

uniform sampler2D u_Color;

void main() {

  // Transform point position
  mat3 normal_transform = mat3(u_Transform[0].xyz, u_Transform[1].xyz, u_Transform[2].xyz);

  // Compute Normals ahead of time 
  v_Normal = normal_transform * a_Normal;
  v_Normal = v_Normal / length(v_Normal);

  // Discard Vertices by backface culling in Vertex Shader
  if (v_Normal.z < 0.0) {
    gl_PointSize = 0.0;
    gl_Position = vec4(2.0, 2.0, 2.0, 1.0);
    return;
  }

  // Calculate Tangent and bitangent
  vec3 up = abs(v_Normal.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tangent = normalize(cross(up, v_Normal));
  vec3 bitangent = normalize(cross(v_Normal, tangent));
  v_TBN = mat3(tangent, bitangent, v_Normal);

  vec4 newPos =  u_Camera * u_Transform * vec4(a_Position, 1.0);
  
  vec2 proportionalPos = vec2(newPos.x, newPos.y);
  float PWRatio = u_Window.x / u_Window.y;

  if (u_Window.y < u_Window.x) {
    proportionalPos.x = newPos.x * u_Window.y / u_Window.x;
    PWRatio = u_Window.y / u_Window.x;
  } else {
    proportionalPos.y = newPos.y * u_Window.x / u_Window.y;
  }
  
  gl_Position = vec4(proportionalPos, (newPos.z - 100.0) / 100.0, 1.0);

  float FOV = length(vec3(u_Camera[0][0], u_Camera[0][1], u_Camera[0][2]));
  
  // Determine Point Size

  v_Density = a_Density * vec2(u_Transform[1][1], u_Transform[0][0]) / min(a_Density.x * u_Transform[1][1], a_Density.y * u_Transform[0][0]);

  // 70 is just a sweet spot. There is no exact reason why
  gl_PointSize = (100.0 * max(a_Density.x * u_Transform[1][1], a_Density.y * u_Transform[0][0]) * FOV * PWRatio / gl_Position.w) / (abs(gl_Position.z));

  // Forward UV Map
  v_UV = a_UV;
}