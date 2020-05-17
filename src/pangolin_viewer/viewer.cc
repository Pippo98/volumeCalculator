#include "viewer.h"
#include <unistd.h>
#include <iostream>
using namespace std;

namespace pangolin_viewer
{

    void Viewer::canvas()
    {
        pangolin::CreateWindowAndBind("Main", 640, 480);
        glEnable(GL_DEPTH_TEST);

        // Define Projection and initial ModelView matrix
        pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
            pangolin::ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin::AxisY));

        // Create Interactive View in window
        pangolin::Handler3D handler(s_cam);
        pangolin::View &d_cam = pangolin::CreateDisplay()
                                    .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
                                    .SetHandler(&handler);

        while (!pangolin::ShouldQuit())
        {
            // Clear screen and activate view to render into
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            d_cam.Activate(s_cam);

            // Render OpenGL Cube
            pangolin::glDrawColouredCube();

            glPushMatrix();

            glLineWidth(1);
            glBegin(GL_LINES);

            for (int y = 0; y < 100; y += 10)
            {
                for (int x = 0; x < 100; x += 10)
                {
                    draw_line(y, x, 0, y + 10, x + 10, 0);
                }
            }
            glEnd();

            glPopMatrix();

            // Swap frames and Process Events
            pangolin::FinishFrame();

            usleep(1000);
        }
    }
    void Viewer::draw_points()
    {
    }

    void Viewer::set_map_class()
    {
    }

} // namespace pangolin_viewer