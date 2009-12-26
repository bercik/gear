/*
 * Copyright (c) 2009, Piotr Korzuszek, Paweł Rybarczyk
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <ClanLib/core.h>
#include <ClanLib/network.h>

#if defined(CLIENT)
#include <ClanLib/display.h>
#endif // CLIENT

#include "common.h"

class Player;

namespace Net {
	class CarState;
}

namespace Gfx {
	class RaceGraphics;
}

namespace Race {

class Bound;
class Checkpoint;
class Level;

class Car
{

	SIGNAL_1(inputChanged, const Car&);

	public:

		Car(const Player *p_owner);

		virtual ~Car();


		// attributes

		bool isDrifting() const;

		bool isLocked() const;

		const Checkpoint *getCurrentCheckpoint() const;

		int getLap() const;

		const Player *getOwner() const;

		const CL_Pointf& getPosition() const;

		float getRotation() const;
		
		float getRotationRad() const;

		float getSpeed() const;

		/** @return Car speed in km/s */
		float getSpeedKMS() const;

		
		// operations

		void applyCarState(const Net::CarState &p_carState);

		Net::CarState prepareCarState() const;

		void setAcceleration(bool p_value);

		void setBrake(bool p_value);

		void setLap(int p_lap);

		/**
		 * Sets if car movement should be locked (car won't move).
		 */
		void setLocked(bool p_locked);

		void setTurn(float p_value);

		void setPosition(const CL_Pointf &p_position);

		void setRotation(float p_rotation);
		
		void setHandbrake(bool p_handbrake);

		/**
		 * Sets the car position at selected <code>p_startPosition</code>
		 * which is a number >= 1.
		 *
		 * @param p_startPosition Car start position.
		 */
		void setStartPosition(int p_startPosition);

		void update(unsigned int elapsedTime);

		/**
		 * Sets the new checkpoint and calculates car progress on track.
		 * If lap is reached, then lap number will increase by one.
		 */
		void updateCurrentCheckpoint(const Checkpoint *p_checkpoint);

#if defined(CLIENT)
		/** @return Current collision outline based on car position and rotation */
		CL_CollisionOutline calculateCurrentCollisionOutline() const;

		/** Invoked when collision with bound has occurred */
		void performBoundCollision(const Bound &p_bound);
#endif // CLIENT

	private:

		/** Parent player */
		const Player *m_owner;
		
		/** Parent level */
		Race::Level *m_level;

		/** Lap number */
		int m_lap;

		/** This will help to keep 1/60 iteration speed */
		unsigned m_timeFromLastUpdate;


		// current vehicle state

		/** Central position on map */
		CL_Pointf m_position;

		/** CW rotation from positive X axis */
		CL_Angle m_rotation;

		/** Current speed in map pixels per frame */
		float m_speed;


		// input state

		/** Acceleration switch */
		bool m_inputAccel;

		/** Brake switch */
		bool m_inputBrake;
		
		/** Handbrake switch */
		bool m_inputHandbrake;

		/** Current turn. -1 is maximum left, 0 is center and 1 is maximum right */
		float m_inputTurn;

		/** Locked state. If true then car shoudn't move. */
		bool m_inputLocked;

		/** Checksum value that will tell if input has changed */
		int m_inputChecksum;


		// physics

		/** Move vector for next frame */
		CL_Vec2f m_phyMoveVec;

		/** Car movement rotation */
		CL_Angle m_phyMoveRot;

		/** Speed delta (for isDrifting()) */
		float m_phySpeedDelta;

		/** Did hit test to bound occurred? (FIXME: think again if this is necessary to have this to be a field?) */
		bool m_phyBoundHitTest;

		/** If hit test occurred, this field will keep bound segment that vehicle collided with. */
		CL_LineSegment2f m_phyCollideBound;

#if defined(CLIENT)
		/** Body outline for collision check */
		CL_CollisionOutline m_phyCollisionOutline;
#endif // CLIENT

		
		// checkpoint system

		/** The greatest checkpoint id met on this lap */
		int m_greatestCheckpointId;

		/** Current checkpoint position */
		const Checkpoint *m_currentCheckpoint;



		void update1_60();

		// helpers

		void alignRotation(CL_Angle &p_what, const CL_Angle &p_to, float p_stepRad);

		int calculateInputChecksum() const;

		float normalize(float p_value) const;

		CL_Angle vecToAngle(const CL_Vec2f &p_vec);


		friend class Race::Level;

#if defined(DRAW_CAR_VECTORS) && !defined(NDEBUG)
friend class Gfx::RaceGraphics;
#endif // DRAW_CAR_VECTORS && !NDEBUG

};

} // namespace
