#include "pangolin_viewer/viewer.h"
#include "publisher/map_publisher.h"
#include "data/data.h"

#include <iostream>
using namespace std;

int main(int, char **)
{

    publish::map_publisher map;

    pangolin_viewer::Viewer pgV(&map);

    cout << "Loading Map" << std::endl;
    map.load_json();
    cout << "Done" << std::endl;

    cout << "Loading Landmarks" << std::endl;
    std::vector<quicktype::Landmark> landmarks = map.get_landmarks();
    cout << "Found " << landmarks.size() << " landmarks" << std::endl;

    pgV.canvas();

    return 0;
}