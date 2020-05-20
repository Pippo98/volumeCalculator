#include "pangolin_viewer/viewer.h"
#include "publisher/map_publisher.h"
#include "data/data.h"

#include <iostream>
using namespace std;

int main(int, char **)
{
    pangolin_viewer::Viewer pgV;

    publish::map_publisher map;

    map.load_json();

    //std::vector<quicktype::Keypt> keypts = map.get_keyframes();

    std::vector<quicktype::Landmark> landmarks = map.get_landmarks();

    pgV.canvas(landmarks);

    return 0;
}