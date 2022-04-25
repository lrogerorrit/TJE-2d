#pragma once



#define randomInt() (rand()%10)
#define randomIntRange(min,max) (min + ( rand() % ( max - min + 1 ) ))
#define mapValue(x,minIn,maxIn,minOut,maxOut) ((x - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut);

const int MAX_PLANET_OPTIONS = 3;
const int MAX_PC_MENU = 3;

enum class holdingIcon { //Mainly used in uiHandler
	EMPTY,
	FOOD,
	WATER,
	MEDS,
	GUN,
	NA,

};

enum class eItemType //Mainly used in inventoryHandler
{
	EMPTY,
	FOOD,
	WATER,
	MEDS,
	WEAPON,
};

enum class stageType { //Mainly used in stage
	COUNTDOWN,
	SURVIVAL,
	PLANET_CHOOSING,
	PC,
	MULTIPLE_OPTIONS,
	MESSAGE,
	MENU,
	TUTORIAL,
	END,
};

enum class ePcPage { //Mainly used in stage
	
	INVENTORY,
	CREW,
	PLANET
};