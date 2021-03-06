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

#include "Stage.h"

#include "gfx/DebugLayer.h"
#include "gfx/Scene.h"

namespace Gfx {

int Stage::m_width = 0;

int Stage::m_height = 0;

CL_ResourceManager *Stage::m_resourceManager = NULL;

DebugLayer *Stage::m_debugLayer = NULL;

std::stack<Scene*> Stage::m_sceneStack;

void Stage::pushScene(Scene *p_scene)
{
//	cl_log_event("stage", "scene push: %1", p_scene->get_class_name());
	m_sceneStack.push(p_scene);

	p_scene->pushed();
}

void Stage::popScene()
{
	Scene *scene = peekScene();

//	cl_log_event("stage", "scene pop: %1", scene->get_class_name());
	m_sceneStack.pop();

	scene->poped();
}

Scene *Stage::peekScene()
{
	return m_sceneStack.empty() ? NULL : m_sceneStack.top();
}

void Stage::replaceScene(Scene *p_scene)
{
//	cl_log_event("stage", "scene replace: %1", p_scene->get_class_name());
	m_sceneStack.pop();
	m_sceneStack.push(p_scene);
}

} // namespace
