#version 130
//the fragment shader operates on each pixel in a given polygon

//to stop interpolation, add a flat before in
in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel
out vec4 color;

//textures are called sampler
uniform sampler2D mySampler;

void main(){
	
	//U and V coordinates map a texture to a geometry. Like the 
	//x and y axis of a texture
	vec4 textureColor = texture(mySampler, fragmentUV);
	
	color = fragmentColor * textureColor;
}