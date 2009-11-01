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

#include "CarState.h"

#include "network/events.h"

namespace Net {

CL_NetGameEvent CarState::buildEvent() const
{
	CL_NetGameEvent event(EVENT_CAR_STATE);

	event.add_argument(m_position.x);
	event.add_argument(m_position.y);

	event.add_argument(m_rotation.to_radians());

	event.add_argument(m_movement.x);
	event.add_argument(m_movement.y);

	event.add_argument(m_accel);
	event.add_argument(m_turn);

	return event;
}

void CarState::parseEvent(const CL_NetGameEvent &p_event)
{
	assert(p_event.get_name() == EVENT_CAR_STATE);

	m_position.x = p_event.get_argument(0);
	m_position.y = p_event.get_argument(1);

	m_rotation.from_radians(p_event.get_argument(2));

	m_movement.x = p_event.get_argument(3);
	m_movement.y = p_event.get_argument(4);

	m_accel = p_event.get_argument(5);
	m_turn = p_event.get_argument(6);
}

} // namespace
