#include <bits/stdc++.h>
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

// airline_ticket.h operators reload
bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(rhs == lhs);
}
bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}
bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const Date& date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}
bool operator==(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}
bool operator!=(const Time& lhs, const Time& rhs) {
    return !(rhs == lhs);
}
bool operator<(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}
bool operator>(const Time& lhs, const Time& rhs) {
    return rhs < lhs;
}
bool operator<=(const Time& lhs, const Time& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const Time& lhs, const Time& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const Time& time1) {
    os << "hours: " << time1.hours << " minutes: " << time1.minutes;
    return os;
}

bool operator<(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return std::tie(lhs.from, lhs.to, lhs.airline, lhs.departure_date, lhs.departure_time, lhs.arrival_date,
                    lhs.arrival_time, lhs.price) < std::tie(rhs.from, rhs.to, rhs.airline, rhs.departure_date,
                                                            rhs.departure_time, rhs.arrival_date,
                                                            rhs.arrival_time, rhs.price);
}
bool operator>(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return rhs < lhs;
}
bool operator<=(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return !(rhs < lhs);
}
bool operator>=(const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return !(lhs < rhs);
}
ostream& operator<<(ostream& os, const AirlineTicket& ticket) {
    os << "from: " << ticket.from << " to: " << ticket.to << " airline: " << ticket.airline
       << " departure_date: " << ticket.departure_date << " departure_time: " << ticket.departure_time
       << " arrival_date: " << ticket.arrival_date << " arrival_time: " << ticket.arrival_time
       << " price: " << ticket.price;
    return os;
}

// END reload

#define SORT_BY(field) \
    ([](const AirlineTicket& lhs, const AirlineTicket& rhs) { return lhs.field < rhs.field; })

void TestSortBy() {
    vector<AirlineTicket> tixs = {
        {"VKO", "AER", "Utair", {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20, 0}, 1200},
        {"AER", "VKO", "Utair", {2018, 3, 5}, {14, 15}, {2018, 3, 5}, {16, 30}, 1700},
        {"AER", "SVO", "Aeroflot", {2018, 3, 5}, {18, 30}, {2018, 3, 5}, {20, 30}, 2300},
        {"PMI", "DME", "Iberia", {2018, 2, 8}, {23, 00}, {2018, 2, 9}, {3, 30}, 9000},
        {"CDG", "SVO", "AirFrance", {2018, 3, 1}, {13, 00}, {2018, 3, 1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}
