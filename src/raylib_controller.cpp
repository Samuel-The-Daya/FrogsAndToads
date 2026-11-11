#include "raylib_controller.hpp"
#include "raylib.h"
#include "board_layout.hpp"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {
		// TODO (student): Implement non-blocking keyboard input.

		static_assert(BoardModel::BoardSize <= 9,
			"Single-character commands support at most nine board cells.");


		// Key Reference
		const int key{ GetKeyPressed() };

		// Mouse Vector
		const Vector2 mousePos{ GetMouseX(), GetMouseY() };

		// If Mouse Is Inputted
		// Check the cell which the mouse is hovered over can move
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

			if (BoardLayout::cellAt(mousePos) != std::nullopt) {
				model.tryMove(BoardLayout::cellAt(mousePos).value());
			}

		}

		// If R Key is pressed, reset
		if (IsKeyPressed(KEY_R)) {
			model.reset();
			return;
		}

		// Return when key is not within the board size
		if (key < KEY_ONE || key > KEY_NINE || key > KEY_ZERO + BoardModel::BoardSize) {
			return;
		}

		// Numbered keys select zero-based cells by subtracting '1'.
		// In this way, '1' maps to 0, '2' to 1, '3' to 2, etc.
		model.tryMove(key - '1');
	}
}
