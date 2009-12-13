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

#include "GameMenuController.h"

#include "gfx/Stage.h"
#include "gfx/race/ui/GameMenu.h"
#include "logic/race/RaceLogic.h"


GameMenuController::GameMenuController(Race::RaceLogic **p_raceLogic, Gfx::GameMenu *p_gameMenu) :
	m_raceLogic(p_raceLogic),
	m_gameMenu(p_gameMenu)
{
	m_gameMenu->func_exit_clicked().set(this, &GameMenuController::onExitClicked);
	m_gameMenu->func_vote_clicked().set(this, &GameMenuController::onVoteClicked);
	m_gameMenu->func_input_pressed().set(this, &GameMenuController::onInputPressed);
}

GameMenuController::~GameMenuController()
{
}

void GameMenuController::onExitClicked()
{
	m_gameMenu->set_visible(false);
	Gfx::Stage::popScene();
}

void GameMenuController::onVoteClicked()
{
	m_gameMenu->set_visible(false);
	(*m_raceLogic)->callAVote(VOTE_RESTART_RACE);
}

bool GameMenuController::onInputPressed(const CL_InputEvent &p_event)
{

	if (m_gameMenu->is_visible()) {
		if (p_event.id == CL_KEY_ESCAPE) {
			m_gameMenu->set_visible(false);
			return true;
		}
	}

	return false;
}
