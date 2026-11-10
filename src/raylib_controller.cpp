#include "raylib_controller.hpp"
#include "raylib.h"
#include "board_layout.hpp"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {
		// TODO (student): Implement non-blocking keyboard input.

		static_assert(BoardModel::BoardSize <= 9,
			"Single-character commands support at most nine board cells.");

		const int key{ GetKeyPressed() };

		const Vector2 mousePos{ GetMouseX(), GetMouseY() };

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

			if (BoardLayout::cellAt(mousePos) != std::nullopt) {
				model.tryMove(BoardLayout::cellAt(mousePos).value());
			}

		}

		if (IsKeyPressed(KEY_R)) {
			model.reset();
			return;
		}

		if (key < KEY_ONE || key > KEY_NINE || key > KEY_ZERO + BoardModel::BoardSize) {
			return;
		}

		// Numbered keys select zero-based cells by subtracting '1'.
		// In this way, '1' maps to 0, '2' to 1, '3' to 2, etc.
		model.tryMove(key - '1');
	}
}
