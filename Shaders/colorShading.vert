#version 130
// The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

// this output color is sent to the fragment, if they share the same name
// to stop interpolation, add a flat before the out
out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 P; //passing in our orthographic projection 

void main() {
	//sets the x,y positions on the screen
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	
	//z position is zero since its 2D
	gl_Position.z = 0.0;
	
	//Indicates that the coordniates are normalized
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}