#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <vector>

class Ring_Buffer
{
public:
    Ring_Buffer(int s);

    void insert(double val);
    double integrate();
    void clear();

private:
    int theSize;
    int idx;
    std::vector<double> buf;
};

#endif // RING_BUFFER_H
