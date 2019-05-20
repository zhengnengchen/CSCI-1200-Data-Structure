HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  Zhengneng Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None. cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out
b: The number of bits required to represent the largest ID
i: The number of decimal digits required to represent the largest ID

loadConnections(): O(m). I use a while loop to read in connects. While loop is
                   executed m times to read in m connections which represents m
                   edges of graph.

loadLocations(): O(l). l lines with l users with a location. I still use while
                 loop to read in locations one line/user a time.

printAllUsersWithinDistance(): O(l+p) since I visit each user with a location
                               except for starting user itself whici implies a
                               O(l) complexity and to print out results to
                               outfile, it takes a O(p) operation to visit each
                               result.

printDegreesHistogram(): O(d+p) since each pair in adj_lists is visited once to
                         calculate the histogram of occurances which implies
                         O(d) and to print out, we do a O(p) on visiting the map
                         we used to restore results.

printDegreesOfAll(): O(d) since adj_lists is sorted with respect to key/id
                     implicitly and I visit each pair in adj_lists.

printFriendsWithDegree(): O(m/d*log(d)+p). We look up each friend of starting
                          user that in average, the number of friends of an
                          arbitraty user is in O(m/d). Besides that, for each
                          friend, we do searchs in adj_lists to find degree of
                          each friend which implies O(log(d)). Finally, we
                          traverse the map used to restore results to print out
                          to outfile which implies O(p).

printFriendsWithinDistance(): O(m/d*log(l)+p). Similarly, first we look up each
                              friend of starting user that in average, the
                              number of friends of an arbitraty user is in
                              O(m/d). Next, do searchs in locations to find
                              degree of each friend which implies O(log(l)).
                              This gives us O(m/d*log(l)). Finally, we are going
                              to traverse the map used to restore results to
                              print out to outfile which implies O(p).

printUsersWithinIDRange(): O(p). According to the specification of function, if
                           there are p users that are going to be printed out,
                           we can at most do p times operator++/-- operations.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






