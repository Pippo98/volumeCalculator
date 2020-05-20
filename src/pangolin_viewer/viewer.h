#ifndef PANGILIN_VIEWER_VIEWER_H
#define PANGILIN_VIEWER_VIEWER_H

#include <pangolin/pangolin.h>

#include <memory>
#include "../data/data.h"

namespace pangolin_viewer
{
    class Viewer
    {
    public:
        void canvas(std::vector<quicktype::Landmark> keypoints);

        void set_map_class();
        void draw_points(std::vector<quicktype::Keypt>);

    private:
        inline void draw_line(float x1, float y1, float z1,
                              float x2, float y2, float z2) const
        {
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
    };

}; // namespace pangolin_viewer
#endif