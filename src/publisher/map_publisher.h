#ifndef PUBLISHER_MAP_PUBLISHER_H
#define PUBLISHER_MAP_PUBLISHER_H

#include <mutex>

#include <msgpack.hpp>
#include <string>
#include <sstream>
#include "../data/data.h"

namespace publish
{
    class map_publisher
    {
    public:
        void load_json();

        std::vector<quicktype::Landmark> get_landmarks();
        std::vector<quicktype::Vec3_t> get_points();
        quicktype::NearPoints get_near_points();

        void load_near_points();
        void load_landmarks();
        void load_points();

    private:
        nlohmann::json map_j;

        std::vector<quicktype::Landmark> landmarks_;
        std::vector<quicktype::Vec3_t> points_;
        quicktype::NearPoints nr_points_;
    };

} // namespace publish

#endif // PUBLISHER_MAP_PUBLISHER_H