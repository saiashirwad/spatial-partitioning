#include <iostream>
#include <list>
#include <iterator>

// Point
struct Point
{
    int x, y;
    void print();
};

void Point::print()
{
    std::cout << "(" << x << ", " << y << ")";
}

// Rectangle
struct Rectangle
{
    Rectangle(int, int, int, int);
    void print();
    int x, y, w, h;
    bool contains(Point* point);
    bool intersects(Rectangle* range);
};

Rectangle::Rectangle(int _x, int _y, int _w, int _h) :
    x(_x), y(_y), w(_w), h(_h) {}

bool Rectangle::intersects(Rectangle* range)
{
    return !(
            range.x - range.w > x + w ||
            range.x + range.w < x - w ||
            range.y + range.h < y + h ||
            range.y + range.h < y - h
    );
}

bool Rectangle::contains(Point* point)
{
    return point->x > x-w &&  point->x < x+w && point->y > y-h && point->y < y+h;
}

void Rectangle::print()
{
    std::cout << "x: " << x <<
                 "y: " << y <<
                 "w: " << w <<
                 "h: " << h << std::endl;
}

class Circle
{
public:
    Circle(int, int, int);
    contains(Point*);
    intersects(Rectangle*);
};



// Quadtree
class QuadTree
{
public:
    //QuadTree(Rectangle*, int);
    QuadTree(int, int, int, int, int);
    QuadTree(int, int, int, int);
    void print();
    void insert(Point*);
    void insert(int x, int y);

private:
    void subdivide();

public:
    Rectangle* boundary;
    int capacity;
    QuadTree *nw, *ne, *sw, *se;

private:
    bool divided;
    std::list<Point*> :: iterator it;
    std::list<Point*> points;
    Point* p;
};

void QuadTree::subdivide()
{
    int x = boundary->x;
    int y = boundary->y;
    int w = boundary->w;
    int h = boundary->h;
    ne = new QuadTree(x+w/2, y-h/2,  w/2, h/2);
    nw = new QuadTree(x-w/2, y-h/2,  w/2, h/2);
    se = new QuadTree(x+w/2, y+h/2,  w/2, h/2);
    sw = new QuadTree(x-w/2, y+h/2,  w/2, h/2);
}

void QuadTree::insert(int x, int y)
{
    Point* p = new Point{x, y};
    insert(p);
}

void QuadTree::insert(Point* point)
{
    if (boundary->contains(point))
    {
        if (points.size() < capacity)
        { 
            points.push_back(point);
        } else {
            if (!divided)
            {
                subdivide();
                std::cout << "subdivided" << std::endl;
                divided = true;
            }
            ne->insert(point);
            nw->insert(point);
            se->insert(point);
            sw->insert(point);
        }
    }
}

QuadTree::QuadTree(int _x, int _y, int _w, int _h, int _capacity)
    : capacity(_capacity)
{
    boundary = new Rectangle(_x, _y, _w, _h);
    divided = false;
}

QuadTree::QuadTree(int _x, int _y, int _w, int _h)
{
    boundary = new Rectangle(_x, _y, _w, _h);
    divided = false;
    capacity = 4;
}

void QuadTree::print()
{
    boundary->print();
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "Points :\n";
    for (it = points.begin(); it != points.end(); ++it)
        (*it)->print();
    std::cout << std::endl;
}

int main()
{
    QuadTree* q1 = new QuadTree(200, 200, 200, 200, 4);
    q1->insert(23, 25);
    q1->insert(23, 35);
    q1->insert(34, 83);
    q1->insert(43, 83);
    q1->insert(43, 3);
    q1->insert(43, 83);
    q1->insert(43, 83);
    
    q1->nw->print();

    return 0;
}
