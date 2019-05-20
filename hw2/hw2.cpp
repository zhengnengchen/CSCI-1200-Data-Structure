#include "player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

// Repeating work to call push_back() for two member variables, data and
// string_data.
void process_data(std::ifstream& in_str,
                  int& score,
                  std::string& input,
                  Player& player) {
    in_str >> input;
    score = atoi(input.c_str());
    player.append_data(score, input);
}

// Compare each player's name to find the longest one and return it's length to
// set the width of score sheet.
int longest_name(const std::vector<Player>& players) {
    int longest_length = 0;
    for (int i = 0; i < players.size(); ++i) {
        const std::string first_name = players[i].getFirstName();
        const std::string last_name = players[i].getLastName();
        int name_length = first_name.size() + last_name.size() + 1;
        longest_length = std::max(name_length, longest_length);
    }
    return longest_length;
}

// The function is used to draw scoresheet
void draw_table(const std::vector<Player>& players,
                std::ofstream& out_str) {
    int name_length = longest_name(players);
    int line_length = 66 + name_length;
    const std::string dash_line(line_length, '-');
    
    out_str << dash_line << std::endl;
    for (int i = 0; i < players.size(); ++i) {
        // First column of scoresheet is player's name
        out_str << "| " << players[i].getFirstName();
        out_str << ' ' << players[i].getLastName();
        int first_name_size = players[i].getFirstName().size();
        int last_name_size = players[i].getLastName().size();
        int name_size = first_name_size + last_name_size + 1;
        out_str << std::string(name_length - name_size, ' ') << " |";
        
        // Next 10 columns are for 10 frames
        int frame_count = 0;
        for (int j = 0; j < players[i].getStringData().size(); ++j) {
            if (frame_count == 9 && players[i].getScores()[frame_count] >= 10) {
                // strike or spare at 10th frame => 3 throws
                out_str << ' ' << players[i].getStringData()[j];
                j += 1;
                out_str << ' ' << players[i].getStringData()[j];
                j += 1;
                out_str << ' ' << players[i].getStringData()[j];
            } else if (frame_count == 9) {
                // no strike nor spare at 10th frame => 2 throws
                out_str << ' ' << players[i].getStringData()[j];
                j += 1;
                out_str << ' ' << players[i].getStringData()[j] << "  ";
            } else if (players[i].getStringData()[j] == "X") {
                // Strike at first 9 frames => 1 throw
                out_str << "   " << players[i].getStringData()[j];
            } else {
                // No strike at first 9 frames => 2 throws
                out_str << ' ' << players[i].getStringData()[j];
                j += 1;
                out_str << ' ' << players[i].getStringData()[j];
            }
            out_str << " |";
            frame_count += 1;
        }
        
        // Second row are for accumulative scores
        out_str << std::endl << "| " << std::string(name_length, ' ') << " |";
        for (int j = 0; j < players[i].getAccumulativeScores().size() - 1; ++j) {
            out_str << std::setfill(' ') << std::setw(4);
            out_str << players[i].getAccumulativeScores()[j] << " |";
        }
        out_str << std::setfill(' ') << std::setw(6);
        int last_one = players[i].getAccumulativeScores().size() - 1;
        out_str << players[i].getAccumulativeScores()[last_one] << " |";
        out_str << std::endl << dash_line << std::endl;
    }
}

