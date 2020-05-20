#pragma once

#include "../json/include/nlohmann/json.hpp"
#include "../json/include/nlohmann/json_fwd.hpp"

#include "type.h"

namespace quicktype
{
    using nlohmann::json;

    inline json get_untyped(const json &j, const char *property)
    {
        if (j.find(property) != j.end())
        {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json &j, std::string property)
    {
        return get_untyped(j, property.data());
    }

    struct P20Lite
    {
        std::string color_order;
        int64_t cols;
        double cx;
        double cy;
        int64_t focal_x_baseline;
        int64_t fps;
        double fx;
        double fy;
        double k1;
        double k2;
        int64_t k3;
        std::string model_type;
        int64_t num_grid_cols;
        int64_t num_grid_rows;
        double p1;
        double p2;
        int64_t rows;
        std::string setup_type;
    };

    struct Cameras
    {
        P20Lite p20_lite;
    };

    struct Keypt
    {
        double ang;
        int64_t oct;
        std::vector<double> pt;
    };

    struct Keyframe
    {
        std::string cam;
        int64_t depth_thr;
        std::vector<int64_t> depths;
        std::vector<std::vector<int64_t>> descs;
        std::vector<Keypt> keypts;
        std::vector<int64_t> lm_ids;
        std::vector<nlohmann::json> loop_edges;
        int64_t n_keypts;
        int64_t n_scale_levels;
        std::vector<double> rot_cw;
        double scale_factor;
        std::vector<int64_t> span_children;
        int64_t span_parent;
        int64_t src_frm_id;
        std::vector<double> trans_cw;
        double ts;
        std::vector<std::vector<double>> undists;
        std::vector<int64_t> x_rights;
    };

    struct Landmark
    {
        int64_t the_1_st_keyfrm;
        int64_t n_fnd;
        int64_t n_vis;
        quicktype::Vec3_t pos_w;
        int64_t ref_keyfrm;
    };

    struct Map
    {
        Cameras cameras;
        int64_t frame_next_id;
        int64_t keyframe_next_id;
        std::map<std::string, Keyframe> keyframes;
        int64_t landmark_next_id;
        std::map<std::string, Landmark> landmarks;
    };
} // namespace quicktype

namespace nlohmann
{
    void from_json(const json &j, quicktype::P20Lite &x);
    void to_json(json &j, const quicktype::P20Lite &x);

    void from_json(const json &j, quicktype::Cameras &x);
    void to_json(json &j, const quicktype::Cameras &x);

    void from_json(const json &j, quicktype::Keypt &x);
    void to_json(json &j, const quicktype::Keypt &x);

    void from_json(const json &j, quicktype::Keyframe &x);
    void to_json(json &j, const quicktype::Keyframe &x);

    void from_json(const json &j, quicktype::Landmark &x);
    void to_json(json &j, const quicktype::Landmark &x);

    void from_json(const json &j, quicktype::Map &x);
    void to_json(json &j, const quicktype::Map &x);

    inline void from_json(const json &j, quicktype::P20Lite &x)
    {
        x.color_order = j.at("color_order").get<std::string>();
        x.cols = j.at("cols").get<int64_t>();
        x.cx = j.at("cx").get<double>();
        x.cy = j.at("cy").get<double>();
        x.focal_x_baseline = j.at("focal_x_baseline").get<int64_t>();
        x.fps = j.at("fps").get<int64_t>();
        x.fx = j.at("fx").get<double>();
        x.fy = j.at("fy").get<double>();
        x.k1 = j.at("k1").get<double>();
        x.k2 = j.at("k2").get<double>();
        x.k3 = j.at("k3").get<int64_t>();
        x.model_type = j.at("model_type").get<std::string>();
        x.num_grid_cols = j.at("num_grid_cols").get<int64_t>();
        x.num_grid_rows = j.at("num_grid_rows").get<int64_t>();
        x.p1 = j.at("p1").get<double>();
        x.p2 = j.at("p2").get<double>();
        x.rows = j.at("rows").get<int64_t>();
        x.setup_type = j.at("setup_type").get<std::string>();
    }

    inline void to_json(json &j, const quicktype::P20Lite &x)
    {
        j = json::object();
        j["color_order"] = x.color_order;
        j["cols"] = x.cols;
        j["cx"] = x.cx;
        j["cy"] = x.cy;
        j["focal_x_baseline"] = x.focal_x_baseline;
        j["fps"] = x.fps;
        j["fx"] = x.fx;
        j["fy"] = x.fy;
        j["k1"] = x.k1;
        j["k2"] = x.k2;
        j["k3"] = x.k3;
        j["model_type"] = x.model_type;
        j["num_grid_cols"] = x.num_grid_cols;
        j["num_grid_rows"] = x.num_grid_rows;
        j["p1"] = x.p1;
        j["p2"] = x.p2;
        j["rows"] = x.rows;
        j["setup_type"] = x.setup_type;
    }

    inline void from_json(const json &j, quicktype::Cameras &x)
    {
        x.p20_lite = j.at("P20Lite").get<quicktype::P20Lite>();
    }

