/*
 * Copyright (c) 2009-2010, Piotr Korzuszek
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
#include <ClanLib/display.h>
#include <vector>

#include "EditorHelper.h"

#include "common.h"

#include "gfx/race/level/Level.h"
#include "logic/race/level/Level.h"
#include "logic/race/level/Track.h"
#include "gfx/Viewport.h"

namespace Editor
{
	class EditorBase
	{
	public:
		EditorBase(Race::Level& p_raceLevel, Gfx::Level& p_gfxLevel, Race::Track& p_track, Gfx::Viewport& p_viewport);

		virtual ~EditorBase();

		void draw(CL_GraphicContext &p_gc);

		void load(CL_GraphicContext &p_gc);

		void mouseMoved(const CL_Pointf &p_mousePos, const CL_Pointf &p_inconditionalMousePos);

		void mouseScrolled(bool p_up);

		void update(unsigned int p_timeElapsed);

		void handleInput(InputState p_state, const CL_InputEvent& p_event);

	protected:
		virtual void onDraw(CL_GraphicContext &p_gc);

		virtual void onLoad(CL_GraphicContext &p_gc);

		virtual void onMouseMoved();

		virtual void onMouseScrolled(bool p_up);

		virtual void onUpdate(unsigned int p_timeElapsed);

		virtual void onHandleInput();

		bool hasContainsKey(int p_key);

		const std::vector<int>& getKeys() const;

		bool isFirstKey(int p_key);

		bool isSecondKey(int p_key);

		CL_Pointf m_lastMousePos;

		CL_Pointf m_mousePos;

		CL_Pointf m_deltaMousePos;

		CL_Pointf m_inconditionalMousePos;

		CL_Pointf m_inconditionalLastMousePos;

		CL_Pointf m_inconditionalDeltaMousePos;

		bool m_alt;

		bool m_ctrl;

		bool m_shift;

		Race::Level& m_raceLevel;
		
		Gfx::Level& m_gfxLevel;

		Race::Track& m_track;

		Gfx::Viewport& m_viewport;

	private:
		void addKey(int p_key);

		void removeKey(int p_key);

		int findKey(int p_key);

		std::vector<int> m_keys;
	};
}