// The function is used to print out players ranked by their total scores.
// Modified: add mode argument for custom. Using different argument, avoid
//           repeat work when output players with some ranking key.
void list_sort(const std::vector<Player>& players,
               std::ofstream& out_str,
               const std::string& mode = "total score") {
    int name_length = longest_name(players);
    for (int i = 0; i < players.size(); ++i) {
        out_str << players[i].getFirstName() << ' ' << players[i].getLastName();
        int first_name_size = players[i].getFirstName().size();
        int last_name_size = players[i].getLastName().size();
        int name_size = first_name_size + last_name_size + 1;
        out_str << std::string(name_length - name_size + 2, ' ');
        if (mode == std::string("total score")) {
            out_str << std::setw(3) << players[i].getTotalScore() << std::endl;
        } else if (mode == std::string("total strike")) {
            out_str << std::setw(8) << players[i].getTotalStrike() << std::endl;
        } else if (mode == std::string("total strike and spare")) {
            int total_strike_and_spare = players[i].getTotalStrike() +
                                         players[i].getTotalSpare();
            out_str << std::setw(8) << total_strike_and_spare << std::endl;
        } else if (mode == std::string("avg strike bonus")) {
            float avg_strike_bonus;
            if (players[i].getTotalStrike() == 0) avg_strike_bonus = 0;
            else avg_strike_bonus = (float)players[i].getStrikeBonus()/
                                    (float)players[i].getTotalStrike();
            out_str << std::setw(8) << avg_strike_bonus << std::endl;
        } else {
            float avg_spare_bonus;
            if (players[i].getTotalSpare() == 0) avg_spare_bonus = 0;
            else avg_spare_bonus = (float)players[i].getStrikeBonus()/
                                    (float)players[i].getTotalStrike();
            out_str << std::setw(8) << avg_spare_bonus << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // Check argument number, create I/O file descriptor and read in file into a
    // vector of word strings
    if (argc != 4) {
        std::cerr << "Need 3 arguments" << std::endl;
        return 1;
    }
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Cannot open file " << std::string(argv[1]) << " to read" << std::endl;
        return 1;
    }
    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std::cerr << "Cannot open file " << std::string(argv[2]) << " to write" << std::endl;
        return 1;
    }
    
    std::vector<Player> players;
    std::string input;
    // Read in all data into a vector of Player class and calculate scores for
    // each player
    while (in_str >> input) {
        // First two inputs are name of player
        Player player;
        player.setFirstName(input);
        in_str >> input;
        player.setLastName(input);
        // Then 10 frames of game
        int frame_count = 0;
        while (frame_count < 10) {
            int score = 0;
            process_data(in_str, score, input, player);
            if (frame_count == 9 && score == 10) {
                // Strike at 10th frame => 3 throws
                process_data(in_str, score, input, player);
                process_data(in_str, score, input, player);
            } else if (frame_count == 9) {
                int score_count = score;
                process_data(in_str, score, input, player);
                // Spare at 10th frame => 3 throws
                if (score_count + score == 10)
                    process_data(in_str, score, input, player);
            } else if (score < 10) {
                // Two throw for not strike
                process_data(in_str, score, input, player);
            }
            frame_count += 1;
        }
        // After read in 1 player's data. Call member function to calculate scores
        player.calculate_scores();
        players.push_back(player);
    }
    
    if (std::string(argv[3]) == std::string("standard")) {
        std::sort(players.begin(), players.end(), name_sort);
        draw_table(players, out_str);
        out_str << std::endl;
        std::sort(players.begin(), players.end(), score_sort);
        list_sort(players, out_str);
    } else if (std::string(argv[3]) == std::string("custom")) {
        std::sort(players.begin(), players.end(), strike_sort);
        out_str << "Rank based on total strikes:" << std::endl;
        list_sort(players, out_str, std::string("total strike"));
        out_str << std::endl;
        std::sort(players.begin(), players.end(), strike_and_spare_sort);
        out_str << "Rank based on total strikes and spares:" << std::endl;
        list_sort(players, out_str, std::string("total strike and spare"));
        out_str << std::endl;
        std::sort(players.begin(), players.end(), avg_strike_bonus_sort);
        out_str << "Rank based on average bonus gathered after strikes:" << std::endl;
        list_sort(players, out_str, std::string("avg strike bonus"));
        out_str << std::endl;
        std::sort(players.begin(), players.end(), avg_spare_bonus_sort);
        out_str << "Rank based on average bonus gathered after spares:" << std::endl;
        list_sort(players, out_str, std::string("avg spare bonus"));
    } else {
        std::cerr << "wrong 4th argument" << std::endl;
        return 1;
    }
    
    return 0;
}
