// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <algorithm>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//


// =============================================================================
// These are simulated double linked list member functions to manipulate a
// double linked list like we did to std::list.

// First, implement Push_back function which is used in SimpleTrainTest but not
// defined. This function takes two arguments with the first argument as a
// pointer to a TrainCar list and append the second argument to the end of list.
void PushBack(TrainCar*& train, TrainCar *car) {
    if (car == NULL) return;
    car->next = NULL;
    // TrainCar list is empty: car is the only car of train
    if (train == NULL) {
        train = car;
        train->prev = NULL;
    } else {
    // List is not empty: Find the last car and modify 2 pointers
        TrainCar* ptr = train;
        while (ptr != NULL) {
            if (ptr->next == NULL) break;
            else ptr = ptr->next;
        }
        ptr->next = car;
        car->prev = ptr;
    }
}

// Used in Separate(). Simulating push_front() in std::list that this function
// will also push element pointed by car to the front of list.
void PushFront(TrainCar*& train, TrainCar*  car) {
    if (train == NULL) {
    // TrainCar list is empty: car is the only car of train
        train = car;
        train->next = train->prev = NULL;
    } else {
    // List is not empty: modify 2 pointers of head of list
        train->prev = car;
        car->prev = NULL;
        car->next = train;
        train = train->prev;
    }
}

// This helper function is used in ShipFreight() and Separate() to remove the
// last element from list and a pointer pointing to this element is returned so
// that we can do something with the element just deleted from list.
TrainCar* PopBack(TrainCar*& train) {
    TrainCar* ptr = train;
    // If list is empty, do nothing and return a NULL pointer
    if (ptr == NULL) return NULL;
    else if (ptr->next == NULL) {
        // If there is only 1 element in list, no need to modify prev and next
        // pointers.
        train = NULL;
        return ptr;
    }
    // Otherwise, move pointer to last element
    while (ptr->next != NULL) ptr = ptr->next;
    // Modify 2 pointers so that the second last element become new tail
    ptr->prev->next = NULL;
    ptr->prev = NULL;
    return ptr;
}

// Similar to PopBack(), this function removes the last element in list and
// return a pointer pointing to the removed element.
TrainCar* PopFront(TrainCar*& train) {
    TrainCar* ptr = train;
    // If list is empty, do nothing and return a NULL pointer
    if (train == NULL) return NULL;
    else if (train->next == NULL) {
        // If there is only 1 element in list, no need to modify prev and next
        // pointers.
        train = NULL;
        return ptr;
    }
    // Otherwise, move pointer to next element
    train = train->next;
    // Modify 2 pointers so that the second element become new head
    train->prev = NULL;
    ptr->next = NULL;
    return ptr;
}

// When moving a engine car from a train to another train, PopFront() and
// Popback() are not enoughed. Usually, we need remove a element from the middle
// of a list. Thus I implement this helper function to do that. Removed element
// is returned by a pointer pointing to it. The second argument, a pointer
// pointing to the position where element is to be removed, is moved a step
// forward.
TrainCar* Erase(TrainCar*& train, TrainCar*& ptr) {
    // Do nothing if train is empty
    if (train == NULL || ptr == NULL) return NULL;
    TrainCar *tmp = ptr;
    // If there is only 1 elements in train, train would become empty and
    // ptr is supposed to set to NULL.
    if (ptr->prev == NULL && ptr->next == NULL) train = NULL;
    else if (ptr->next == NULL) ptr->prev->next = NULL; // Tail
    else if (ptr->prev == NULL) {
        // Head: Modify 1 pointer and set train and ptr to new head.
        ptr->next->prev = NULL;
        train = train->next;
    } else {
        // If ptr is not head nor tail of list, we are going to modify 2 pointers
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }
    ptr = ptr->next;
    // Make sure tmp is not connect to anything so that no unexpectted things
    // would happen.
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}

