#include "BusStop.h"
/* ========================================================
BOILERPLATE
======================================================== */

size_t hash<BusStop>::operator()(const BusStop& obj) const {
    static const size_t x = 228'1488 + 54'27;
    size_t r1 = string_hash(obj.name);
    size_t r2 = Coordinate_hash(obj.coordinate);
    return PolynomicCombine(x, {r1, r2});
}
