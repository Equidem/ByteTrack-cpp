#pragma once

#include <ByteTrack/STrack.h>
#include <ByteTrack/lapjv.h>
#include <ByteTrack/Object.h>

namespace byte_track
{
class BYTETracker
{
public:
    BYTETracker(int frame_rate = 30, int track_buffer = 30);
    ~BYTETracker();

    std::vector<STrack> update(const std::vector<Object>& objects);
    cv::Scalar get_color(int idx);

private:
    std::vector<STrack*> joint_stracks(std::vector<STrack*> &tlista, std::vector<STrack> &tlistb);
    std::vector<STrack> joint_stracks(std::vector<STrack> &tlista, std::vector<STrack> &tlistb);

    std::vector<STrack> sub_stracks(std::vector<STrack> &tlista, std::vector<STrack> &tlistb);
    void remove_duplicate_stracks(std::vector<STrack> &resa, std::vector<STrack> &resb, std::vector<STrack> &stracksa, std::vector<STrack> &stracksb);

    void linear_assignment(std::vector<std::vector<float> > &cost_matrix, int cost_matrix_size, int cost_matrix_size_size, float thresh,
        std::vector<std::vector<int> > &matches, std::vector<int> &unmatched_a, std::vector<int> &unmatched_b);
    std::vector<std::vector<float> > iou_distance(std::vector<STrack*> &atracks, std::vector<STrack> &btracks, int &dist_size, int &dist_size_size);
    std::vector<std::vector<float> > iou_distance(std::vector<STrack> &atracks, std::vector<STrack> &btracks);
    std::vector<std::vector<float> > ious(std::vector<std::vector<float> > &atlbrs, std::vector<std::vector<float> > &btlbrs);

    double lapjv(const std::vector<std::vector<float> > &cost, std::vector<int> &rowsol, std::vector<int> &colsol, 
        bool extend_cost = false, float cost_limit = LONG_MAX, bool return_cost = true);

private:
    float track_thresh_;
    float high_thresh_;
    float match_thresh_;
    int frame_id_;
    int max_time_lost_;

    std::vector<STrack> tracked_stracks_;
    std::vector<STrack> lost_stracks_;
    std::vector<STrack> removed_stracks_;
    KalmanFilter kalman_filter_;
};
}