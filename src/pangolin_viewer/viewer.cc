#include "viewer.h"
#include <unistd.h>

#include <opencv2/highgui.hpp>

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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // depth testing to be enabled for 3D mouse handler
        glEnable(GL_DEPTH_TEST);

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

            draw_points();
            draw_near_points();

            // Swap frames and Process Events
            pangolin::FinishFrame();

            //usleep(1000);
        }
    }
    void Viewer::draw_points()
    {
        std::vector<quicktype::Vec3_t> points = map->get_points();

        glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        glPointSize(4);
        for (auto point : points)
        {
            glVertex3fv(point.cast<float>().eval().data());
        }

        glEnd();
    }

    void Viewer::draw_near_points()
    {
        quicktype::NearPoints points = map->get_near_points();

        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        for (auto point : points.points)
        {
            quicktype::Vec3_t ref = std::get<0>(point);
            for (auto pt : std::get<1>(point))
            {
                glVertex3f(ref[0], ref[1], ref[2]);
                glVertex3f(pt[0], pt[1], pt[2]);
            }
        }
        glEnd();
    }

    void
    Viewer::set_map_class()
    {
    }

} // namespace pangolin_viewer