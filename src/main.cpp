//Using SDL and standard IO

#include "Engine/Scene.h"
#include "Engine/Engine.h"
#include "Engine/RTexture.h"
#include "SceneExamples.h"
#include "SceneFont.h"
#include "level.h"
#include <stdio.h>
#include <string>

void preCalc() {
	//Precalculate variables

	calcCircleAlfaRadius4[9][9];

	int radius = 4;
	int radQuad =  radius * radius;
	for(int x=-radius; x<=radius; ++x) {
		int xQuad = x * x;
		for(int y=-radius; y<=radius; ++y) {
			int rq = (xQuad + y*y);
			if(rq <= radQuad ) {
				int alfa =  radius - sqrt(rq);
				alfa =  alfa * 160 / radius;
				calcCircleAlfaRadius4[x + radius][y + radius] = 50 +alfa ;
			} else {
				calcCircleAlfaRadius4[x + radius][y + radius] = 0;
			}
		}
	}



}


bool loadMedia() {
	 preCalc();
	//Loading success flag 
	bool success = true; 

	EngineInst->loadGlobalFont(GlobalFontPath, 18);
	EngineInst->showFPS(true);
	
	success &= EngineInst->loadResources(globalTextures, globalTexturesSize);
//	gScene = new MainScene();
	// uncomment this to instead get scene with first preview of map
	if (!EngineInst->loadAudioResources(globalAudios, globalAudiosSize))
		success = false;

	return success;
}

int main( int argc, char* args[] )
{
	Level *level = new Level(0);
	if( !Engine::Create() )
	{
		printf( "Failed to initialize!\n" );
		PAUSE();
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
			PAUSE();
		}
		else
		{	
			EngineInst->setNextScene(level->getCurrentScene());
			EngineInst->mainLoop();
		}
	}

	EngineInst->unLoadResources(globalTextures, globalTexturesSize);
	EngineInst->unLoadGlobalFont();
	Engine::Destroy();


	delete level;
	return 0;
}