// This function is mainly used in SeparateComfort(). Element pointed by car
// will be inserted into train in front of ptr. ptr keep pointing to the
// position where it points to but train might change if ptr points to train.
// That is, ptr points to the head of list. In this case, insertion means a
// push_front() operation.
TrainCar* Insert(TrainCar*& train, TrainCar*& ptr, TrainCar* car) {
    if (car == NULL) return NULL; // Cannot add if car if NULL
    else if (train == NULL && ptr == NULL) { // Empty list.
        // My implementation is different from std::list that insert() words for
        // a empty list.
        car->prev = NULL;
        car->next = NULL;
        train = ptr = car;
    } else if (ptr == NULL) return NULL; // ptr is pointed to a illegal memory position
    else if (train == NULL) return NULL; // ptr is not pointed to train
    else if (train == ptr) { // ptr points to head of list
        car->prev = NULL;
        car->next = ptr;
        ptr->prev = car;
        train = car;
    } else { // ptr points to the middle of list
        car->prev = ptr->prev;
        car->next = ptr;
        ptr->prev->next = car;
        ptr->prev = car;
    }
    return ptr;
}

// This function is used in SimpleTrainTest() to delete dynamically allocated
// memory of TrainCar list.
void DeleteAllCars(TrainCar*& train) {
    // If list is empty, no need to delete
    if (train == NULL) return;
    
    TrainCar *ptr = train;
    // Before delete, move pointer to next one so that deletion would not affect
    // the usage of next pointer.
    while (ptr->next != NULL) {
        ptr = ptr->next;
        delete ptr->prev;
    }
    delete ptr;
    train = NULL;
}
// =============================================================================


// =============================================================================
// 4 Helper functions used in PrintTrain().

// This function is used to calculate a series of stats by iterating the whole
// list. Arguments are a pointer to TrainCar list and stats that are passed into
// function by reference. Thus we can directly modify thes stats.
void TotalWeightAndCountCars(TrainCar *train,
                             int& total_weight,
                             int& num_engines,
                             int& num_freight_cars,
                             int& num_passenger_cars,
                             int& num_dining_cars,
                             int& num_sleeping_cars) {
    TrainCar *ptr = train;
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    while (ptr != NULL) {
        total_weight += ptr->getWeight();
        if (ptr->isEngine()) num_engines += 1;
        else if (ptr->isFreightCar()) num_freight_cars += 1;
        else if (ptr->isPassengerCar()) num_passenger_cars += 1;
        else if (ptr->isDiningCar()) num_dining_cars += 1;
        else num_sleeping_cars += 1;
        ptr = ptr->next;
    }
}

// This function is used to calculate train speed and return this speed in float
// The equation used is the one on our HW's pdf. The only argument taken is a
// pointer to TrainCar list.
float CalculateSpeed(TrainCar *train, TrainCar *car) {
    // 2 Variables used to count hp and weight
    int total_hp = 0;
    int total_weight = 0;
    // Iterating whole list to count total horsepower and total weight
    TrainCar *ptr = train;
    while (ptr != NULL) {
        total_weight += ptr->getWeight();
        if (ptr->isEngine()) total_hp += 3000;
        ptr = ptr->next;
    }
    // If car is not NULL, we are going to calculate the speed of train if car
    // is linked to it.
    if (car != NULL) total_weight += car->getWeight();
    // calculate speed using equation provided in hw pdf.
    return (float)total_hp * 9.375 / total_weight;
}

