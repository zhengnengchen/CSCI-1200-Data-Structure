#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define earthRadiusKm 6371.0

//TODO: You must fill in all ?????? with the correct types.
typedef unsigned int ID_TYPE; //Type for user IDs
typedef std::pair<float, float> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef std::map<ID_TYPE, std::vector<ID_TYPE> > ADJ_TYPE; //Adjacency Lists type
typedef std::map<ID_TYPE, COORD_TYPE> GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations, 
                                std::ofstream& outfile, const ID_TYPE& start_id, 
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin, 
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0] 
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!" 
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!" 
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename 
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id, 
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile, 
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
    std::string a, b;
    while (loadfile >> a >> b) {
        ID_TYPE id_a = (ID_TYPE)atol(a.c_str());
        ID_TYPE id_b = (ID_TYPE)atol(b.c_str());
        ADJ_TYPE::iterator itr = adj_lists.find(id_a);
        if (itr != adj_lists.end()) itr->second.push_back(id_b);
        else {
            std::vector<ID_TYPE> tmp;
            tmp.push_back(id_b);
            adj_lists[id_a] = tmp;
        }
    }
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
    std::string a, b, c;
    while (loadfile >> a >> b >> c) {
        ID_TYPE id = (ID_TYPE)atol(a.c_str());
        float lat = atof(b.c_str()), lon = atof(c.c_str());
        locations[id] = COORD_TYPE(lat, lon);
    }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations,
                                 std::ofstream& outfile,
                                 const ID_TYPE& start_id,
                                 double max_distance) {
    // Find start_id
    GEO_TYPE::const_iterator start_itr = locations.find(start_id);
    if (start_itr == locations.end()) {
        // Check if start_id exists
        outfile << "User ID " << start_id;
        outfile << " does not have a recorded location." << std::endl;
        return;
    }
    
    // find and sort all others users within max distance
    std::map<double, std::vector<ID_TYPE> > sorted;
    for (GEO_TYPE::const_iterator itr = locations.begin();
         itr != locations.end(); ++itr) {
        if (itr->first != start_id) {
            double distance = floor(distanceEarth(start_itr->second.first,
                                                  start_itr->second.second,
                                                  itr->second.first,
                                                  itr->second.second));
            if (distance <= max_distance) {
                std::map<double, std::vector<ID_TYPE> >::iterator sort_itr;
                sort_itr = sorted.find(distance);
                if (sort_itr == sorted.end()) {
                    std::vector<ID_TYPE> tmp;
                    tmp.push_back(itr->first);
                    sorted[distance] = tmp;
                } else sort_itr->second.push_back(itr->first);
            }
        }
    }
    
    // Print out results
    if (sorted.size() == 0) {
        outfile << "There are no users within " << max_distance;
        outfile << " km of user " << start_id << std::endl;
    } else {
        outfile << "User IDs within " << max_distance << " km of user ";
        outfile << start_id << ":" << std::endl;
        for (std::map<double, std::vector<ID_TYPE> >::const_iterator itr = sorted.begin();
             itr != sorted.end(); ++itr) {
            outfile << " " << itr->first << " km:";
            for (unsigned int i = 0; i < itr->second.size(); ++i)
            outfile << " " << itr->second[i];
            outfile << std::endl;
        }
    }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile) {
    // Build a map with degree number as key and the number of user with that degree as value
    std::map<unsigned int, unsigned int> histogram;
    for (ADJ_TYPE::const_iterator itr = adj_lists.begin();
         itr != adj_lists.end(); ++itr) {
        unsigned int degree = itr->second.size();
        std::map<unsigned int, unsigned int>::iterator r = histogram.find(degree);
        if (r != histogram.end()) r->second += 1;
        else histogram[degree] = 1;
    }
    
    // Print out
    outfile << "Histogram for " << adj_lists.size() << " users:" << std::endl;
    for (std::map<unsigned int, unsigned int>::const_iterator itr = histogram.begin();
         itr != histogram.end(); ++itr)
        outfile << " Degree " << itr->first << ": " << itr->second << std::endl;
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile) {
    // adj_lists is sorted based on user IDs since user IDs are keys of map
    outfile << "Degrees for " << adj_lists.size() << " users:" << std::endl;
    for (ADJ_TYPE::const_iterator itr = adj_lists.begin();
         itr != adj_lists.end(); ++itr) {
        outfile << " " << itr->first << ": Degree " << itr->second.size();
        outfile << std::endl;
    }
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree) {
    // Find start_id
    ADJ_TYPE::const_iterator start_itr = adj_lists.find(start_id);
    if (start_itr == adj_lists.end()) {
        // Check if start_id exists
        outfile << "There is no user with friends and ID " << start_id;
        outfile << std::endl;
        return;
    }
    std::vector<ID_TYPE> start_friends = start_itr->second;
    
    // Find all friends with particular degree
    std::vector<ID_TYPE> sorted;
    for (unsigned int i = 0; i < start_friends.size(); ++i) {
        ADJ_TYPE::const_iterator friend_itr = adj_lists.find(start_friends[i]);
        if (friend_itr != adj_lists.end()) {
            if (friend_itr->second.size() == degree)
                sorted.push_back(friend_itr->first);
        }
    }
    std::sort(sorted.begin(), sorted.end());
    
    // Print out results
    outfile << "User " << start_id << " has " << sorted.size();
    outfile << " friend(s) with degree " << degree;
    if (sorted.size() != 0) outfile << ":";
    for (unsigned int i = 0; i < sorted.size(); ++i) outfile << " " << sorted[i];
    outfile << std::endl;
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists,
                                const GEO_TYPE& locations,
                                std::ofstream& outfile,
                                const ID_TYPE& start_id,
                                double max_distance){
    // Find start_id's friends
    ADJ_TYPE::const_iterator itr1 = adj_lists.find(start_id);
    if (itr1 == adj_lists.end()) { // Check if start_id exists in adk_lists
        outfile << "There is no user with friends and ID " << start_id;
        outfile << std::endl;
        return;
    }
    std::vector<ID_TYPE> start_friends = itr1->second;
    
    // Also, find start_id's location
    GEO_TYPE::const_iterator itr2 = locations.find(start_id);
    if (itr2 == locations.end()) { // Check if start_id exists in locations
        outfile << "User ID " << start_id;
        outfile << " does not have a recorded location." << std::endl;
        return;
    }
    COORD_TYPE start_location = itr2->second;
    
    // find and sort all friends within max distance
    std::map<double, std::vector<ID_TYPE> > sorted;
    for (unsigned int i = 0; i < start_friends.size(); ++i) {
        // For each friend
        GEO_TYPE::const_iterator friend_itr = locations.find(start_friends[i]);
        if (friend_itr != locations.end()) {
            // Compute distance from start_id's location to this friend and save
            // this to a map
            double distance = distanceEarth(friend_itr->second.first,
                                            friend_itr->second.second,
                                            start_location.first,
                                            start_location.second);
            if (distance <= max_distance) {
                std::map<double, std::vector<ID_TYPE> >::iterator itr;
                itr = sorted.find(distance);
                if (itr == sorted.end()) {
                    std::vector<ID_TYPE> tmp;
                    tmp.push_back(friend_itr->first);
                    sorted[distance] = tmp;
                } else itr->second.push_back(friend_itr->first);
            }
        }
        
    }
    
    // Print out results
    if (sorted.size() == 0) {
        outfile << "There are no friends within " << max_distance;
        outfile << " km of user " << start_id << std::endl;
    } else {
        outfile << "Friends within " << max_distance << " km of user ";
        outfile << start_id << ":" << std::endl;
        for (std::map<double, std::vector<ID_TYPE> >::const_iterator itr = sorted.begin();
             itr != sorted.end(); ++itr) {
            outfile << " " << itr->first << " km:";
            for (unsigned int i = 0; i < itr->second.size(); ++i)
                outfile << " " << itr->second[i];
            outfile << std::endl;
        }
    }
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile,
                             ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end, 
                             ADJ_TYPE::const_iterator start_it,
                             unsigned int offset){
    // At first, check if start_it exists in adj_lists.
    if (start_it == end) {
        outfile << "There is no user with the requested ID" << std::endl;
        return;
    }
    
    // Find forwardly and backwardly
    std::vector<ID_TYPE> sorted;
    ID_TYPE start_id = start_it->first;
    ADJ_TYPE::const_iterator tmp = start_it;
    while (++tmp != end) {
        if (tmp->first <= start_id + offset) sorted.push_back(tmp->first);
    }
    tmp = start_it;
    while (tmp-- != begin) {
        if (tmp->first >= start_id - offset) sorted.push_back(tmp->first);
    }
    std::sort(sorted.begin(), sorted.end());
    
    // Print out results
    if (sorted.size() == 0) {
        outfile << "There are no users with an ID within +/-" << offset;
        outfile << " of " << start_id << std::endl;
    }
    else {
        outfile << "Users with an ID within +/-" << offset << " of ";
        outfile << start_id << ":";
        for (unsigned int i = 0; i < sorted.size(); ++i)
            outfile << " " << sorted[i];
        outfile << std::endl;
    }
}
