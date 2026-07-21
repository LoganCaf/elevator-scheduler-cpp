#include "elevator.hpp"

#include <cstddef>
#include <cstdint>

namespace {
constexpr std::uint64_t travelTimePerFloor = 10;

std::uint64_t floorDistance(std::int32_t first, std::int32_t second) {
    const auto difference = static_cast<std::int64_t>(first) - static_cast<std::int64_t>(second);
    return static_cast<std::uint64_t>(difference < 0 ? -difference : difference);
}
}  // namespace

Elevator::Elevator(std::int32_t currentFloor) : currentFloor(currentFloor) {
    visited.push_back(currentFloor);
}

void Elevator::Move(std::int32_t targetFloor) {
    if (targetFloor == currentFloor) {
        return;
    }

    travelTime += floorDistance(targetFloor, currentFloor) * travelTimePerFloor;
    currentFloor = targetFloor;
    visited.push_back(currentFloor);
}

void Elevator::AddDestination(std::int32_t targetFloor) {
    targets.push_back(targetFloor);
}

void Elevator::VisitAll() {
    for (const std::int32_t target : targets) {
        Move(target);
    }
    targets.clear();
}

void Elevator::VisitAllNearest() {
    while (!targets.empty()) {
        std::size_t bestIndex = 0;
        std::uint64_t bestDistance = floorDistance(targets.front(), currentFloor);

        for (std::size_t index = 1; index < targets.size(); ++index) {
            const std::uint64_t distance = floorDistance(targets[index], currentFloor);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestIndex = index;
            }
        }

        const std::int32_t nextStop = targets[bestIndex];
        targets.erase(targets.begin() + static_cast<std::ptrdiff_t>(bestIndex));
        Move(nextStop);
    }
}

std::int32_t Elevator::GetCurrentFloor() const {
    return currentFloor;
}

std::uint64_t Elevator::GetTravelTime() const {
    return travelTime;
}

std::vector<std::int32_t> Elevator::GetVisited() const {
    return visited;
}

std::vector<std::int32_t> Elevator::GetTargets() const {
    return targets;
}