float AverageDistanceToDiningCar(TrainCar *train) {
    int total_dist = 0;
    int total_passenger_car = 0;
    int total_dining_car = 0;
    TrainCar *ptr = train;
    while (ptr != NULL) {
        if (ptr->isPassengerCar()) {
            total_passenger_car += 1;
            int dist_next = 0, dist_prev = 0;
            // Go both directions to find dining car
            TrainCar *find_next = ptr, *find_prev = ptr;
            while (find_next->next != NULL) {
                find_next = find_next->next;
                dist_next += 1;
                // Stop when find a dining car
                if (find_next->isDiningCar()) break;
                else if (find_next->isEngine() ||
                         find_next->isFreightCar() ||
                         find_next->next == NULL) {
                    // Set dist to 0 and stop because passenger cannot cross a
                    // engine car or a freight car or this is the last car
                    dist_next = 0;
                    break;
                }
            }
            while (find_prev->prev != NULL) {
                find_prev = find_prev->prev;
                dist_prev += 1;
                // Stop when find a dining car
                if (find_prev->isDiningCar()) break;
                else if (find_prev->isEngine() ||
                         find_prev->isFreightCar() ||
                         find_prev->prev == NULL) {
                    // Set dist to 0 and stop because passenger cannot cross a
                    // engine car or a freight car or this is the last car
                    dist_prev = 0;
                    break;
                }
            }
            // If there are dining cars on both direction, count the closer one.
            // If either direction is 0, no dining car on this direction. Count
            // the other direction's result. Do nothing if we cannot find dining
            // car on either directions.
            if (dist_next != 0 && dist_prev != 0)
                total_dist += std::min(dist_next, dist_prev);
            else if (dist_next != 0) total_dist += dist_next;
            else if (dist_prev != 0) total_dist += dist_prev;
        } else if (ptr->isDiningCar()) total_dining_car += 1;
        ptr = ptr->next;
    }
    // Train must have both dining cars and passenger cars so that calculation
    // is meaningful.
    if (total_passenger_car > 0 && total_dining_car > 0)
        return (float)total_dist / total_passenger_car;
    else return -1;
}

int ClosestEngineToSleeperCar(TrainCar *train) {
    int dist = INT_MAX;
    TrainCar *ptr = train;
    while (ptr != NULL) {
        if (ptr->isEngine()) {
            int dist_next = 0, dist_prev = 0;
            // Go both directions to find dining car
            TrainCar *find_next = ptr, *find_prev = ptr;
            while (find_next->next != NULL) {
                find_next = find_next->next;
                dist_next += 1;
                // Stop when find a dining car
                if (find_next->isSleepingCar()) break;
                else if (find_next->isEngine() ||
                         find_next->isFreightCar() ||
                         find_next->next == NULL) {
                    // Set dist to 0 and stop because passenger cannot cross a
                    // engine car or a freight car or this is the last car
                    dist_next = 0;
                    break;
                }
            }
            while (find_prev->prev != NULL) {
                find_prev = find_prev->prev;
                dist_prev += 1;
                // Stop when find a dining car
                if (find_prev->isSleepingCar()) break;
                else if (find_prev->isEngine() ||
                         find_prev->isFreightCar() ||
                         find_prev->prev == NULL) {
                    // Set dist to 0 and stop because passenger cannot cross a
                    // engine car or a freight car or this is the last car
                    dist_prev = 0;
                    break;
                }
            }
            // If there are dining cars on both direction, count the closer one.
            // If either direction is 0, no dining car on this direction. Count
            // the other direction's result. Do nothing if we cannot find dining
            // car on either directions.
            if (dist_next != 0 && dist_prev != 0)
                dist = std::min(dist, std::min(dist_next, dist_prev));
            else if (dist_next != 0) dist = std::min(dist, dist_next);
            else if (dist_prev != 0) dist = std::min(dist, dist_prev);
        }
        ptr = ptr->next;
    }
    // dist would not be INT_MAX if any sleeper car is found. So if dist is
    // still INT_MAX, there is no sleeper car and we should return negative
    // number to imply this.
    if (dist != INT_MAX) return dist;
    else return -1;
}
// =============================================================================


