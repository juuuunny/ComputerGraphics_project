#version 140

// created by Thorsten Thormaehlen for educational purpose
in vec3 position;
in vec2 texcoord;
in vec3 normal;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normalMat;
uniform vec3 lightDirection;
uniform int mode;

out vec4 forFragColor;

const vec4 ambientColor = vec4(0.01, 0.0, 0.0, 1.0);
const vec4 diffuseColor = vec4(0.25, 0.0, 0.0, 1.0);
const vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
const float shininess = 20.0;
const vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
const float irradiPerp = 1.0;

vec3 phongBRDF(vec3 lightDir, vec3 viewDir, vec3 normal, vec3 phongDiffuseCol, vec3 phongSpecularCol, float phongShininess) {
  vec3 color = phongDiffuseCol;
  vec3 reflectDir = reflect(-lightDir, normal);
  float specDot = max(dot(reflectDir, viewDir), 0.0);
  color += pow(specDot, phongShininess) * phongSpecularCol;
  return color;
}

void main(){
    
  // all following geometric computations are performed in the
  // camera coordinate system (aka eye coordinates)
  
  vec4 vertPos4 = modelview * vec4(position, 1.0);
  vec3 vertPos = vec3(vertPos4) / vertPos4.w;
  vec3 n = vec3(normalMat * vec4(normal, 0.0));

  vec3 lightDir = normalize(-lightDirection);
  vec3 viewDir = normalize(-vertPos);

  vec3 radiance = ambientColor.rgb;
  
  float irradiance = max(dot(lightDir, n), 0.0) * irradiPerp;
  if(irradiance > 0.0) {
    vec3 brdf = phongBRDF(lightDir, viewDir, n, diffuseColor.rgb, specularColor.rgb, shininess);
    radiance += brdf * irradiance * lightColor.rgb;
  }
  
  radiance = pow(radiance, vec3(1.0 / 2.2) ); // gamma correction
  forFragColor = vec4(radiance, 1.0);
  gl_Position = projection * modelview * vec4(position, 1.0);
}
