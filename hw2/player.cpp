#include "player.h"
#include <cassert>

Player::Player(const std::string& fname, const std::string& lname) {
    first_name = fname;
    last_name = lname;
}

// Repeating work for calling push_back() to append data into private variables
void Player::append_data(const int score,
                         const std::string input) {
    data.push_back(score);
    if (score == 10) string_data.push_back("X");
    else if (score == 0) string_data.push_back("-");
    else string_data.push_back(input);
}

// During processing each one of data, I calculate scores for each frame and
// saved into scores vector. Then the accumulative scores are what we needed to
// print out on scoresheet which are calculated by the sum of first n terms. The
// last one of accumulative scores is the final total score.
// Modified: Added features to calculate interesting things for custom mode.
void Player::calculate_scores() {
    int frame_count = 0, spare = 0, strike = 0;
    // Variables added for custom
    int strike_count = 0, spare_count = 0, strike_bonus_count = 0, spare_bonus_count = 0;
    // Process scores for each frame
    for (int i = 0; i < data.size(); ++i) {
        // First, count bonus for previous frame
        if (spare == 1) {
            scores[scores.size() - 1] += data[i];
            spare_bonus_count += data[i]; // custom
            spare = 0;
        }
        if (strike == 1) {
            scores[scores.size() - 1] += data[i] + data[i+1];
            strike_bonus_count += data[i] + data[i+1]; // custom
            strike = 0;
        }
        // Then process each data for each frame
        int score_count = 0;
        if (frame_count == 9 && data[i] == 10) {
            strike_count += 1; // custom
            // strike at 10th frame => 2 bonus throw
            score_count += data[i];
            i += 1;
            if (data[i] == 10) strike_count += 1; // custom
            score_count += data[i];
            strike_bonus_count += data[i]; // custom
            i += 1;
            if (data[i] == 10) strike_count += 1; // custom
            score_count += data[i];
            strike_bonus_count += data[i]; // custom
            scores.push_back(score_count);
        } else if (frame_count == 9) {
            score_count += data[i];
            i += 1;
            if (score_count + data[i] == 10) {
                spare_count += 1; // custom
                // Spare at 10th frame => 1 bonus throw
                string_data[i] = "/";
                score_count += data[i];
                i += 1;
                score_count += data[i];
                spare_bonus_count += data[i]; // custom
                // No strike nor spare at 10th frame => 2 throw in total
            } else score_count += data[i];
            scores.push_back(score_count);
        } else if (data[i] == 10) {
            strike_count += 1; // custom
            // One throw for strike at first 9 frames
            score_count += 10;
            scores.push_back(score_count);
            strike = 1;
        } else {
            // Not a strike at first 9 frames => 2 throws
            score_count += data[i];
            i += 1;
            // Spare
            if (score_count + data[i] == 10) {
                spare_count += 1; // custom
                string_data[i] = "/";
                spare = 1;
            }
            score_count += data[i];
            scores.push_back(score_count);
        }
        frame_count += 1;
    }
    
    // Accumulate scores to output
    accumulative_scores = scores;
    for (int i = 0; i < accumulative_scores.size(); ++i) {
        for (int j = 0; j < i; ++j) accumulative_scores[i] += scores[j];
    }
    
    // total score is the last score of accumulative ones
    total_score = accumulative_scores[accumulative_scores.size() - 1];
    
    // strike and spare statistics for custom
    total_strikes = strike_count;
    total_spares = spare_count;
    strike_bonus = strike_bonus_count;
    spare_bonus = spare_bonus_count;
}

// 2 sort functions for scoresheet and total score ranking
bool name_sort(const Player& p1, const Player& p2) {
    return (p1.getLastName() < p2.getLastName()) ||
           (p1.getLastName() == p2.getLastName() &&
            p1.getFirstName() < p2.getFirstName());
}

bool score_sort(const Player& p1, const Player& p2) {
    return p1.getTotalScore() > p2.getTotalScore();
}

// 4 sort functions for custom
bool strike_sort(const Player& p1, const Player& p2) {
    return p1.getTotalStrike() > p2.getTotalStrike();
}

bool strike_and_spare_sort(const Player& p1, const Player& p2) {
    return (p1.getTotalStrike() + p1.getTotalSpare()) >
           (p2.getTotalStrike() + p2.getTotalSpare());
}

bool avg_strike_bonus_sort(const Player& p1, const Player& p2) {
    if (p1.getTotalStrike() == 0) return false;
    if (p2.getTotalStrike() == 0) return true;
    return ((float)p1.getStrikeBonus()/(float)p1.getTotalStrike()) >
           ((float)p2.getStrikeBonus()/(float)p2.getTotalStrike());
}

bool avg_spare_bonus_sort(const Player& p1, const Player& p2) {
    if (p1.getTotalSpare() == 0) return false;
    if (p2.getTotalSpare() == 0) return true;
    return ((float)p1.getSpareBonus() / (float)p1.getTotalSpare()) >
           ((float)p2.getSpareBonus() / (float)p2.getTotalSpare());
}
