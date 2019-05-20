#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"

// Don't write code like this!!!

#include <cstdlib> // for rand()

void baz(std::vector<Point2D*>& foo) {
    // baz adds data to foo
    // for (int i = 0; i < foo.size(); i++) {
    foo.push_back(new Point2D(1,1));
    foo.push_back(new Point2D(1,1));
    foo.push_back(new Point2D(10,1));
    foo.push_back(new Point2D(3.1, 2.3));
    foo.push_back(new Point2D(4, 2.9));
    //}
}

// the norf function may need to be defined before the warbly function
void norf(const std::vector<Rectangle>& foo) {
    for (unsigned int baz = 0; baz < foo.size(); baz++) {
        // norf calls print_rectangle with baz and foo
        print_rectangle(foo[baz]);
    }
}

void warbly(std::vector<Rectangle>& zyzzy,
            const std::vector<Point2D*>& zyyzy) {
    // first loop over the data using a variable r
    for (unsigned int r = 0; r < zyzzy.size(); ++r) {
        for (unsigned int i = 0; i < zyyzy.size(); ++i) {
            // then run is_point_within
            if (zyzzy[r].is_point_within(*zyyzy[i]))
                zyzzy[r].add_point(*zyyzy[i]);
        }
    }
}

// using matching variable and function names is fun
void quuuux(std::vector<Rectangle>& quuuuux) {
    for (int i = 0; i < 100; ++i)
        //if (quuuuux.is_point_within(Point2D(rand(),rand()))) {
        quuuuux.push_back(Rectangle(Point2D(rand(), rand()), Point2D(rand(), rand())));
    //}
}

// Function foo
void foo() {
    // create the vector of Rectangles quux
    std::vector<Rectangle> quux;
    quuuux(quux);
    std::vector<Point2D*> quuux;  // the vector quuux contains pointers to points
    baz(quuux);
    warbly(quux, quuux);  // call function warbly using quux and quuuz as arguments
    // finally let's call function norf using quuz as an argument
    norf(quux);
}


int main() {
    //warbly(norf,baz);
    
    // foo does all the work
    foo();
    
    // this wasn't working
    //qux(quux,quuux);
    
    return 0;
}
