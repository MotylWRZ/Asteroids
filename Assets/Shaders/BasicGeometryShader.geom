#version 330

// Input is the passed point cloud
layout (lines) in;

// The output will consist of triangle strips with four vertices each
layout (line_strip, max_vertices = 7) out;

// Main entry point
void main()
{

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EndPrimitive();
}