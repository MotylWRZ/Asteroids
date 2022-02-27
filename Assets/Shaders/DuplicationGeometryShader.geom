#version 330

// Input is the passed point cloud
layout (lines) in;

// The output will consist of triangle strips with four vertices each
layout (line_strip, max_vertices = 14) out;

// Main entry point
void main()
{
    // Create an original primitive without any changes
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EndPrimitive();

   vec4 Offset = vec4(0.1, vec3(0.0));

    // Create a primite which is a duplicate of the original one and offset it by adding an offset vector.
    gl_Position = gl_in[0].gl_Position + Offset;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + Offset;
    EmitVertex();
  
    EndPrimitive();
}