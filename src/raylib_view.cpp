#include "raylib_view.hpp"
#include <string>
#include "board_layout.hpp"

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

		std::string instructions{ "1.." + std::to_string(BoardModel::BoardSize) + " = Move & R = Restart" };

		// Instructions
		DrawText("Toads & Frogs !!!", BoardLayout::Left, BoardLayout::Top/3, BoardLayout::CellSize/3, BLACK);

		const Vector2 mousePos{ GetMouseX(), GetMouseY() };

		if (BoardLayout::cellAt(mousePos) != std::nullopt) {

			DrawRectangleRec(BoardLayout::cellRect(BoardLayout::cellAt(mousePos).value()), YELLOW);
		}

		for (int i = 0; i < BoardModel::BoardSize; i++)
		{
			// Board Row
			DrawRectangleLinesEx(BoardLayout::cellRect(i),
				2,
				DARKGRAY
			);

			switch (model.cellAt(i)) {
			case BoardModel::Cell::Frog:
				DrawCircle(
					(i * BoardLayout::CellSize) + BoardLayout::Left + (BoardLayout::CellSize / 2),
					BoardLayout::Top + (BoardLayout::CellSize /2),
					BoardLayout::CellSize /3,
					GREEN
				);
				break;
			case BoardModel::Cell::Toad:
				DrawCircle(
					(i * BoardLayout::CellSize) + BoardLayout::Left + (BoardLayout::CellSize / 2),
					BoardLayout::Top + (BoardLayout::CellSize / 2),
					BoardLayout::CellSize / 3,
					DARKGREEN
				);
				break;
			}
			// Number Positions
			DrawText(
				std::to_string(i+1).c_str(),
				(i * BoardLayout::CellSize) + BoardLayout::Left + (BoardLayout::CellSize / 2),
				BoardLayout::Top/0.5,
				BoardLayout::CellSize / 3,
				BLACK
				);
		}


		// Status Lines
		switch (model.state()) {
		case BoardModel::GameState::Solved:
			DrawText("Solved :D R to restart.", BoardLayout::Left, BoardLayout::Top/1.5, BoardLayout::CellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Lost:
			DrawText("No Legal Moves Left :( R to Restart", BoardLayout::Left, BoardLayout::Top / 1.5, BoardLayout::CellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Playing:
			DrawText(instructions.c_str(), BoardLayout::Left, BoardLayout::Top / 1.5, BoardLayout::CellSize / 3.5, BLACK);
			break;
		}
	}

	int RaylibView::windowW() { return 600; }
	int RaylibView::windowH() { return 300; }
}
