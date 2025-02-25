/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "uiHandler.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "characterHandler.h"
#include "utils/mapHandler.h"
#include <cmath>
#include "inventoryHandler.h"
#include "utils/commonItems.h"
#include "utils/assetManager.h"



class stage;
class countdownStage;

class Game
{

private:
	
public:
	static Game* instance;

	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	//some globals
	long frame;
    float time;
	float elapsed_time;
	float totalTime = 0.0f;
	int fps;
	bool must_exit;

	//audio
	Synth synth;

	//custom stuff
	Color bgcolor= Color(0,0,0);
	
	const int RENDER_X_CELLS = 3;
	const int RENDER_Y_CELLS = 3;
	const float y_displ= 13.0f;
	const float x_displ = 0.0f;
	
	const float x_collisionDist = 8.0f;
	const float y_collisionDist = 5.0f;
	



	const int astronautNum = 4;
	character localChar;

	characterHandler charHandler;
	gameMap startMap;
	Vector2ub tilePos;
	Vector2 localTilePos;
	int cellSize;

	bool is_countdownLevel=true;

	uiHandler uihandler;
	inventoryHandler invHandler;

	assetManager* assetMan= NULL;
	
	std::vector<stage*> stages;
	stageType activeStage=stageType::MENU;
	bool deadCheckActive = true;
	bool debugMode = true;
	// make a list of ints of size astronautNum
	

	//ctor
	Game( int window_width, int window_height, SDL_Window* window );
	//Resets game
	void initGame();
	//main functions
	void render( void );
	void update( double dt );

	void showFramebuffer(Image* img);

	//events
	void onKeyDown( SDL_KeyboardEvent event );
	void onKeyUp(SDL_KeyboardEvent event);
	void onMouseButtonDown( SDL_MouseButtonEvent event );
	void onMouseButtonUp(SDL_MouseButtonEvent event);
	void onMouseMove(SDL_MouseMotionEvent event);
	void onMouseWheel(SDL_MouseWheelEvent event);
	void onGamepadButtonDown(SDL_JoyButtonEvent event);
	void onGamepadButtonUp(SDL_JoyButtonEvent event);
	void onResize(int width, int height);

	//audio stuff
	void enableAudio(); //opens audio channel to play sound
	void onAudio(float* buffer, unsigned int len, double time, SDL_AudioSpec &audio_spec); //called constantly to fill the audio buffer

	//custom functions


	inline bool getIsCountdownLevel() { return is_countdownLevel; }
	inline void setIsCountdownLevel(bool value) { is_countdownLevel = value; }
	void setLocalChar(character& plChar) {
		this->localChar = plChar;
	};
	
	
	Vector2ub getTilePosition() { return tilePos; };
	Vector2ub getTileAtPos(float x, float y) {
		return Vector2ub(x / cellSize, (y + y_displ) / cellSize);
	}
	Vector2ub getTileAtPos(Vector2 pos) {
		return Vector2ub(pos.x / cellSize, (pos.y + y_displ) / cellSize);
	}
	
	sCell& getCellAtPos(Vector2 pos) {
		Vector2ub tile= getTileAtPos(pos);
		return startMap.getCell(tile.x, tile.y);
	}
	
	sCell& getCellAtPos(float x, float y) {
		Vector2ub tile = getTileAtPos(x,y);
		return startMap.getCell(tile.x, tile.y);
	}
	
	stage* getActiveStage() {
		return stages[(int)activeStage];
	}
	stage* getStage(stageType reqStage) {
		return stages[(int)reqStage];
	}

	characterHandler& getCharacterHandler() {
		return this->charHandler;
	}
	inventoryHandler& getInventoryHandler() {
		return this->invHandler;
	}
	void setActiveStage(int num) {
		this->activeStage = (stageType)num;
	}
	void setActiveStage(stageType num) {
		this->activeStage = num;
	}
	stage* getStageOfType(stageType type) {
		return stages[(int)type];
	}
	
	Vector2ub mapMousePosition();

	
};


#endif 