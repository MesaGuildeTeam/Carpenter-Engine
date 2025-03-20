attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;

uniform vec2 window;

varying vec2 v_UV;
varying vec3 v_Normal;

void main() {
  gl_Position = vec4(a_Position.x * window.y / window.x, a_Position.y, a_Position.z, 1.0);
  v_UV = a_UV;
  v_Normal = a_Normal;
}