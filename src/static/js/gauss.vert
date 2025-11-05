precision mediump float;

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec3 a_Normal;
attribute float a_Density;

uniform vec2 u_Window;
uniform mat4 u_Transform;
uniform mat4 u_Camera;

varying vec2 v_UV;
varying vec3 v_Normal;
varying vec3 v_Position;

uniform sampler2D u_Color;

vec3 convolve3x3(sampler2D tex, vec2 uv, mat3 kernel, float texelSize) {
    vec3 result = vec3(0.0);

    // Iterate through the 3x3 neighborhood
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            vec3 sample = texture2D(tex, uv + offset).rgb;
            result += sample * kernel[y + 1][x + 1];
        }
    }

    return result;
}

void main() {

  // Transform point position
  mat3 normal_transform = mat3(u_Transform[0].xyz, u_Transform[1].xyz, u_Transform[2].xyz);

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
  
  // Determine Point Size

  // 70 is just a sweet spot. There is no exact reason why
  vec3 pointScale = (u_Transform[3].xyz * u_Camera[3].xyz);
  gl_PointSize = (15.0 * a_Density * PWRatio / gl_Position.w) / (1.0 + gl_Position.z);

  // Forwared Normals and UV 
  v_UV = a_UV;
  v_Normal = normal_transform * a_Normal;
  v_Normal = v_Normal / length(v_Normal);
}