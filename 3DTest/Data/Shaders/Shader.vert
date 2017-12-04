#version 330
uniform mat4 M_Model;
uniform mat4 M_View;
uniform mat4 M_Projection;

in vec3 Position;
in vec3 Normal;

//output world-space position and normal
out vec4 W_Position;
out vec4 W_Normal;

//output clip-space position
out vec4 C_Position;

void main() {
	W_Position = 	M_Model * vec4(Position, 1);
	W_Normal = 		M_Model * vec4(Normal, 0);
	
	C_Position = M_View * W_Position;
	
	gl_Position = M_Projection * C_Position;
}
