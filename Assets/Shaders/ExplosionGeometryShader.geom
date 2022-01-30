#version 330

// Input is the passed point cloud
layout (lines) in;

// The output will consist of triangle strips with four vertices each
layout (line_strip, max_vertices = 14) out;

uniform float Time;
uniform vec4 Center;

// Main entry point
void main()
{
vec4 Offset = vec4(0.1, vec3(0.0));

  vec4 tMidpoint = (gl_in[0].gl_Position + gl_in[1].gl_Position) * 0.5;

  gl_Position = gl_in[0].gl_Position;
  vec4 tDiff = vec4(0.0, 0.0, 0.0, 0.0) - gl_Position;
  tDiff = normalize(tDiff);
  tDiff *= 0.1;
  gl_Position += tDiff;
  EmitVertex();

  gl_Position = gl_in[1].gl_Position;
  vec4 tDiff2 = vec4(0.0, 0.0, 0.0, 0.0) - gl_Position;
  tDiff2 = normalize(tDiff2);
  tDiff2 *= 0.9;
  gl_Position += tDiff2;
  EmitVertex();

 EndPrimitive();


    // Create a primite which is a duplicate of the original one and offset it by adding an offset vector.
   // gl_Position = gl_in[0].gl_Position;
   // EmitVertex();

    //gl_Position = gl_in[1].gl_Position;
    //EmitVertex();

    // Find the line midpoint
    //gl_Position = (gl_in[0].gl_Position + gl_in[1].gl_Position) * 0.5;
    //gl_Position += vec4(Time, Time, 0.0, 0.0);
    //EmitVertex();

   // gl_Position = gl_in[0].gl_Position;
   // EmitVertex();
  
   
}