// =============================================================================
// 2 Helper function used by ShipFreight() and Separate() to count total number
// of cars of a train and total number of engines of a train.
int CountCars(TrainCar* train) {
    int count = 0;
    TrainCar* ptr = train;
    while (ptr != NULL) {
        count += 1;
        ptr = ptr->next;
    }
    return count;
}

int CountEngines(TrainCar* train) {
    int count = 0;
    TrainCar* ptr = train;
    while (ptr != NULL) {
        if(ptr->isEngine()) count += 1;
        ptr = ptr->next;
    }
    return count;
}
// =============================================================================


// =============================================================================
// Implmentation of 2 mainly used algorithm
std::vector<TrainCar*> ShipFreight(TrainCar*& engines,
                                   TrainCar*& freights,
                                   const int& min_speed,
                                   const int& max_cars_per_train) {
    std::vector<TrainCar*> trains;
    while (engines != NULL && freights != NULL) {
        TrainCar *train = NULL;
        // Any train must have at least 1 engine to run. Thus directly add 1
        // engine to the start of a train.
        PushBack(train, PopFront(engines));
        // Comstraints: must be faster than minimum speed as well as less than
        //              maximum number of cars per train
        while (CalculateSpeed(train) > min_speed &&
               CountCars(train) < max_cars_per_train) {
            // Find heaviest car that can be added to this train
            TrainCar *last = NULL, *compare = freights;
            while (compare != NULL) {
                if (CalculateSpeed(train, compare) >= min_speed && last == NULL)
                    last = compare;
                else if (CalculateSpeed(train, compare) >= min_speed)
                    if (compare->getWeight() > last->getWeight()) last = compare;
                compare = compare->next;
            }
            // If a car is found, add it. If not, no freights can be fit into
            // this train. Stop this loop.
            if (last != NULL) {
                PushBack(train, Erase(freights, last));
            } else break;
        }
        trains.push_back(train);
    }
    // Linking short trains
    int num_shortest, num_longest, pos_shortest, pos_longest;
    do {
        num_shortest = INT_MAX, num_longest = -1;
        pos_shortest = INT_MAX, pos_longest = -1;
        // Find shortest train and its length
        for (unsigned int i = 0; i < trains.size(); ++i) {
            if (0 < CountCars(trains[i]) &&
                CountCars(trains[i]) < num_shortest) {
                num_shortest = CountCars(trains[i]);
                pos_shortest = i;
            }
        }
        // Find longest train that can be linked with shortest train which is
        // found previously and its length
        for (unsigned int i = 0; i < trains.size(); ++i) {
            if (max_cars_per_train - num_shortest >= CountCars(trains[i]) &&
                CountCars(trains[i]) >= num_longest &&
                CountCars(trains[i]) > 0) {
                num_longest = CountCars(trains[i]);
                pos_longest = i;
            }
        }
        // If both shortest and longest train which are capable of linking
        // together is found, linking them together.
        if (pos_shortest < trains.size() &&
            pos_longest > -1 &&
            pos_shortest != pos_longest) {
            TrainCar* ptr = PopFront(trains[pos_shortest]);
            while (ptr != NULL) {
                PushBack(trains[pos_longest], ptr);
                ptr = PopFront(trains[pos_shortest]);
            }
        }
    } while (pos_shortest < trains.size() &&
             pos_longest > -1 &&
             pos_shortest != pos_longest);
    // Build a new vector so that NULL pointers in trains would be omitted
    std::vector<TrainCar*> trains2;
    for (unsigned int i = 0; i < trains.size(); ++i) {
        if (trains[i] != NULL) trains2.push_back(trains[i]);
    }
    // After linking short trains together, surplus capacity would be combined
    // and hence might be capable to remaining freights. Check:
    TrainCar* ptr = freights;
    while (ptr != NULL) {
        for (unsigned int i = 0; i < trains2.size(); ++i) {
            if (CalculateSpeed(trains2[i], ptr) >= min_speed &&
                CountCars(trains2[i]) + 1 <= max_cars_per_train) {
                PushBack(trains2[i], Erase(freights, ptr));
                break;
            }
            if (i == trains2.size() - 1) ptr = ptr->next;
        }
    }
    return trains2;
}

