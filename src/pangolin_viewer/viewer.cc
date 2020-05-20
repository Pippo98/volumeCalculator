#include "viewer.h"
#include <unistd.h>

#include <opencv2/highgui.hpp>

#include <iostream>
using namespace std;

namespace pangolin_viewer
{

    void Viewer::canvas(std::vector<quicktype::Landmark> landmarks)
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

                        glLineWidth(1);
            glBegin(GL_POINTS);

            for (auto lm : landmarks)
            {
                int scale = 1;

                float x, y, z;
                x = lm.pos_w[0] / scale;
                y = lm.pos_w[1] / scale;
                z = lm.pos_w[2] / scale;
                //glVertex3f(x, y, z);
                glVertex3fv(lm.pos_w.cast<float>().eval().data());
                // cout << lm.pos_w.cast<float>().eval().data();
            }
            glEnd();

            // Swap frames and Process Events
            pangolin::FinishFrame();

            usleep(1000);
        }
    }
    void Viewer::draw_points(std::vector<quicktype::Keypt> keypoints)
    {
        glPushMatrix();

        glLineWidth(1);
        glBegin(GL_LINES);

        for (int i = 0; i < keypoints.size(); i++)
        {
            glVertex3f(keypoints[i].pt[0], keypoints[i].pt[1], 0.0f);
        }
        glEnd();

        glPopMatrix();
    }

    void Viewer::set_map_class()
    {
    }

} // namespace pangolin_viewer