#include "raylib_controller.hpp"
#include "raylib.h"
#include <conio.h>

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {
		// TODO (student): Implement non-blocking keyboard input.

		static_assert(BoardModel::BoardSize <= 9,
			"Single-character commands support at most nine board cells.");

		const int key{ _getch() };

		// Arrow and function keys produce a 0 or 0xE0 prefix, then a scan code.
		// Discard the scan code so it cannot become the next command.
		if (key == 0 || key == 0xE0) {
			_getch();
			return;
		}

		if (key == 'r' || key == 'R') {
			model.reset();
			return;
		}

		if (key < '1' || key > '9' || key > '0' + BoardModel::BoardSize) {
			return;
		}

		// Numbered keys select zero-based cells by subtracting '1'.
		// In this way, '1' maps to 0, '2' to 1, '3' to 2, etc.
		model.tryMove(key - '1');
	}
}
