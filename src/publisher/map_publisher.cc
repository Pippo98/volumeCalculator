#include "map_publisher.h"
#include "bits/stdc++.h"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include "../ann/ANN/ANN.h"

using namespace Eigen;

#include <typeinfo>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

namespace publish
{
    void map_publisher::load_json()
    {
        std::ifstream buffer("/home/filippo/Desktop/test1/Webcam/map.msg", std::ifstream::in);
        // std::ifstream buffer("/home/filippo/Desktop/test1/cellphoneTest1/map_1.msg", std::ifstream::in);

        map_j = nlohmann::json::from_msgpack(buffer);

        load_landmarks();
        load_points();
        load_near_points();
    }

    void map_publisher::load_points()
    {
        vector<quicktype::Vec3_t> points;
        for (auto lm : landmarks_)
        {
            points.push_back(lm.pos_w * 10);
        }
        points_ = points;
    }

    void map_publisher::load_landmarks()
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
        landmarks_ = landmarks;
    }
    std::vector<quicktype::Vec3_t> map_publisher::get_points()
    {
        return points_;
    }

    std::vector<quicktype::Landmark> map_publisher::get_landmarks()
    {
        std::vector<quicktype::Landmark> landmarks;
        for (auto lm : landmarks_)
        {
            landmarks.push_back(lm);
        }
        return landmarks;
    }

    void map_publisher::load_near_points()
    {

        int k = 10;
        int dim = 3;
        int maxPts = points_.size();

        int nPts = points_.size(); // actual number of data points
        ANNpointArray dataPts;     // data points

        ANNidxArray nnIdx;                  // near neighbor indices
        ANNdistArray dists;                 // near neighbor distances
        ANNkd_tree *kdTree;                 // search structure
        dataPts = annAllocPts(maxPts, dim); // allocate data points

        for (int i = 0; i < maxPts; i++)
        {
            ANNpoint buff;
            buff = annAllocPt(dim);
            buff[0] = points_[i][0];
            buff[1] = points_[i][1];
            buff[2] = points_[i][2];
            dataPts[i] = buff;
        }

        kdTree = new ANNkd_tree( // build search structure
            dataPts,             // the data points
            nPts,                // number of points
            dim);                // dimension of space

        cout << "originalPoints size: " << points_.size() << " treePoints: " << maxPts << "\n";

        for (int i = 0; i < maxPts; i++)
        {                              // read query points
            ANNpoint queryPt;          // query point
            queryPt = annAllocPt(dim); // allocate query point
            queryPt = dataPts[i];

            nnIdx = new ANNidx[k];  // allocate near neigh indices
            dists = new ANNdist[k]; // allocate near neighbor dists

            kdTree->annkSearch( // search
                queryPt,        // query point
                k,              // number of near neighbors
                nnIdx,          // nearest neighbors (returned)
                dists);         // distance (returned)

            vector<quicktype::Vec3_t> nr_points;
            for (int j = 0; j < k; j++)
            { // print summary
                //dists[j] = sqrt(dists[j]); // unsquare distance

                if (j > 0)
                    if (dists[j] > dists[0] * 3)
                        continue;

                // if (dists[j] > 1)
                // {
                //     continue;
                // }

                quicktype::Vec3_t bff;
                bff[0] = dataPts[nnIdx[j]][0];
                bff[1] = dataPts[nnIdx[j]][1];
                bff[2] = dataPts[nnIdx[j]][2];
                nr_points.push_back(bff);
            }

            if (nr_points.size() == 0)
                continue;

            quicktype::Vec3_t query_point;
            query_point[0] = queryPt[0];
            query_point[1] = queryPt[1];
            query_point[2] = queryPt[2];
            nr_points_.points.push_back(std::make_tuple(query_point, nr_points));
        }
    }

    quicktype::NearPoints map_publisher::get_near_points()
    {
        return nr_points_;
    }

} // namespace publish