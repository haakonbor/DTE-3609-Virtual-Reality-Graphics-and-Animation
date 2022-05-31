#include "../include/Snow.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"
#include "../include/Utils.hpp"
#include "../include/stb_image.h"

#include <iostream>
#include <fstream>
#include <random>

Snow::Snow() {

}

Snow::~Snow() {

}

void Snow::privateInit() {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        particles[loop].active=true;								// Make All The Particles Active
        particles[loop].life=100.0f;								// Give All The Particles Full Life
        particles[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
        particles[loop].xi=float((rand()%1000)-500.0f)*10.0f;		// Random Speed On X Axis
        particles[loop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
        particles[loop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
        particles[loop].xg=0.0f;									// Set Horizontal Pull To Zero
        particles[loop].yg=-3.8f;								// Set Vertical Pull Downward
        particles[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
    }

    setUpTexture();
}

void Snow::privateRender() {

    glLoadIdentity();										// Reset The ModelView Matrix

    for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
    {
        if (particles[loop].active)							// If The Particle Is Active
        {
            float x=particles[loop].x;						// Grab Our Particle X Position
            float y=particles[loop].y;						// Grab Our Particle Y Position
            float z=particles[loop].z+zoom;					// Particle Z Pos + Zoom

            glColor3f(1.0f, 1.0f, 1.0f);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);

            glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
                glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
                glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
                glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
                glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
            glEnd();										// Done Building Triangle Strip

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            particles[loop].x+=particles[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
            particles[loop].y+=particles[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
            particles[loop].z+=particles[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

            particles[loop].xi+=particles[loop].xg;			// Take Pull On X Axis Into Account
            particles[loop].yi+=particles[loop].yg;			// Take Pull On Y Axis Into Account
            particles[loop].zi+=particles[loop].zg;			// Take Pull On Z Axis Into Account
            particles[loop].life-=particles[loop].fade;		// Reduce Particles Life By 'Fade'

            if (particles[loop].life<0.0f)					// If Particle Is Burned Out
            {
                particles[loop].life=100.0f;					// Give It New Life
                particles[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
                particles[loop].x=0.0f;						// Center On X Axis
                particles[loop].y=40.0f;						// Center On Y Axis
                particles[loop].z=0.0f;						// Center On Z Axis
                particles[loop].xi=float((rand()%1000)-500.0f);	// X Axis Speed And Direction
                particles[loop].yi=float(-30.0f);	// Y Axis Speed And Direction
                particles[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
            }
        }
    }

}

void Snow::privateUpdate() {

}

void Snow::setUpTexture() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    std::string filepath = "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/snow.png";
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE FROM " << filepath <<"\nFAILURE REASON: "<< stbi_failure_reason() << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}
