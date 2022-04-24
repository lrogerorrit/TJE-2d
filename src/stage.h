#pragma once
//#include "../game.h"
#include "utils/commonItems.h"
#include "includes.h"
#include "image.h"
#include "utils/mapHandler.h"
#include "characterHandler.h"
#include "utils/assetManager.h"



class Game;





class stage
{
protected:
	Image& font;
	Game* gameInstance;
	assetManager* assetManagerInstance;
	
	
public:
	
	stage(Image& font);
	
	virtual void render(Image& framebuffer) {};
	virtual void update(double seconds_elapsed) {};
	virtual void initStage() {};
};




class countdownStage :public stage
{
	
private:
	
	
	int cellSize;
	Vector2ub tilePos = Vector2ub(2, 2);
	Vector2 localTilePos = Vector2(0.0f, 0.0f);

	const int RENDER_X_CELLS = 3;
	const int RENDER_Y_CELLS = 3;
	const float x_collisionDist = 8.0f;
	const float y_collisionDist = 5.0f;
	Image& tileset;
	Image& sprite;
	character& localChar;
	
	
	
	void updateTilePosition();
	Vector2ub getTilePosition() { return tilePos; };
	Vector2ub getTileAtPos(float x, float y);
	Vector2ub getTileAtPos(Vector2 pos);

	sCell& getCellAtPos(Vector2 pos);

	sCell& getCellAtPos(float x, float y);
	void renderMap(Image& framebuffer, float dx, float dy);

public:
	countdownStage(Image& tileset, Image& sprite, Image& font, character& localChar) : stage(font), tileset(tileset), sprite(sprite), localChar(localChar) {
		this->cellSize = tileset.width / 16;
	};

	stageType type = stageType::COUNTDOWN;

	void render(Image& framebuffer, float dx, float dy);
	void update(double seconds_elapsed);
	void initStage() {};
	
};

class survivalActions;

enum class eNextCycleGetInfo {
	NONE,
	PLANETCHOICE,
};

class survivalStage :public stage
{
private:
	Image& smallFont;
	survivalActions* survivalActionHandler=nullptr;
	eNextCycleGetInfo infoToFech= eNextCycleGetInfo::NONE;
	void renderSpaceShip(Image& framebuffer);
	void renderInfo(Image& framebuffer);
	void renderUI(Image& framebuffer);
	void renderBackground(Image& framebuffer);
	
	std::string iconTip = "";
	bool tipVisible = false;

public:

	stageType type = stageType::SURVIVAL;
	survivalStage(Image& font, Image& smallFont);

	void choosePlanet();

	void advanceToNextDay();

	void render(Image& framebuffer);
	void update(double seconds_elapsed);
	void initStage() {};

};

struct planetData;




class planetChoosingStage :public stage {
private:
	Image& secondFont;
	int selectedOption=0;
	int fallbackStage = 0;
	
	std::vector< planetData*> planetsData;
	void renderPlanetCard(Image& framebuffer, planetData* planData, int pos);
public:
	stageType type = stageType::PLANET_CHOOSING;
	
	planetChoosingStage(Image& font, Image& secondFont);
	
	void render(Image& framebuffer);
	void update(double seconds_elapsed);
	void initStage(std::vector< planetData>& newData, int fallbackStage);
	int getSelectedOption() {
		return this->selectedOption;
	};
};


class pcStage :public stage {
private:
	Image& secondFont;
	int fallbackStage = 0;
	ePcPage activePage= ePcPage::INVENTORY;
	bool atPlanet = false;
	
	void openPage(ePcPage page);

	//render functions
	void renderInventoryPage(Image& framebuffer);
	void renderConsumePage(Image& framebuffer);
	void renderInfoPage(Image& framebuffer);
	void renderPlanetSpacePage(Image& framebuffer);
	void renderPlanetPlanetPage(Image& framebuffer);
	
	//update functions
	void updateInventoryPage();
	void updateConsumePage();
	void updateInfoPage();
	void updatePlanetSpacePage();
	void updatePlanetPlanetPage();
	
public:
	void render(Image& framebuffer);
	void update(double seconds_elapsed);
	void initStage(int fallbackStage, ePcPage pcPage, bool atPlanet);
	pcStage(Image& font, Image & secondFont);
	
};