#pragma once

class ScoreManager{
public:
    using ScorePoints = int;
    ScoreManager(ScorePoints initial_score);
    ScorePoints score() const;
    void add_points(ScorePoints sp);
private:
    ScorePoints score_points;
};