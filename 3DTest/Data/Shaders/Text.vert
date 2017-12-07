#version 330
uniform mat4 M_Projection;
uniform mat4 M_Transform;

in vec2 Position;
in vec2 UV;

out vec2 F_UV;

void main() {
	F_UV = UV;
	
	gl_Position = M_Projection * M_Transform * vec4(Position.xy, 0, 1);
}
