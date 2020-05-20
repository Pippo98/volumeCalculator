#ifndef MAP_DATA_DATA_H
#define MAP_DATA_DATA_H

#include <set>
#include <vector>
#include <tuple>
#include <iostream>

#include <msgpack.hpp>
using namespace std;

namespace data
{
    class data
    {
    };

    class p20Lite
    {
    public:
        string color_order;
        long cols;
        double cx;
        double cy;
        long focal_x_baseline;
        long fps;
        double fx;
        double fy;
        double k1;
        double k2;
        long k3;
        string model_type;
        long num_grid_cols;
        long num_grid_rows;
        double p1;
        double p2;
        long rows;
        string setup_type;

        MSGPACK_DEFINE(color_order, cols, cx, cy, focal_x_baseline, fps, fx, fy, k1, k2, k3, model_type, num_grid_cols, num_grid_rows, p1, p2, rows, setup_type);
    };

    class Keypt
    {
    public:
        double ang;
        long oct;
        std::vector<double> pt;
        MSGPACK_DEFINE(ang, oct, pt);
    };

    class Cameras
    {
    public:
        p20Lite P20Lite;
        MSGPACK_DEFINE(P20Lite);
    };

    class Keyframe
    {
    public:
        string cam;
        long depth_thr;
        std::vector<long> depths;
        std::vector<long> descs;
        std::vector<Keypt> keypts;
        std::vector<long> lm_ids;
        std::vector<int> loop_edges; /////////////////////////////////
        long n_keypts;
        long n_scale_levels;
        std::vector<double> rot_cw;
        double scale_factor;
        std::vector<long> span_children;
        long span_parent;
        long src_frm_id;
        std::vector<double> trans_cw;
        double ts;
        std::vector<std::vector<double>> undists;
        std::vector<long> x_rights;

        MSGPACK_DEFINE(cam, depth_thr, depths, descs, keypts, lm_ids, loop_edges, n_keypts, n_scale_levels, rot_cw, scale_factor, span_children, span_parent, src_frm_id, trans_cw, ts, undists, x_rights);
    };

    class Landmark
    {
    public:
        long keyfrm1;
        long n_fnd;
        long n_vis;
        std::vector<double> pos_w;
        long ref_keyfrm;
        MSGPACK_DEFINE(keyfrm1, n_fnd, n_vis, pos_w, ref_keyfrm);
    };

    class Map
    {
    public:
        Cameras cameras;
        long frame_next_id;
        long keyframe_next_id;
        //std::vector<Keyframe> keyframes;
        std::string keyframes;
        long landmark_next_id;
        //std::vector<Landmark> landmarks;
        std::string landmarks;

        MSGPACK_DEFINE(cameras, frame_next_id, keyframe_next_id, keyframes, landmark_next_id, landmarks);
    };

} // namespace data

#endif