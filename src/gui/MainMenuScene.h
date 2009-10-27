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

#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "Player.h"
#include "graphics/Scene.h"
#include "network/Client.h"
#include "race/RaceScene.h"
#include "gui/LoadingScene.h"

class MainMenuScene: public Scene {
	public:
		MainMenuScene(CL_GUIComponent *p_parent);

		virtual ~MainMenuScene();

		virtual void draw(CL_GraphicContext &p_gc);

	private:
		// gui components

		CL_Label m_nameLabel, m_serverLabel;

		CL_LineEdit m_nameLineEdit, m_serverLineEdit;

		CL_PushButton m_okButton;

		CL_Label m_errorLabel;

		CL_PushButton m_quitButton;

		// game mechanics

		Player m_player;

		Client m_client;

		// further scenes

		LoadingScene m_loadingScene;

		RaceScene m_raceScene;

		// other

		/** The slot container */
		CL_SlotContainer m_slots;


		//
		// Methods
		//

		// action slots

		void onOkClicked();

		void onQuitClicked();


		void onClientConnected();

		void onClientInitialized();

		// other

		void displayError(const CL_String& p_message);
};

#endif /* MAINMENUSCENE_H_ */
