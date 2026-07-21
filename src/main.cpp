#include "elevator.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
std::int32_t parseFloor(const std::string& value) {
    std::size_t parsedCharacters = 0;
    const long long floor = std::stoll(value, &parsedCharacters);
    if (parsedCharacters != value.size() || floor < std::numeric_limits<std::int32_t>::min() ||
        floor > std::numeric_limits<std::int32_t>::max()) {
        throw std::out_of_range("floor must be a 32-bit integer");
    }
    return static_cast<std::int32_t>(floor);
}
}  // namespace

int main() {
    try {
        std::cout << "Starting floor: ";
        std::string input;
        std::getline(std::cin, input);
        Elevator elevator(parseFloor(input));

        std::cout << "Destination floors (comma separated): ";
        std::getline(std::cin, input);
        std::stringstream destinations(input);
        std::string destination;
        while (std::getline(destinations, destination, ',')) {
            if (destination.empty()) {
                throw std::invalid_argument("destination cannot be empty");
            }
            elevator.AddDestination(parseFloor(destination));
        }

        if (elevator.GetTargets().empty()) {
            throw std::invalid_argument("enter at least one destination");
        }

        std::cout << "Optimize route? (y/n): ";
        std::getline(std::cin, input);
        if (!input.empty() && (input.front() == 'y' || input.front() == 'Y')) {
            elevator.VisitAllNearest();
        } else {
            elevator.VisitAll();
        }

        const auto visited = elevator.GetVisited();
        std::cout << "Travel time: " << elevator.GetTravelTime() << "\nFloors visited: ";
        for (std::size_t index = 0; index < visited.size(); ++index) {
            if (index > 0) {
                std::cout << ',';
            }
            std::cout << visited[index];
        }
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Invalid input: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
