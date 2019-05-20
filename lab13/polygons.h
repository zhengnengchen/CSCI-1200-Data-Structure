#ifndef __polygons_h_
#define __polygons_h_

#include "utilities.h"
#include <string>
#include <vector>

class Polygon {
public:
    // Constructors
    Polygon(const std::string& n, const std::vector<Point>& p) {
        m_name = n;
        m_points = p;
    }
    virtual ~Polygon() {}
    
    // Accessor and help function
    std::string getName() const { return m_name; }
    virtual bool HasAllEqualSides() const {
        std::vector<double> lengths;
        for (unsigned int i = 1; i < m_points.size(); ++i) {
            lengths.push_back(DistanceBetween(m_points[i - 1],m_points[i]));
        }
        for (unsigned int i = 0; i < lengths.size() - 1; ++i) {
            for (unsigned int j = 1; j < lengths.size(); ++j) {
                if (!EqualSides(lengths[i], lengths[j])) return false;
            }
        }
        return true;
    }
    virtual bool HasAllEqualAngles() const {
        std::vector<double> angles;
        for (unsigned int i = 0; i < m_points.size(); ++i) {
            if (i == 0) angles.push_back(Angle(m_points[m_points.size() - 1],
                                               m_points[i],
                                               m_points[i + 1]));
            else if (i == m_points.size() - 1)
                angles.push_back(Angle(m_points[i - 1],
                                       m_points[i],
                                       m_points[0]));
            else angles.push_back(Angle(m_points[i - 1],
                                        m_points[i],
                                        m_points[i + 1]));
        }
        for (unsigned int i = 0; i < angles.size() - 1; ++i) {
            for (unsigned int j = 1; j < angles.size(); ++j) {
                if (!EqualAngles(angles[i], angles[j])) return false;
            }
        }
        return true;
    }
    virtual bool HasARightAngle() const {
        std::vector<double> angles;
        for (unsigned int i = 0; i < m_points.size(); ++i) {
            if (i == 0) angles.push_back(Angle(m_points[m_points.size() - 1],
                                               m_points[i],
                                               m_points[i + 1]));
            else if (i == m_points.size() - 1)
                angles.push_back(Angle(m_points[i - 1],
                                       m_points[i],
                                       m_points[0]));
            else angles.push_back(Angle(m_points[i - 1],
                                        m_points[i],
                                        m_points[i + 1]));
        }
        for (unsigned int i = 0; i < angles.size() - 1; ++i) {
            if (RightAngle(angles[i])) return true;
        }
        return false;
    }
    
protected:
    std::string m_name;
    std::vector<Point> m_points;
};

class Triangle : public Polygon {
public:
    Triangle(const std::string& n, const std::vector<Point>& p)
    : Polygon(n, p) { if (p.size() != 3) throw 1210; }
};

class IsoscelesTriangle : virtual public Triangle {
public:
    IsoscelesTriangle(const std::string& n, const std::vector<Point>& p)
    : Triangle(n, p) {
        double side1_length = DistanceBetween(m_points[0],m_points[1]);
        double side2_length = DistanceBetween(m_points[1],m_points[2]);
        double side3_length = DistanceBetween(m_points[2],m_points[0]);
        if (!EqualSides(side1_length, side2_length) &&
            !EqualSides(side1_length, side3_length) &&
            !EqualSides(side2_length, side3_length)) throw 1210;
    }
};

class RightTriangle : virtual public Triangle {
public:
    RightTriangle(const std::string& n, const std::vector<Point>& p)
    : Triangle(n, p) {
        double angle1 = Angle(m_points[0],m_points[1], m_points[2]);
        double angle2 = Angle(m_points[1],m_points[2], m_points[0]);
        double angle3 = Angle(m_points[2],m_points[0], m_points[1]);
        if (!RightAngle(angle1) && !RightAngle(angle2) && !RightAngle(angle3))
            throw 1210;
    }
    //bool HasARightAngle() const { return true; }
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
    IsoscelesRightTriangle(const std::string& n, const std::vector<Point>& p)
    : Triangle(n, p), IsoscelesTriangle(n, p), RightTriangle(n, p) {}
    //bool HasAllEqualSides() const { return false; }
    //bool HasAllEqualAngles() const { return false; }
    //bool HasARightAngle() const { return true; }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string& n, const std::vector<Point>& p)
    : Triangle(n, p), IsoscelesTriangle(n, p) {
        double side1_length = DistanceBetween(m_points[0],m_points[1]);
        double side2_length = DistanceBetween(m_points[1],m_points[2]);
        double side3_length = DistanceBetween(m_points[2],m_points[0]);
        if (!EqualSides(side1_length, side2_length) ||
            !EqualSides(side1_length, side3_length) ||
            !EqualSides(side2_length, side3_length)) throw 1210;
    }
    //bool HasAllEqualSides() const { return true; }
    //bool HasAllEqualAngles() const { return true; }
    //bool HasARightAngle() const { return false; }
};

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const std::string& n, const std::vector<Point>& p)
    : Polygon(n, p) { if(p.size() != 4) throw 1210; }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(const std::string& n, const std::vector<Point>& p)
    : Quadrilateral(n, p) {
        double angle1 = Angle(m_points[0],m_points[1], m_points[2]);
        double angle2 = Angle(m_points[1],m_points[2], m_points[3]);
        double angle3 = Angle(m_points[2],m_points[3], m_points[0]);
        double angle4 = Angle(m_points[3],m_points[0], m_points[1]);
        if (!RightAngle(angle1) || !RightAngle(angle2) ||
            !RightAngle(angle3) || !RightAngle(angle4)) throw 1210;
    }
    //bool HasAllEqualAngles() const { return true; }
    //bool HasARightAngle() const { return true; }
};

class Square : public Rectangle {
public:
    Square(const std::string& n, const std::vector<Point>& p)
    : Rectangle(n, p) {
        double side1_length = DistanceBetween(m_points[0], m_points[1]);
        double side2_length = DistanceBetween(m_points[1], m_points[2]);
        if (!EqualSides(side1_length, side2_length)) throw 1210;
    }
    //bool HasAllEqualSides() const { return true; }
    //bool HasAllEqualAngles() const { return true; }
    //bool HasARightAngle() const { return true; }
};

#endif