    inline void to_json(json &j, const quicktype::Cameras &x)
    {
        j = json::object();
        j["P20Lite"] = x.p20_lite;
    }

    inline void from_json(const json &j, quicktype::Keypt &x)
    {
        x.ang = j.at("ang").get<double>();
        x.oct = j.at("oct").get<int64_t>();
        x.pt = j.at("pt").get<std::vector<double>>();
    }

    inline void to_json(json &j, const quicktype::Keypt &x)
    {
        j = json::object();
        j["ang"] = x.ang;
        j["oct"] = x.oct;
        j["pt"] = x.pt;
    }

    inline void from_json(const json &j, quicktype::Keyframe &x)
    {
        x.cam = j.at("cam").get<std::string>();
        x.depth_thr = j.at("depth_thr").get<int64_t>();
        x.depths = j.at("depths").get<std::vector<int64_t>>();
        x.descs = j.at("descs").get<std::vector<std::vector<int64_t>>>();
        x.keypts = j.at("keypts").get<std::vector<quicktype::Keypt>>();
        x.lm_ids = j.at("lm_ids").get<std::vector<int64_t>>();
        x.loop_edges = j.at("loop_edges").get<std::vector<json>>();
        x.n_keypts = j.at("n_keypts").get<int64_t>();
        x.n_scale_levels = j.at("n_scale_levels").get<int64_t>();
        x.rot_cw = j.at("rot_cw").get<std::vector<double>>();
        x.scale_factor = j.at("scale_factor").get<double>();
        x.span_children = j.at("span_children").get<std::vector<int64_t>>();
        x.span_parent = j.at("span_parent").get<int64_t>();
        x.src_frm_id = j.at("src_frm_id").get<int64_t>();
        x.trans_cw = j.at("trans_cw").get<std::vector<double>>();
        x.ts = j.at("ts").get<double>();
        x.undists = j.at("undists").get<std::vector<std::vector<double>>>();
        x.x_rights = j.at("x_rights").get<std::vector<int64_t>>();
    }

    inline void to_json(json &j, const quicktype::Keyframe &x)
    {
        j = json::object();
        j["cam"] = x.cam;
        j["depth_thr"] = x.depth_thr;
        j["depths"] = x.depths;
        j["descs"] = x.descs;
        j["keypts"] = x.keypts;
        j["lm_ids"] = x.lm_ids;
        j["loop_edges"] = x.loop_edges;
        j["n_keypts"] = x.n_keypts;
        j["n_scale_levels"] = x.n_scale_levels;
        j["rot_cw"] = x.rot_cw;
        j["scale_factor"] = x.scale_factor;
        j["span_children"] = x.span_children;
        j["span_parent"] = x.span_parent;
        j["src_frm_id"] = x.src_frm_id;
        j["trans_cw"] = x.trans_cw;
        j["ts"] = x.ts;
        j["undists"] = x.undists;
        j["x_rights"] = x.x_rights;
    }

    inline void from_json(const json &j, quicktype::Landmark &x)
    {
        x.the_1_st_keyfrm = j.at("1st_keyfrm").get<int64_t>();
        x.n_fnd = j.at("n_fnd").get<int64_t>();
        x.n_vis = j.at("n_vis").get<int64_t>();
        x.pos_w = quicktype::Vec3_t(j.at("pos_w").get<std::vector<quicktype::Vec3_t::value_type>>().data());
        x.ref_keyfrm = j.at("ref_keyfrm").get<int64_t>();
    }

    inline void to_json(json &j, const quicktype::Landmark &x)
    {
        j = json::object();
        j["1st_keyfrm"] = x.the_1_st_keyfrm;
        j["n_fnd"] = x.n_fnd;
        j["n_vis"] = x.n_vis;
        j["pos_w"] = {x.pos_w(0), x.pos_w(1), x.pos_w(2)};
        j["ref_keyfrm"] = x.ref_keyfrm;
    }

    inline void from_json(const json &j, quicktype::Map &x)
    {
        x.cameras = j.at("cameras").get<quicktype::Cameras>();
        x.frame_next_id = j.at("frame_next_id").get<int64_t>();
        x.keyframe_next_id = j.at("keyframe_next_id").get<int64_t>();
        x.keyframes = j.at("keyframes").get<std::map<std::string, quicktype::Keyframe>>();
        x.landmark_next_id = j.at("landmark_next_id").get<int64_t>();
        x.landmarks = j.at("landmarks").get<std::map<std::string, quicktype::Landmark>>();
    }

    inline void to_json(json &j, const quicktype::Map &x)
    {
        j = json::object();
        j["cameras"] = x.cameras;
        j["frame_next_id"] = x.frame_next_id;
        j["keyframe_next_id"] = x.keyframe_next_id;
        j["keyframes"] = x.keyframes;
        j["landmark_next_id"] = x.landmark_next_id;
        j["landmarks"] = x.landmarks;
    }
} // namespace nlohmann
