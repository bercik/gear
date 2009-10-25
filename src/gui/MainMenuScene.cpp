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

#include "MainMenuScene.h"

#include "common.h"

MainMenuScene::MainMenuScene(CL_GUIComponent *p_parent) :
	Scene(p_parent),
	m_nameLabel(this),
	m_serverLabel(this),
	m_nameLineEdit(this),
	m_serverLineEdit(this),
	m_okButton(this),
	m_errorLabel(this),
	m_quitButton(this),
	m_raceScene(p_parent, &m_player, &m_client)
{
	set_class_name("MainMenuScene");

	m_nameLabel.set_geometry(CL_Rect(100, 100, 180, 120));
	m_nameLabel.set_text("Player's name");

	m_nameLineEdit.set_geometry(CL_Rect(200, 100, 400, 120));

	m_serverLabel.set_geometry(CL_Rect(100, 140, 180, 160));
	m_serverLabel.set_text("Server addr");

	m_serverLineEdit.set_geometry(CL_Rect(200, 140, 400, 160));

	m_okButton.set_geometry(CL_Rect(300, 180, 400, 200));
	m_okButton.set_text("Start Race");

	m_errorLabel.set_geometry(CL_Rect(200, 220, 400, 260));

	m_quitButton.set_geometry(CL_Rect(Stage::getWidth() - 100, Stage::getHeight() - 40, Stage::getWidth() - 20, Stage::getHeight() - 20));
	m_quitButton.set_text("Quit");

	m_okButton.func_clicked().set(this, &MainMenuScene::onOkClicked);
	m_quitButton.func_clicked().set(this, &MainMenuScene::onQuitClicked);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::draw(CL_GraphicContext &p_gc)
{
	CL_Draw::fill(p_gc, 0.0f, 0.0f, get_width(), get_height(), CL_Colorf::white);
}

void MainMenuScene::onOkClicked()
{
	displayError("");

	if (m_nameLineEdit.get_text().empty()) {
		displayError("No player's name choosen");
		return;
	}

	m_player.setName(m_nameLineEdit.get_text());

	if (!m_serverLineEdit.get_text().empty()) {
		// separate server addr from port if possible
		std::vector<CL_TempString> parts = CL_StringHelp::split_text(m_serverLineEdit.get_text(), ":");

		const CL_String serverAddr = parts[0];
		const int serverPort = (parts.size() == 2 ? CL_StringHelp::local8_to_int(parts[1]) : DEFAULT_PORT);

		m_client.connect(serverAddr, serverPort, &m_player);
	}

	// looks good, start the race scene
	Stage::pushScene(&m_raceScene);
}

void MainMenuScene::onQuitClicked()
{
	Stage::popScene();
}

void MainMenuScene::displayError(const CL_String& p_message)
{
	m_errorLabel.set_text(p_message);
	m_errorLabel.request_repaint();

}
