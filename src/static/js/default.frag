precision mediump float;

varying vec2 v_UV;
varying vec3 v_Normal;
uniform mat4 u_Transform;

uniform sampler2D u_Color;

void main() {
  float lighting = dot(v_Normal, vec3(-0.1, -0.5, 1.0) / sqrt(2.26));
  vec4 image = texture2D(u_Color, v_UV);
  gl_FragColor = image * vec4(vec3(lighting), 1.0);
}