#version 140
// created by Thorsten Thormaehlen for educational purpose

in vec3 position;
in vec2 texcoord;
in vec3 normal;

uniform mat4 cameraLookAt;
uniform mat4 cameraProjection;
uniform mat4 meshTransform;
uniform mat4 meshTransformTransposedInverse;

out vec2 tc;
out vec3 wfn;
out vec3 vertPos;

void main(){
  tc = texcoord;
  wfn = vec3(meshTransformTransposedInverse * vec4(normal, 0.0));
  vec4 vertPos4 = meshTransform * vec4(position, 1.0);
  vertPos = vec3(vertPos4) / vertPos4.w;
  gl_Position = cameraProjection * cameraLookAt * vertPos4;
}
        
