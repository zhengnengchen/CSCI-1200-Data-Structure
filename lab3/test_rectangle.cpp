#include "Rectangle.h"
#include "Point2D.h"

#include <iostream>
#include <vector>

int main() {
    Point2D p1(2, 2);
    Point2D p2(4, 4);
    Point2D p3(3, 3);
    Point2D p4(5, 5);
    Rectangle r1(p1, p2);
    Rectangle r2(p3, p4);
    
    if ( r1.is_point_within(p3) ) std::cout << "p3 is within the rectangle r1." << std::endl;
    if ( r2.is_point_within(p2) ) std::cout << "p2 is within the rectangle r2." << std::endl;
    
    if ( r1.add_point(p3) ) std::cout << "successfully add p3 to r1." << std::endl;
    if ( r2.add_point(p2) ) std::cout << "successfully add p3 to r1." << std::endl;
    
    Point2D p5(1, 5);
    Point2D p6(2, 6);
    if ( r1.add_point(p5) ) std::cout << "successfully add p5 to r1." << std::endl;
    if ( r2.add_point(p6) ) std::cout << "successfully add p6 to r1." << std::endl;
    
    Point2D p7(3.5, 3.5);
    if ( r1.add_point(p7) ) std::cout << "successfully add p7 to r1." << std::endl;
    if ( r2.add_point(p7) ) std::cout << "successfully add p7 to r1." << std::endl;
    std::vector<Point2D> p8 = points_in_both(r1,r2);
    std::cout << "These points are in both r1 and r2: ";
    for (int i = 0; i < p8.size(); ++i) {
        std::cout << '(' << p8[i].x() << ", " << p8[i].y() << ") ";
    }
    std::cout << std::endl;
    
    print_rectangle(r1);
}
