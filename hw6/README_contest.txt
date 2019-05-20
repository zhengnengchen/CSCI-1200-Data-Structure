HOMEWORK 6: BATTLESHIP CONTEST


NAME:  Zhengneng Chen



COLLABORATORS AND OTHER RESOURCES:
None



DESCRIPTION OF ANY PERFORMANCE IMPROVEMENTS/OPTIMIZATIONS:
(please be concise!)

I use vector of strings to represent a solution. Hence, to check if a solution
has existed, the performance is improved by using compare string instead of
compare each char using loop. Each non-submarine ship can be put into two
direction. Hence, to prune as much invalid branches as possible, I use two
similar double for loop to check horizontal and vertical direction separately.
Lots of branches are pruned using terminating conditions of for loops. Also, I
check if there are at least one space along where ship is put. If I met a zero
space, I skip to nect non-zero space to search.



DESCRIBE INTERESTING NEW PUZZLES YOU CREATED:



SUMMARY OF YOUR PERFORMANCE ON ALL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.

puzzle_sample.txt:            2 solutions;    0.011s; 0.021s
puzzle_sample_constraint.txt: 1 solution;     0.023s; 0.020s
puzzle_sample_unknown.txt:    2 solutions;    0.020s; 0.019s
puzzle1.txt:                  1 solution;     0.021s; 0.020s
puzzle2.txt:                  1 solution;     0.022s; 0.020s
puzzle3.txt:                  1 solution;     0.022s; 0.019s
puzzle4.txt:                  1 solution;     0.022s; 0.020s
puzzle4_unknowns.txt:         1 solutions;    0.020s; 0.020s
puzzle5.txt:                  2 solutions;    0.021s; 0.020s
puzzle6.txt:                  24 solutions;   0.022s; 0.021s
puzzle6_unknowns.txt:         24 solutions;   0.021s; 0.025s
puzzle7.txt:                  14 solutions;   0.022s; 0.021s
puzzle8.txt:                  2 solutions;    0.022s; 0.060s
puzzle9.txt:                  152 solutions;  0.023s; 0.170s
puzzle9_constraints.txt:      1 solution;     0.062s; 0.063s
puzzle10.txt:                 3754 solutions; 0.023s; 12.510s
puzzle10_constraints.txt:     1 solutions;    0.023s; 0.125s
