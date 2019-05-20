HOMEWORK 5: LINKED TRAIN CARS


NAME:  Zhengneng Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritize between these goals.  Describe your
prioritization and your implementation.

Practically, we are supposed to ship as much as freights with as less engine as
possible. The main problem railway companies often meet is the lack of shipping
capacity. This problem is caused by the lack of engines and the overflow of
freights. Thus, to optimize my algorithm, I would target on shipping most
freights with fewest number of engines used. If this target is achieved, along
with the limit of maximum number of cars of one train, fewest resulting trains
used is followed as a result. Train speed is not targeted since almost all
railways have both minimum and maximum speed limit so that one single train
would not block the whole line of railway nor break safety rules.

Thus I would improve my algorithm by following steps:
1. Building a series of trains with just one engine. Then add freight which is
   heaviest among freights and does not break minimum speed limitation one by
   one to them.
2. A lot of trains would be shorter than maximum number of cars per train. So I
   linking those too short trains together.
3. Now, surplus capacities are combined and might be able to fit remaining
   freights. Hence, check each freights with each train. If fit, then add to it.


DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeping)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritize between these goals.  Describe your prioritization and your
implementation.

My first priority is the smallest values for average distance to dining and
the largest values for closest engine to sleeping. Meanwhile, total costs would
be optimal that all cars are draged in least distances. In order to find the
largest values for closest engine to sleeping, all engines are put on one side
of a train. Thus my implementation can handle the cases that there are more than
2 engines. My implementation is an extension of Separate() instead of a
modification in following steps:
1. Before calling to Separate(), extracting all dining and sleeping cars from
   train.
2. Calling Separate() to separate train into 2 trains in an optimal way.
3. If there exists any sleeping cars, moving engines to one side and sleeping
   cars to the other side of train.
4. If there exists any dining cars, align them in the middle of passenger cars
   evenly.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


