HOMEWORK 8: B+ TREES


NAME:  Zhengneng Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?
I use lldb to ckech frame variable since when I implement B+ tree, I met some
assertion failures. Also, after I finished implementation, Dr. Memory help me
figure out a little bug in destructor. For testing "corner case", I tested
inserting to leftmost and rightmost and in middle of tree. Besides different
T value, I checked insertion in tree with different layers. Further more, I
checked parents of non-root node in a multiple layers' tree.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

