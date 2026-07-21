#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <cstdint>
#include <vector>

class Elevator {
public:
    explicit Elevator(std::int32_t currentFloor);

    void Move(std::int32_t targetFloor);
    void AddDestination(std::int32_t targetFloor);
    void VisitAll();
    void VisitAllNearest();

    [[nodiscard]] std::uint64_t GetTravelTime() const;
    [[nodiscard]] std::vector<std::int32_t> GetVisited() const;
    [[nodiscard]] std::int32_t GetCurrentFloor() const;
    [[nodiscard]] std::vector<std::int32_t> GetTargets() const;

private:
    std::int32_t currentFloor;
    std::uint64_t travelTime{0};
    std::vector<std::int32_t> visited;
    std::vector<std::int32_t> targets;
};

#endif
