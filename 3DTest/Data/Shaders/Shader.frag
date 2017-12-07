#version 330
//World-space position and normal
in vec4 W_Position;
in vec4 W_Normal;

//Clip-space position
in vec4 C_Position;

//Fragment colour
out vec4 colour;

float shininess = .0001;

vec3 ambient = vec3(0, 0.05, 0);
vec3 diffuse_colour = vec3(1, 1, 1);
vec3 specular_colour = vec3(1, 1, 1);
vec3 light_pos = vec3(0, 5, -2);

void main() {
	vec3 light_dir = normalize(light_pos - W_Position.xyz);
	vec3 eye_dir = normalize(-C_Position.xyz);
	vec3 reflection_dir = normalize(-reflect(light_dir, W_Normal.xyz));
	
	vec3 diffuse = diffuse_colour * clamp(dot(W_Normal.xyz, light_dir), 0, 1);
	
	vec3 specular = specular_colour * pow(dot(reflection_dir, eye_dir), shininess);
	specular = clamp(specular, 0, 1);
	
	colour = vec4(ambient + diffuse, 1);
}