void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3) {
    // train2 and train3 is initialized without value. So we assign it to NULL
    // to prevent some unexpect errors.
    train2 = train3 = NULL;
    int total_cars = CountCars(train1);
    int num_engines = CountEngines(train1);
    int num_non_engines = total_cars - num_engines;
    int left_engines = 0, right_engines = 0;
    // Evenly split train1
    for (int i = 0; i < num_non_engines / 2; ++i) {
        TrainCar* ptr;
        do {
            ptr = PopFront(train1);
            PushBack(train2, ptr);
        } while (ptr->isEngine());
        do {
            ptr = PopBack(train1);
            PushFront(train3, ptr);
        } while (ptr->isEngine());
    }
    // If there is odd number of passenger cars, there must be cars left in
    // train1. We decide the place where train1 need to be unlinked using the
    // relative position of engines.
    if (num_non_engines % 2 != 0) {
        left_engines = CountEngines(train2);
        TrainCar* ptr = train1;
        while (ptr->isEngine()) {
            left_engines += 1;
            ptr = ptr->next;
        }
        right_engines = num_engines - left_engines;
        // Left half of train has more engines, unlink train closing to left
        // would save costs. Otherwise, unlinking train closing to right.
        if (left_engines > right_engines) {
            do {
                ptr = PopBack(train1);
                PushFront(train3, ptr);
            } while (ptr->isEngine());
        } else {
            do {
                ptr = PopFront(train1);
                PushBack(train2, ptr);
            } while (ptr->isEngine());
        }
    }
    // Any more cars left are engines, evenly added to train2 and train3 if
    // possible.
    while (train1 != NULL) {
        TrainCar* ptr = PopFront(train1);
        PushBack(train2, ptr);
        if (train1 != NULL) {
            ptr = PopBack(train1);
            PushFront(train3, ptr);
        }
    }
    // Check engines' positions. If train3 has too much engines, unlinking some
    // from train3 and append to the end of train2. Otherwise, unlinking engines
    // from train2 and push to the front of train3. In this way, the cost of
    // dragging engines is fewest.
    while (CountEngines(train2) < num_engines / 2) {
        TrainCar* ptr = train3;
        while (!ptr->isEngine()) ptr = ptr->next;
        PushBack(train2, Erase(train3, ptr));
    }
    while (CountEngines(train3) < num_engines / 2) {
        TrainCar* ptr = train2;
        while (ptr->next != NULL) ptr = ptr->next;
        while (!ptr->isEngine()) ptr = ptr->prev;
        PushFront(train3, Erase(train2, ptr));
    }
}
// =============================================================================


// =============================================================================
// Extra credit
void MoveEnginesAndInsertDiningCars(TrainCar*& train,
                                    TrainCar*& dinings,
                                    const int& num_dining_cars) {
    int left_shift = 0, right_shift = 0;
    int total_cars = CountCars(train), num_engines = CountEngines(train);
    int num_passenger_cars = total_cars - num_engines;
    int count_passenger_cars = 0;
    // Counting the total costs of shifting all engines to left or right to
    // decide which side we are going to shift engines to. Meanwhile, extract
    // all engines out of train. Engines will be added after dining cars added
    // into trains.
    TrainCar *engines = NULL, *ptr = train;
    while (ptr != NULL) {
        if (ptr->isEngine()) {
            left_shift += count_passenger_cars;
            right_shift += num_passenger_cars - count_passenger_cars;
            PushBack(engines, Erase(train, ptr));
        } else {
            count_passenger_cars += 1;
            ptr = ptr->next;
        }
    }
    // Evenly inserting dining cars into passenger cars.
    int pos = num_passenger_cars / (num_dining_cars + 1);
    if (pos == 0 || num_passenger_cars == num_dining_cars) {
        ptr = train;
        unsigned int i = 0;
        for (; i < num_passenger_cars; ++i, ptr = ptr->next)
            Insert(train, ptr, PopFront(dinings));
        for (; i < num_dining_cars; ++i) PushBack(train, PopFront(dinings));
    } else {
        int count_pos = 0, count_add = 0;
        ptr = train;
        while (count_add < num_dining_cars) {
            if (count_pos == pos) {
                Insert(train, ptr, PopFront(dinings));
                count_add += 1;
                count_pos = 0;
            }
            count_pos += 1;
            ptr = ptr->next;
        }
    }
    // If shifting all engines to left costs less, putting all engines to left
    // side. Otherwise, putting all engines to right side. Sleeping cars are put
    // as the same time but on the opposite side of engines.
    if (left_shift <= right_shift) {
        ptr = train;
        while (engines != NULL) Insert(train, ptr, PopFront(engines));
    } else while (engines != NULL) PushBack(train, PopFront(engines));
}

