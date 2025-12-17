# 2048-tile-twister
Simple Tile Twister game in C++

## project architecture

```
2048-tile-twister/
│   README.md
│   LICENSE
├── include/
├── src/
|   |── main.cpp
│   ├── core/
│   │   ├── Game.h/.cpp
│   │   ├── Grid.h/.cpp
│   │   └── Tile.h/.cpp
│   └── views/
│       ├── Window.h/.cpp
│       ├── GameObject.h/.cpp
│       ├── TileView.h/.cpp
│       ├── GridView.h/.cpp
│       └── InputManager.h/.cpp
```

## class diagram (Mermaid)

```mermaid
classDiagram
	class Game {
		-Grid grid
		+void move(Direction)
		+void addRandomTile()
		+bool isGameOver()
	}
	class Grid {
		-Tile[4][4] tiles
		+bool move(Direction)
		+bool canMove()
		+void mergeTiles(Direction)
		+void addTile(Tile)
	}
	class Tile {
		-int value
		-int x
		-int y
		+int getValue()
		+(x, y) getPosition()
	}
	class Window {
		+void init()
		+void render()
		+void handleEvents()
	}
	class GameObject {
		<<abstract>>
		-int x
		-int y
		-int width
		-int height
		+virtual void render()
	}
	class TileView {
		+void render()
	}
	class GridView {
		+void render()
	}
	class InputManager {
		+Direction getInput()
	}
	Game --> Grid
	Grid --> Tile
	Window --> GameObject
	TileView --|> GameObject
	GridView --|> GameObject
	Window --> InputManager
	Window --> GridView
	GridView --> TileView
```
## Inner workings

The core classes (Game, Grid, Tile) manage the state and rules of the game. They do not depend on SDL or rendering code.
The SDL "Views" classes (Window, GameObject, GridView, TileView, etc.) are responsible for displaying the game and handling user input. They depend on the core classes to get the current state of the game.

The main loop (in main.cpp or Window) creates an instance of the Game class (from core).
The GridView and TileView classes (in sdl) receive a reference or pointer to the Grid and Tile objects (from core) to render the current state.
When the user presses a key, the InputManager (in sdl) translates it into a direction and calls the appropriate method on the Game object (in core), which updates the game state.
After each update, the SDL classes re-render the new state by querying the core objects.
