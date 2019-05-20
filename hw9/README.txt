HOMEWORK 9: MINIBLAST


NAME:  Zhengneng Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Lab 11. cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


HASH FUNCTION DESCRIPTION
I used the hash function used in lab 11.


HASH TABLE IMPLEMENTATION
My implementation of hash table is a vector of pairs. Each pair is consisting of
a key(string) and a list of key's position in data.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?
I used a string to store the whole genome sequence which implies a O(L) memory
usage. If key size is k, there are at most L-K different keys. Each key has p
different locations. Then the table takes O(L-k) to save keys and O((L-k)*p) to
save all lists. The whole hash table needs O((L-k)*(p+1))=O((L-k)*p) of memory.
In total, the moemory usage is O(L+(L-k)*p)=O((L-k)*p).


What is the order notation for performance (running time) of each of
the commands?
1. "genome" command ask us to save the whole sequence which is O(L).
2/3. "occupancy" and "table_size" commands call modifier functions to set
private member variable before table is build. Hence is O(1).
4. "kmer" command is followed by table building. Insert() function is called
O(L-k) times. Each call need to hash the key which is O(1), find suitable
position which is O(1), and append position to the end of position which is also
O(1). Cost of insert is O(1). Hence, the performance of building hash table is
O(L-k).
5. "query" command call getPosition() function once. getPosition() using key's
hash value to find associating list in hash table. Calculating hash value is
O(1). Finding in hash table is also O(1). Results returned give us p different
location in data sequence to look up. Each lookup is linear comparison. Hence
the performance of "query" is O(p*q).


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


