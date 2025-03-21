precision mediump float;

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;

uniform vec2 u_Window;
uniform mat4 u_Transform;

varying vec2 v_UV;
varying vec3 v_Normal;

void main() {
  vec4 newPos = u_Transform * vec4(a_Position, 1.0);
  gl_Position = vec4(newPos.x * u_Window.y / u_Window.x, newPos.y, newPos.z, 1.0);
  v_UV = a_UV;
  v_Normal = a_Normal;
}