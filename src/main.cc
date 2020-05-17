#include "pangolin_viewer/viewer.h"
#include "publisher/map_publisher.h"

#include <iostream>
using namespace std;

int main(int, char **)
{
    pangolin_viewer::Viewer pgV;

    publish::map_publisher map;

    map.test();

    //pgV.canvas();

    return 0;
}