#version 150

// Input is the passed point cloud
layout (lines) in;

// The output will consist of triangle strips with four vertices each
layout (line_strip, max_vertices = 10) out;

// Main entry point
void main()
{
    /////////////////////////////////////////////////////
    // Create an original primitive without any changes
    /////////////////////////////////////////////////////
    gl_Position = gl_in[0].gl_Position;
  
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EndPrimitive();

    /////////////////////////////////////////////////////
    // Generate a duplicated geometry but with a position offset
    // This technique will add a geometry which will create a wrapping effect
    /////////////////////////////////////////////////////

// Screen Percentage Value (-1.0 means it's at position 0.0 and 1.0 means that geometry is at the max with/height of the screen)
float ScreenPosPercent = 1.0;

    /////////////////////////////////////////////////////
    // Wrap X coordinate
    /////////////////////////////////////////////////////

// Position offset on X axis for the duplicated geometry
 float OffsetX = 0;

// Check if the geometry reached the maximum width of the screen
if(gl_in[0].gl_Position.x > ScreenPosPercent || gl_in[1].gl_Position.x > ScreenPosPercent)
    {
        // Duplicate geometry and calculate the position offset for the new geometry. Then, set the Y coordinate.

        gl_Position = gl_in[0].gl_Position;
        OffsetX = gl_in[0].gl_Position.x - ScreenPosPercent;
        gl_Position.x = OffsetX - ScreenPosPercent;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        OffsetX = gl_in[1].gl_Position.x - 1.0;
        gl_Position.x = OffsetX - ScreenPosPercent;
        EmitVertex();

        EndPrimitive();
    }

// Check if the geometry is positioned below the minimum width (0.0) of the screen
if(gl_in[0].gl_Position.x < -ScreenPosPercent || gl_in[1].gl_Position.x < -ScreenPosPercent)
    {
        // Duplicate geometry and calculate the position offset for the new geometry. Then, set the Y coordinate.

        gl_Position = gl_in[0].gl_Position;
        OffsetX = gl_in[0].gl_Position.x + 1.0;
        gl_Position.x = OffsetX + ScreenPosPercent;
        EmitVertex();

        OffsetX = gl_in[1].gl_Position.x + 1.0;
        gl_Position = gl_in[1].gl_Position;
        gl_Position.x = OffsetX + ScreenPosPercent;
        EmitVertex();
        EndPrimitive();
    }

    /////////////////////////////////////////////////////
    // Wrap Y coordinate
    /////////////////////////////////////////////////////

// Position offset on Y axis for the duplicated geometry
float OffsetY = 0;

// Check if the geometry reached the maximum height of the screen
if(gl_in[0].gl_Position.y > ScreenPosPercent || gl_in[1].gl_Position.y > ScreenPosPercent)
    {
        // Duplicate geometry and calculate the position offset for the new geometry. Then, set the Y coordinate.

        gl_Position = gl_in[0].gl_Position;
        OffsetY = gl_in[0].gl_Position.y - ScreenPosPercent;
        gl_Position.y = OffsetY - ScreenPosPercent;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        OffsetY = gl_in[1].gl_Position.y - ScreenPosPercent;
        gl_Position.y = OffsetY - ScreenPosPercent;
        EmitVertex();

        EndPrimitive();
    }

// Check if the geometry is positioned below the minimum height (0.0) of the screen
if(gl_in[0].gl_Position.y < -ScreenPosPercent || gl_in[1].gl_Position.y < -ScreenPosPercent)
    {
         // Duplicate geometry and calculate the position offset for the new geometry. Then, set the Y coordinate.

        gl_Position = gl_in[0].gl_Position;
        OffsetY = gl_in[0].gl_Position.y + ScreenPosPercent;
        gl_Position.y = OffsetY + ScreenPosPercent;
        EmitVertex();

        OffsetY = gl_in[1].gl_Position.y + ScreenPosPercent;
        gl_Position = gl_in[1].gl_Position;
        gl_Position.y = OffsetY + ScreenPosPercent;
        EmitVertex();

        EndPrimitive();
    }
}
