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

#include "EditorHelper.h"
#include "EditorBase.h"

#include "common.h"
#include "gfx/Viewport.h"
#include "gfx/Stage.h"
#include "gfx/race/level/Level.h"
#include "logic/race/level/Level.h"
#include "logic/race/level/Track.h"
#include "logic/race/level/TrackPoint.h"

namespace Editor
{
	class EditorTrackImpl;

	class EditorTrack : public EditorBase
	{
	public:
		EditorTrack(Race::Level& p_raceLevel, Gfx::Level& p_gfxLevel, Race::Track& p_track, Gfx::Viewport& p_viewport);

		~EditorTrack();

		virtual void onDraw(CL_GraphicContext &p_gc);

		virtual void onMouseMoved();

		virtual void onHandleInput();

		virtual void onMouseScrolled(bool p_up);

	private:

		void drawTrack(CL_GraphicContext &p_gc);

		void drawNet(CL_GraphicContext &p_gc);

		void setDefaultView();

		void setScale(float set);

		CL_SharedPtr<EditorTrackImpl> m_impl;
	};
}
