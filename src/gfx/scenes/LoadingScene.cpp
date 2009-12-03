/*
 * Copyright (c) 2009, Piotr Korzuszek
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

#include "LoadingScene.h"

#include "gfx/Stage.h"

LoadingScene::LoadingScene(CL_GUIComponent *p_parent) :
	Scene(p_parent),
	m_controller(this),
	m_label(p_parent)
{
	set_class_name("LoadingScene");
	m_label.set_geometry(CL_Rect(10.0f, Gfx::Stage::getHeight() - 30.0f, Gfx::Stage::getWidth() - 10.0f, Gfx::Stage::getHeight() - 10.0f));
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::initialize()
{
	m_visibleOnScreen = false;
	m_sceneVisibleSigInvoked = false;
}

void LoadingScene::destroy()
{

}

void LoadingScene::draw(CL_GraphicContext &p_gc)
{
	INVOKE_0(sceneRepaint);

	CL_Draw::fill(p_gc, 0.0f, 0.0f, Gfx::Stage::getWidth(), Gfx::Stage::getHeight(), CL_Colorf::white);

	// invoke the scene visible, when I'm sure that is really visible
	// and make it only once per initialize()
	if (!m_visibleOnScreen) {
		m_visibleOnScreen = true;
	} else if (!m_sceneVisibleSigInvoked) {
		INVOKE_0(sceneVisible);
		m_sceneVisibleSigInvoked = true;
	}

}

void LoadingScene::setMessage(const CL_String &p_message)
{
	m_label.set_text(p_message);
}