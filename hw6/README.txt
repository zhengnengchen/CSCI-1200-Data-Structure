HOMEWORK 6: BATTLESHIP RECURSION


NAME:  Zhengneng Chen



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None.
cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  40



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of ships (s)? 
The total number of occupied cells (o) or open water (w)? 
The number of constraints (c)? 
The number of unknown sums (u) or unspecified ship types (t)? 
Etc. 

My recursion is to check each position on board for each ships from longest ship
to shortest ship. Once a position is capable of putting that ship, adding the
ship on that position and call recursion function to check next ship. Thus main
factors affecting the performance of my algorithm would be dimensions of the
board and the number of ships. When checking if a position is capable of putting
ship on it, I check if all positions where ship is projected on board are open
water as well as adjacent cells. Thus the length of each ship (l) matters. Thus
the overall order notation of my algorithm is O(whsl). However, my algorithm
saves all validating solutions into a vector to make sure future solutions don't
contain repeating solutions. Thus the number of solutions matters too.



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.

puzzle_sample.txt:            2 solutions;    0.102s; 0.107s
puzzle_sample_constraint.txt: 1 solution;     0.097s; 0.097s
puzzle_sample_unknown.txt:    2 solutions;    0.005s; 0.006s
puzzle1.txt:                  1 solution;     0.098s; 0.096s
puzzle2.txt:                  1 solution;     0.098s; 0.109s
puzzle3.txt:                  1 solution;     0.100s; 0.112s
puzzle4.txt:                  1 solution;     0.020s; 0.102s
puzzle4_unknowns.txt:         1 solutions;    0.005s; 0.023s
puzzle5.txt:                  2 solutions;    0.023s; 0.107s
puzzle6.txt:                  24 solutions;   0.098s; 0.143s
puzzle6_unknowns.txt:         24 solutions;   0.064s; 0.014s
puzzle7.txt:                  14 solutions;   0.005s; 0.017s
puzzle8.txt:                  2 solutions;    0.007s; 0.260s
puzzle9.txt:                  152 solutions;  0.018s; 0.735s
puzzle9_constraints.txt:      1 solution;     0.205s; 0.296s
puzzle10.txt:                 3754 solutions; 0.104s; 56.865s
puzzle10_constraints.txt:     1 solutions;    0.023s; 0.520s




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


