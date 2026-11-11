#include "board_layout.hpp"
#include "board_model.hpp"
#include <cassert> // assert() in cellRect()

namespace FrogToad {
    Rectangle BoardLayout::board() {
        // TODO by You.

        return { Left, Top, BoardModel::BoardSize * CellSize, CellSize}; // Replace with the rectangle covering all cells.
    }

    Rectangle BoardLayout::cellRect(int index) {
        // Assert that the index is valid:
        assert(index >= 0 && index < BoardModel::BoardSize);
        
        // TODO by You.
        return { Left + (CellSize * index), Top, CellSize, CellSize}; // Replace with the calculated rectangle for cell at zero-based position index.
    }

    std::optional<int> BoardLayout::cellAt(Vector2 point) {
        // TODO by You. 
        
        // Check collision within the board
        if (CheckCollisionPointRec(point, board())) {

            // Checks which cell is point colliding with
            for (auto i = 0; i < BoardModel::BoardSize; i++) {

                if (CheckCollisionPointRec(point, cellRect(i))) {
                    return i;
                }
            }
        }

        // Return nullopt only when the point is off the board. You can use board() to detect this.
        return std::nullopt; 
    }
}