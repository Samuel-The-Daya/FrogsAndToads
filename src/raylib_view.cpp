#include "raylib_view.hpp"
#include <string>

namespace FrogToad {

	
	//RaylibView::RaylibView() {
	//	//Texture2D frogSprite{ LoadTexture("resources/hide.png") };
	//	//Texture2D toadSprite{ LoadTexture("resources/peekaboo.png") };
	//}

	//RaylibView::~RaylibView() {
	//	//UnloadTexture(frogSprite);
	//}

	void RaylibView::draw(const BoardModel& model) {
		ClearBackground(RAYWHITE);
		// TODO: Draw the board and game status.

		const int scaleFactor{ 4 };
		const int cellSize{ (windowH() > windowW()) ? windowW() / scaleFactor : windowH() / scaleFactor };

		std::string instructions{ "1.." + std::to_string(BoardModel::BoardSize) + " = Move & R = Restart" };

		// Instructions
		DrawText("Toads & Frogs !!!", ((windowW() - (cellSize * BoardModel::BoardSize)) / 2), windowH()/16, cellSize/3, BLACK);

		for (int i = 0; i < BoardModel::BoardSize; i++)
		{
			// Board Row
			DrawRectangleLines(
				(i*cellSize) + ((windowW() - (cellSize * BoardModel::BoardSize)) / 2),
				windowH()/4,
				cellSize,
				cellSize,
				DARKGRAY
			);

			switch (model.cellAt(i)) {
			case BoardModel::Cell::Frog:
				DrawCircle(
					(i * cellSize) + ((windowW() - (cellSize * BoardModel::BoardSize)) / 2) + (cellSize / 2),
					windowH() / 4 + (cellSize/2),
					cellSize/3,
					GREEN
				);
				break;
			case BoardModel::Cell::Toad:
				DrawCircle(
					(i * cellSize) + ((windowW() - (cellSize * BoardModel::BoardSize)) / 2) + (cellSize / 2),
					windowH() / 4 + (cellSize / 2),
					cellSize / 3,
					DARKGREEN
				);
				break;
			}
			// Number Positions
			DrawText(
				std::to_string(i+1).c_str(),
				(i * cellSize) + ((windowW() - (cellSize * BoardModel::BoardSize)) / 2) + (cellSize / 2),
				windowH() / 2,
				cellSize / 3,
				BLACK
				);
		}


		// Status Lines
		switch (model.state()) {
		case BoardModel::GameState::Solved:
			DrawText("Solved:D R to restart.", ((windowW() - (cellSize * BoardModel::BoardSize)) / 2), windowH() / 1.5, cellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Lost:
			DrawText("No Legal Moves Left :( R to Restart", ((windowW() - (cellSize * BoardModel::BoardSize)) / 2), windowH() / 1.5, cellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Playing:
			DrawText(instructions.c_str(), ((windowW() - (cellSize * BoardModel::BoardSize)) / 2), windowH() / 1.5, cellSize / 3.5, BLACK);
			break;
		}
	}

	int RaylibView::windowW() { return 600; }
	int RaylibView::windowH() { return 300; }
}
