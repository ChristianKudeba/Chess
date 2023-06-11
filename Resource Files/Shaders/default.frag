#version 330 core

// Outputs colours in RGBA
out vec4 FragColor;

// Inputs the colour from the vertex shader (flat qualifier)
flat in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the texture unit from the main function
uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, texCoord);

    // TEST
    //vec4 texColor = texture(tex0, texcoord);
    //float a = texColor.a;
    //FragColor = color * (1-a) + texColor * a; // this is called the "over" operator

}