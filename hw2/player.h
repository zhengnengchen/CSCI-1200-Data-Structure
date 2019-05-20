#ifndef __player_h_
#define __player_h_

#include <string>
#include <vector>

class Player {
public:
    // Constructor
    Player(const std::string& fname = "", const std::string& lname = "");
    
    // Accessors
    const std::string& getFirstName() const { return first_name; }
    const std::string& getLastName() const { return last_name; }
    const std::vector<int>& getData() const { return data; }
    const std::vector<std::string>& getStringData() const { return string_data; }
    const std::vector<int>& getScores() const { return scores; }
    const std::vector<int>& getAccumulativeScores() const { return accumulative_scores; }
    const int& getTotalScore() const { return total_score; }
    // Accessors for custom
    const int& getTotalStrike() const { return total_strikes; }
    const int& getTotalSpare() const { return total_spares; }
    const int& getStrikeBonus() const { return strike_bonus; }
    const int& getSpareBonus() const { return spare_bonus; }
    
    // Modifiers
    void setFirstName(std::string f_name) { first_name = f_name; }
    void setLastName(std::string l_name) { last_name = l_name; }
    void append_data(const int score, const std::string input);
    
    // other member functions
    void calculate_scores();
private:
    std::string first_name, last_name;
    std::vector<int> data;
    std::vector<std::string> string_data;
    std::vector<int> scores;
    std::vector<int> accumulative_scores;
    int total_score;
    // private variables for custom
    int total_strikes, total_spares, strike_bonus, spare_bonus;
};

// Two non-member functions used for sorting in standard mode
bool name_sort(const Player& p1, const Player& p2);
bool score_sort(const Player& p1, const Player& p2);

// 4 sort functions for custom
bool strike_sort(const Player& p1, const Player& p2);
bool strike_and_spare_sort(const Player& p1, const Player& p2);
bool avg_strike_bonus_sort(const Player& p1, const Player& p2);
bool avg_spare_bonus_sort(const Player& p1, const Player& p2);

#endif
