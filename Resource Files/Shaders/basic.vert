#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;
// Colours
layout (location = 1) in vec3 aColor;


// Outputs the colour for the fragment shader (flat qualifier)
flat out vec3 color;

// Controls the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // Assigns the colours from the Vertex Data to "color"
   color = aColor;
}