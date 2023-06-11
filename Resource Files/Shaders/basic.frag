#version 330 core

// Outputs colours in RGBA
out vec4 FragColor;

// Inputs the colour from the vertex shader (flat qualifier)
flat in vec3 color;


void main()
{
    FragColor = vec4(color, 1.0f);

    // TEST
    //vec4 texColor = texture(tex0, texcoord);
    //float a = texColor.a;
    //FragColor = color * (1-a) + texColor * a; // this is called the "over" operator

}