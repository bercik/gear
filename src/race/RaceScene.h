/*
 * RaceScene.h
 *
 *  Created on: 2009-09-08
 *      Author: chudy
 */

#ifndef RACESCENE_H_
#define RACESCENE_H_

#include "race/Car.h"
#include "race/Level.h"
#include "race/RaceUI.h"
#include "race/Viewport.h"
#include "race/RacePlayer.h"
#include "graphics/Drawable.h"

class Race;

class RaceScene: public Drawable {
	public:
		RaceScene(Race* p_race);
		virtual ~RaceScene();

		virtual void draw(CL_GraphicContext &p_gc);
		virtual void load(CL_GraphicContext &p_gc);

		Viewport& getViewport() { return m_viewport; }

	private:

		/** The Race pointer */
		Race *m_race;

		/** How player sees the scene */
		Viewport m_viewport;

		/** Race user interface */
		RaceUI m_raceUI;


};

#endif /* RACESCENE_H_ */
