#include "game/example_fun/snake/score_manager.hpp"

ScoreManager::ScoreManager(ScorePoints initial_points):
    score_points(initial_points){}

ScoreManager::ScorePoints ScoreManager::score() const{
    return score_points;
}

void ScoreManager::add_points(ScorePoints sp){
    score_points += sp;
}