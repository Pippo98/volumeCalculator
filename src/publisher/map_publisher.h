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

    private:
        nlohmann::json map_j;
    };

} // namespace publish

#endif // PUBLISHER_MAP_PUBLISHER_H