void SeparateComfort(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3) {
    // Extract different kind of cars from train1
    TrainCar *sleepings = NULL, *dinings = NULL, *ptr = train1;
    while (ptr != NULL) {
        if (ptr->isSleepingCar()) PushBack(sleepings, Erase(train1, ptr));
        else if (ptr->isDiningCar()) PushBack(dinings, Erase(train1, ptr));
        else ptr = ptr->next;
    }
    
    Separate(train1, train2, train3);
    
    int num_train2_passenger = CountCars(train2) - CountEngines(train2);
    int num_train3_passenger = CountCars(train3) - CountEngines(train3);
    // Shift all engines to one side so that all passenger cars can access to
    // dining car and sleeping cars can be put at the other side of train for
    // higher level of comfort.
    int num_dining_cars = CountCars(dinings);
    if (num_dining_cars % 2 != 0) {
        if (num_train2_passenger >= num_train3_passenger) {
            MoveEnginesAndInsertDiningCars(train2, dinings, num_dining_cars / 2 + 1);
            MoveEnginesAndInsertDiningCars(train3, dinings, num_dining_cars / 2);
        } else {
            MoveEnginesAndInsertDiningCars(train2, dinings, num_dining_cars / 2);
            MoveEnginesAndInsertDiningCars(train3, dinings, num_dining_cars / 2 + 1);
        }
    } else {
        MoveEnginesAndInsertDiningCars(train2, dinings, num_dining_cars / 2);
        MoveEnginesAndInsertDiningCars(train3, dinings, num_dining_cars / 2);
    }
    // Add sleeping cars to the opposite side of engines
    int num_sleeping_cars = CountCars(sleepings);
    if (train2->isEngine()) {
        if (num_sleeping_cars % 2 != 0 &&
            num_train2_passenger >= num_train3_passenger) {
            for (unsigned int i = 0; i < num_sleeping_cars / 2 + 1; ++i)
                PushBack(train2, PopFront(sleepings));
        } else {
            for (unsigned int i = 0; i < num_sleeping_cars / 2; ++i)
                PushBack(train2, PopFront(sleepings));
        }
    } else {
        TrainCar* ptr = train2;
        if (num_sleeping_cars % 2 != 0 &&
            num_train2_passenger >= num_train3_passenger) {
            for (unsigned int i = 0; i < num_sleeping_cars / 2 + 1; ++i)
                Insert(train2, ptr, PopFront(sleepings));
        } else {
            for (unsigned int i = 0; i < num_sleeping_cars / 2; ++i)
                Insert(train2, ptr, PopFront(sleepings));
        }
    }
    if (train3->isEngine()) {
        while (sleepings != NULL) PushBack(train3, PopFront(sleepings));
    } else {
        while (sleepings != NULL) PushFront(train3, PopBack(sleepings));
    }
}
// =============================================================================
