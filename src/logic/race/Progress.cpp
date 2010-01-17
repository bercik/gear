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

#include "Progress.h"

#include <map>

#include "common.h"
#include "logic/race/Car.h"
#include "logic/race/level/Checkpoint.h"
#include "logic/race/level/Level.h"
#include "logic/race/level/Track.h"
#include "logic/race/level/TrackTriangulator.h"
#include "logic/race/level/TrackSegment.h"

namespace Race
{

struct ProgressInfo
{
	int m_lapNum;
	Checkpoint m_checkpoint;
};

class ProgressImpl
{
	public:

		typedef std::map<const Car*, ProgressInfo> TCarProgressMap;

		typedef std::vector<Checkpoint> TCheckpointList;


		// fields

		TCarProgressMap m_cars;

		TCheckpointList m_chkpts;

		const Level &m_level;

		bool m_initd;


		// methods

		ProgressImpl(const Level &p_level) :
			m_level(p_level),
			m_initd(false)
		{ /* empty */ }
};

Progress::Progress(const Level &p_level) :
	m_impl(new ProgressImpl(p_level))
{
	// empty
}

Progress::~Progress()
{
	destroy();
}

void Progress::addCar(const Car &p_car)
{
	G_ASSERT(m_impl->m_initd);

	const ProgressInfo pinfo = {0, m_impl->m_chkpts[0]};
	m_impl->m_cars[&p_car] = pinfo;
}

void Progress::initialize()
{
	if (m_impl->m_initd) {
		return;
	}

	G_ASSERT(m_impl->m_level.isLoaded() && "level must be loaded first");


	// load checkpoints
	const Track &track = m_impl->m_level.getTrack();
	const TrackTriangulator &triang = m_impl->m_level.getTrackTriangulator();
	const int segCount = track.getPointCount();

	int chkPtIdx = 0;

	for (int i = 0; i < segCount; ++i) {
		const TrackSegment &seg = triang.getSegment(i);

		// from mid points of track
		const std::vector<CL_Pointf> &midPts = seg.getMidPoints();
		const int midCount = midPts.size();

		for (int j = 0; j < midCount; ++j) {
			m_impl->m_chkpts.push_back(Checkpoint(chkPtIdx++, midPts[j]));
		}
	}

	G_ASSERT(m_impl->m_chkpts.size() > 0 && "no checkpoints loaded");

	m_impl->m_initd = true;

}

void Progress::destroy()
{
	if (!m_impl->m_initd) {
		return;
	}

	m_impl->m_chkpts.clear();
	m_impl->m_cars.clear();
}

void Progress::removeCar(const Car &p_car)
{
	G_ASSERT(m_impl->m_initd);

	ProgressImpl::TCarProgressMap::iterator itor =
			m_impl->m_cars.find(&p_car);

	G_ASSERT(itor != m_impl->m_cars.end());

	m_impl->m_cars.erase(itor);
}

int Progress::getLapNumber(const Car &p_car) const
{
	G_ASSERT(m_impl->m_initd);

	ProgressImpl::TCarProgressMap::const_iterator itor =
			m_impl->m_cars.find(&p_car);

	G_ASSERT(itor != m_impl->m_cars.end());

	return itor->second.m_lapNum;
}

const Checkpoint &Progress::getCheckpoint(const Car &p_car) const
{
	G_ASSERT(m_impl->m_initd);

	ProgressImpl::TCarProgressMap::const_iterator itor =
			m_impl->m_cars.find(&p_car);

	G_ASSERT(itor != m_impl->m_cars.end());


	return itor->second.m_checkpoint;
}

const Checkpoint &Progress::getCheckpoint(int p_idx) const
{
	G_ASSERT(m_impl->m_initd);
	G_ASSERT(p_idx >= 0 && p_idx < static_cast<signed>(m_impl->m_chkpts.size()));

	return m_impl->m_chkpts[p_idx];
}

int Progress::getCheckpointCount() const
{
	G_ASSERT(m_impl->m_initd);
	return static_cast<signed>(m_impl->m_chkpts.size());
}

} // namespace