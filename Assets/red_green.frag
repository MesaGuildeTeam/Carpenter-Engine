precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;
uniform mat4 u_Transform;

uniform sampler2D u_Color;
uniform float time;

void main() {
  gl_FragColor = vec4(sin(time), 1.0, cos(time), 1.0);
}