#pragma once
#include <bits/stdc++.h>

namespace Response {

struct Base;

using Holder = std::shared_ptr<Base>;

struct Base {
    virtual void print(std::ostream& os) const = 0;
};
std::ostream& operator<<(std::ostream& out, const Base& response);

//
struct BusRouteFound : Base {
    std::string_view bus_name;
    // stops count on FULL route (from stop1 to stop1)
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
    double curvature;
    void print(std::ostream& os) const override;
};
struct BusRouteNotFound : Base {
    std::string_view bus_name;
    void print(std::ostream& os) const override;
};

//
struct BusStopsFound : Base {
    std::string stop_name;
    const std::set<std::string>* bus_names;
    void print(std::ostream& os) const override;
};
struct BusStopsNotFound : Base {
    std::string stop_name;
    void print(std::ostream& os) const override;
};
struct BusStopsEmpty : Base {
    std::string stop_name;
    void print(std::ostream& os) const override;
};

}  // namespace Response
