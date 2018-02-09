#include "ring_buffer.h"
#include <numeric>
#include <iterator>

Ring_Buffer::Ring_Buffer(int s) : theSize(s), idx(0)
{
    buf.assign(theSize,0);
}

void Ring_Buffer::insert(double val) {
    buf[idx++] = val;
    if (idx == theSize - 1) {
        idx = 0;
    }
}

double Ring_Buffer::integrate() {
    return std::accumulate(std::begin(buf), std::end(buf),0);
}

void Ring_Buffer::clear() {
    buf.assign(theSize,0);
}
