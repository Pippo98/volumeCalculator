#include "map_publisher.h"
#include "bits/stdc++.h"

#include <typeinfo>
#include <iostream>
#include <fstream>
using namespace std;

namespace publish
{
    void map_publisher::load_json()
    {

        std::ifstream ifs("/media/filippo/label/Codes/Github/openvslam/build/map.msg", std::ifstream::in);
        // std::ifstream ifs("/home/filippo/Desktop/test1/map.msg", std::ifstream::in);
        std::stringstream stream;
        stream << ifs.rdbuf();
        msgpack::unpacked upd;
        msgpack::unpack(upd, stream.str().data(), stream.str().size());

        ofstream myfile;
        myfile.open("map.txt");
        myfile << upd.get();
        myfile.close();

        std::ifstream is("map.txt", std::ifstream::in);

        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        char *buffer = new char[length];

        is.read(buffer, length);

        map_j = nlohmann::json::parse(buffer);
    }

    std::vector<quicktype::Landmark> map_publisher::get_landmarks()
    {
        std::vector<quicktype::Landmark> landmarks;

        for (const auto keyframe : map_j["keyframes"])
        {
            int n_keypts = keyframe["n_keypts"];
            std::vector<int64_t> id_lm = keyframe["lm_ids"];

            for (int i = 0; i < n_keypts; i++)
            {
                int id = id_lm[i];
                if (id < 0)
                {
                    continue;
                }
                const auto landmark = map_j["landmarks"][std::to_string(id)];
                landmarks.push_back(landmark);
            }
        }
        return landmarks;
    }

} // namespace publish