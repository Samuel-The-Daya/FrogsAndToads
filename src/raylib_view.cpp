#include "raylib_view.hpp"
#include <string>
#include "board_layout.hpp"

namespace FrogToad {

	// Constructor
	RaylibView::RaylibView() {

		// Load Textures

		frogSprite = LoadTexture("resources/frog.png");
		toadSprite = LoadTexture("resources/toad.png");
	}

	// Destructor
	RaylibView::~RaylibView() {

		// Unload Textures if they are valid

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

		// Mouse Position Vector
		const Vector2 mousePos{ GetMouseX(), GetMouseY() };

		// If Mouse is over a cell, create a rectangle highlight
		if (BoardLayout::cellAt(mousePos) != std::nullopt) {

			DrawRectangleRec(BoardLayout::cellRect(BoardLayout::cellAt(mousePos).value()), YELLOW);
		}

		// For loop for each cell
		for (int i = 0; i < BoardModel::BoardSize; i++)
		{
			// Board Row

			// Draw a cell
			DrawRectangleLinesEx(BoardLayout::cellRect(i),
				2,
				DARKBLUE
			);

			// Draw a circle (Lilypad !!! Inspired by Ian)
			DrawCircle(
				(i * BoardLayout::CellSize) + BoardLayout::Left + (BoardLayout::CellSize / 2),
				BoardLayout::Top + (BoardLayout::CellSize / 2),
				BoardLayout::CellSize / 3,
				LIME
			);

			// Checks each Cell
			switch (model.cellAt(i)) {
			case BoardModel::Cell::Frog: // Frog State, Draw Frog Texture
				DrawTexturePro(frogSprite,
					Rectangle { 0, 0, static_cast<float>(frogSprite.width), static_cast<float>(frogSprite.height)},
					BoardLayout::cellRect(i),
					Vector2{ 0 , 0 },
					0,
					YELLOW
					);
				break;
			case BoardModel::Cell::Toad: // Toad State, Draw Toad Texture
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
