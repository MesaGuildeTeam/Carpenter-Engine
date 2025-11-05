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
  // transform vertex position
  vec4 newPos =  u_Camera * u_Transform * vec4(a_Position, 1.0);
  
  vec2 proportionalPos = vec2(newPos.x, newPos.y);

  if (u_Window.y < u_Window.x) {
    proportionalPos.x = newPos.x * u_Window.y / u_Window.x;
  } else {
    proportionalPos.y = newPos.y * u_Window.x / u_Window.y;
  }
  
  gl_Position = vec4(proportionalPos, (newPos.z - 100.0) / 100.0, 1.0);
  
  // Find Vertex Normal
  vec3 difference = normalize(vec3(u_Camera[3].xyz) - a_Position);
  float theta = atan(difference.y/length(difference));
  float phi = atan(difference.z/length(difference));

  vec3 smooth_normal = vec3(
    cos(phi)*difference.x -sin(phi)*cos(theta)*difference.y + sin(phi)*cos(theta)*difference.z,
    sin(phi)*difference.x+cos(phi)*cos(theta)*difference.y-cos(phi)*sin(theta)*difference.z,
    sin(theta)*difference.y+cos(theta)*difference.z
  );

  mat3 normal_transform = mat3(u_Transform[0].xyz, u_Transform[1].xyz, u_Transform[2].xyz);

  v_UV = a_UV;

  v_Normal = normal_transform * smooth_normal;
  v_Normal = v_Normal / length(v_Normal);
}