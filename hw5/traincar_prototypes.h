// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//


// =============================================================================
// These are simulated double linked list member functions to manipulate a
// double linked list like we did to std::list.
void PushBack(TrainCar*& train, TrainCar* car);
void PushFront(TrainCar*& train, TrainCar* car);
TrainCar* PopBack(TrainCar*& train);
TrainCar* PopFront(TrainCar*& train);
TrainCar* Erase(TrainCar*& train, TrainCar*& ptr);
TrainCar* Insert(TrainCar*& train, TrainCar*& ptr, TrainCar* car);
void DeleteAllCars(TrainCar*& train);
// =============================================================================


// =============================================================================
// 4 Helper functions used in PrintTrain().
void TotalWeightAndCountCars(TrainCar* train,
                             int& total_weight,
                             int& num_engines,
                             int& num_freight_cars,
                             int& num_passenger_cars,
                             int& num_dining_cars,
                             int& num_sleeping_cars);
float CalculateSpeed(TrainCar* train, TrainCar* car = NULL);
float AverageDistanceToDiningCar(TrainCar* train);
int ClosestEngineToSleeperCar(TrainCar* train);
// =============================================================================


// =============================================================================
// 2 Helper function used by ShipFreight() and Separate() to count total number
// of cars of a train and total number of engines of a train.
int CountCars(TrainCar* train);
int CountEngines(TrainCar* train);
// =============================================================================


// =============================================================================
// Declaration of 2 mainly used algorithm
std::vector<TrainCar*> ShipFreight(TrainCar*& engines,
                                   TrainCar*& freights,
                                   const int& min_speed,
                                   const int& max_cars_per_train);
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3);
// =============================================================================


// =============================================================================
// Extra credit
void MoveEnginesAndInsertDiningCars(TrainCar*& train,
                                    TrainCar*& dinings,
                                    const int& num_dining_cars);
void SeparateComfort(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3);
// =============================================================================
