#include "board_layout.hpp"
#include "board_model.hpp"
#include <cassert> // assert() in cellRect()

namespace FrogToad {
    Rectangle BoardLayout::board() {
        // TODO by You.



        return {}; // Replace with the rectangle covering all cells.
    }

    Rectangle BoardLayout::cellRect(int index) {
        // Assert that the index is valid:
        assert(index >= 0 && index < BoardModel::BoardSize);
        
        // TODO by You.
        return {}; // Replace with the calculated rectangle for cell at zero-based position index.
    }

    std::optional<int> BoardLayout::cellAt(Vector2 point) {
        // TODO by You. 
        
        // Return nullopt only when the point is off the board. You can use board() to detect this.
        return std::nullopt; 
    }
}