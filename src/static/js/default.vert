precision mediump float;

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;

uniform vec2 u_Window;
uniform mat4 u_Transform;
uniform mat4 u_Camera;

varying vec2 v_UV;
varying vec3 v_Normal;

void main() {
  mat3 normal_transform = mat3(u_Transform[0].xyz, u_Transform[1].xyz, u_Transform[2].xyz);

  vec4 newPos = u_Transform * u_Camera * vec4(a_Position, 1.0);
  
  vec2 proportionalPos = vec2(newPos.x, newPos.y);

  if (u_Window.y < u_Window.x) {
    proportionalPos.x = newPos.x * u_Window.y / u_Window.x;
  } else {
    proportionalPos.y = newPos.y * u_Window.x / u_Window.y;
  }
  
  gl_Position = vec4(proportionalPos, (newPos.z - 100.0) / 100.0, 1.0);
  
  v_UV = a_UV;

  v_Normal = normal_transform * a_Normal;
  v_Normal = v_Normal / length(v_Normal);
}