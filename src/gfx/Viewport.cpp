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

#include "Viewport.h"

#include "gfx/Stage.h"

namespace Gfx
{

class ViewportImpl
{
	public:

		/** Coordinates of view */
		float m_x, m_y, m_width, m_height;

		/** Stick point */
		const CL_Pointf *m_attachPoint;

		/** Scale (only when attached) */
		float m_scale;

		ViewportImpl() :
			m_x(0),
			m_y(0),
			m_width(Gfx::Stage::getWidth()),
			m_height(Gfx::Stage::getHeight()),
			m_attachPoint(NULL),
			m_scale(1.0f)
		{ /* empty */ }
};

Viewport::Viewport() :
	m_impl(new ViewportImpl)
{
}

Viewport::~Viewport() {
}

void Viewport::prepareGC(CL_GraphicContext &p_gc) {
	p_gc.push_modelview();

	if (m_impl->m_attachPoint != NULL) {
		const int stageWidth = Gfx::Stage::getWidth();
		const int stageHeight = Gfx::Stage::getHeight();

		m_impl->m_x = m_impl->m_attachPoint->x - stageWidth / 2 / m_impl->m_scale;
		m_impl->m_y = m_impl->m_attachPoint->y - stageHeight / 2 / m_impl->m_scale;
		m_impl->m_width = stageWidth / m_impl->m_scale;
		m_impl->m_height = stageHeight / m_impl->m_scale;
	}

	const float horizScale = p_gc.get_width() / m_impl->m_width;
	const float vertScale = p_gc.get_height() / m_impl->m_height;

	p_gc.mult_scale(horizScale, vertScale);

	p_gc.mult_translate(-m_impl->m_x, -m_impl->m_y);
}

void Viewport::finalizeGC(CL_GraphicContext &p_gc) {
	p_gc.pop_modelview();
}

CL_Pointf Viewport::onScreen(const CL_Pointf &p_worldPoint) const
{
	return toScreen(p_worldPoint);
}

CL_Pointf Viewport::toScreen(const CL_Pointf &p_point) const
{
	CL_Pointf result;
	result.x = ((p_point.x - m_impl->m_x) / m_impl->m_width) * Stage::getWidth();
	result.y = ((p_point.y - m_impl->m_y) / m_impl->m_height) * Stage::getHeight();

	return result;
}

CL_Pointf Viewport::toWorld(const CL_Pointf &p_point) const
{
	CL_Pointf result;
	result.x = m_impl->m_x + (p_point.x / Stage::getWidth()) * m_impl->m_width;
	result.y = m_impl->m_y + (p_point.y / Stage::getHeight()) * m_impl->m_height;

	return result;
}

void Viewport::attachTo(const CL_Pointf* p_point)
{
	m_impl->m_attachPoint = p_point;
}

void Viewport::detach()
{
	m_impl->m_attachPoint = NULL;
}

float Viewport::getScale() const
{
	return m_impl->m_scale;
}

void Viewport::setScale(float p_scale)
{
	m_impl->m_scale = p_scale;
}

} // namespace
