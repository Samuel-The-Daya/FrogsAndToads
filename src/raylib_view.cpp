#include "raylib_view.hpp"
#include <string>
#include "board_layout.hpp"

namespace FrogToad {

	
	RaylibView::RaylibView() {

		frogSprite = LoadTexture("resources/frog.png");
		toadSprite = LoadTexture("resources/toad.png");
	}

	RaylibView::~RaylibView() {
		if (IsTextureValid(frogSprite)) {
			UnloadTexture(frogSprite);
		}

		if (IsTextureValid(toadSprite)) {
			UnloadTexture(toadSprite);
		}
		
	}

	void RaylibView::draw(const BoardModel& model) {
		ClearBackground(SKYBLUE);
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
				DARKBLUE
			);

			DrawCircle(
				(i * BoardLayout::CellSize) + BoardLayout::Left + (BoardLayout::CellSize / 2),
				BoardLayout::Top + (BoardLayout::CellSize / 2),
				BoardLayout::CellSize / 3,
				LIME
			);

			switch (model.cellAt(i)) {
			case BoardModel::Cell::Frog:
				DrawTexturePro(frogSprite,
					Rectangle { 0, 0, static_cast<float>(frogSprite.width), static_cast<float>(frogSprite.height)},
					BoardLayout::cellRect(i),
					Vector2{ 0 , 0 },
					0,
					YELLOW
					);
				break;
			case BoardModel::Cell::Toad:
				DrawTexturePro(toadSprite,
					Rectangle{ 0, 0, static_cast<float>(toadSprite.width), static_cast<float>(toadSprite.height) },
					BoardLayout::cellRect(i),
					Vector2{ 0 , 0 },
					0,
					ORANGE
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
			DrawText("Solved :D R to restart.", BoardLayout::Left, BoardLayout::Top / 0.4 , BoardLayout::CellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Lost:
			DrawText("No Legal Moves Left :( R to Restart", BoardLayout::Left, BoardLayout::Top / 0.4, BoardLayout::CellSize / 3.5, BLACK);
			break;
		case BoardModel::GameState::Playing:
			DrawText(instructions.c_str(), BoardLayout::Left, BoardLayout::Top / 0.4, BoardLayout::CellSize / 3.5, BLACK);
			break;
		}
	}

	int RaylibView::windowW() { return 600; }
	int RaylibView::windowH() { return 300; }
}
