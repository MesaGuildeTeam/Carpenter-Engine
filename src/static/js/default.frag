precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;

uniform sampler2D u_Color;

void main() {
  gl_FragColor = texture2D(u_Color, v_UV);
}