#version 140
// created by Thorsten Thormaehlen for educational purpose

in vec3 position;
in vec2 texcoord;
in vec3 normal;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normalMat;


out vec2 tc;
out vec3 fn;
out vec3 vertPos;

void main(){
  tc = texcoord;
  fn = vec3(normalMat * vec4(normal, 0.0));
  vec4 vertPos4 = modelview * vec4(position, 1.0);
  vertPos = vec3(vertPos4) / vertPos4.w;
  gl_Position = projection * modelview * vec4(position, 1.0);
}
        
