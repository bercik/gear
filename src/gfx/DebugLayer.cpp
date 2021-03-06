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

#include "DebugLayer.h"

DebugLayer::DebugLayer() :
	m_label(CL_Pointf(), "", Gfx::Label::F_REGULAR)
{
}

DebugLayer::~DebugLayer() {
}

void DebugLayer::draw(CL_GraphicContext &p_gc) {

	if (!isLoaded()) {
		load(p_gc);
	}

	m_label.setText("X");

	float x = 5;
	float y = 15;

	for (std::map<CL_String, CL_String>::iterator itor = m_messages.begin(); itor != m_messages.end(); ++itor) {
		m_label.setText(itor->first + ": " + itor->second);
		m_label.setPosition(CL_Pointf(x, y));

		m_label.draw(p_gc);
		y += m_labelHeight;
	}
}

void DebugLayer::load(CL_GraphicContext &p_gc)
{
	m_label.load(p_gc);

	m_label.setText("X");
	m_labelHeight = m_label.size(p_gc).height;

	Drawable::load(p_gc);
}
