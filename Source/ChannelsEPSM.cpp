/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2020 Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** Dn-FamiTracker is (C) 2020-2024 D.P.C.M.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Library General Public License for more details. To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

// This file handles playing of EPSM channels

#include "stdafx.h"
#include "FamiTrackerTypes.h"		// // //
#include "APU/Types.h"		// // //
#include "Instrument.h"		// // //
#include "ChannelHandler.h"
#include "ChannelsEPSM.h"
#include "InstHandler.h"		// // //
#include "InstHandlerVRC7.h"		// // //

#define OPL_NOTE_ON 0x10
#define OPL_SUSTAIN_ON 0x20

CChannelHandlerEPSM::CChannelHandlerEPSM() : 
	FrequencyChannelHandler(0x7FF, 0xF),
	m_iChannel(CHANID_EPSM_SSG1)
{
	m_iVolume = VOL_COLUMN_MAX;
}

void CChannelHandlerEPSM::SetChannelID(int ID)
{
	CChannelHandler::SetChannelID(ID);
	m_iChannel = ID - CHANID_EPSM_SSG1;
}

void CChannelHandlerEPSM::HandleNoteData(stChanNote *pNoteData, int EffColumns)
{
}

bool CChannelHandlerEPSM::HandleEffect(effect_t EffNum, unsigned char EffParam)
{
	FrequencyChannelHandler::HandleEffect(EffNum, EffParam);
	return true;
}

void CChannelHandlerEPSM::HandleEmptyNote()
{
}

void CChannelHandlerEPSM::HandleCut()
{
}

void CChannelHandlerEPSM::UpdateNoteRelease()		// // //
{
	// Note release (Lxx)
	if (m_iNoteRelease > 0) {
		m_iNoteRelease--;
		if (m_iNoteRelease == 0) {
			HandleRelease();
		}
	}
}

void CChannelHandlerEPSM::HandleRelease()
{
}

void CChannelHandlerEPSM::HandleNote(int Note, int Octave)
{
	CChannelHandler::HandleNote(Note, Octave);		// // //
}

int CChannelHandlerEPSM::RunNote(int Octave, int Note)		// // //
{
	// Run the note and handle portamento
	int NewNote = MIDI_NOTE(Octave, Note);
	int NesFreq = TriggerNote(NewNote);

	return NewNote;
}

bool CChannelHandlerEPSM::CreateInstHandler(inst_type_t Type)
{
	return false;
}

void CChannelHandlerEPSM::SetupSlide()		// // //
{
	CChannelHandler::SetupSlide();		// // //
}

int CChannelHandlerEPSM::TriggerNote(int Note)
{
	return Note;		// // //
}

int CChannelHandlerEPSM::CalculateVolume() const
{
	int Volume = (m_iVolume >> VOL_COLUMN_SHIFT) - GetTremolo();
	if (Volume > 15)
		Volume = 15;
	if (Volume < 0)
		Volume = 0;
	return Volume;		// // //
}

int CChannelHandlerEPSM::CalculatePeriod(bool MultiplyByHarmonic) const
{
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// EPSM SSG Channels
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int CEPSMSSGChannel::getDutyMax() const { return 0x0F; }
int CEPSMSSGChannel::GetChannelType() const { return EPSM_SSG; }

void CEPSMSSGChannel::RefreshChannel()
{	
}

void CEPSMSSGChannel::ClearRegisters()
{
}

void CEPSMSSGChannel::RegWrite(unsigned char Reg, unsigned char Value)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// EPSM FM Channels
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int CEPSMFMChannel::getDutyMax() const { return 0x0F; }
int CEPSMFMChannel::GetChannelType() const { return EPSM_FM; }

void CEPSMFMChannel::RefreshChannel()
{
}

void CEPSMFMChannel::ClearRegisters()
{
}

void CEPSMFMChannel::RegWrite(unsigned char Reg, unsigned char Value)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// EPSM Sample Channels
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int CEPSMSampleChannel::getDutyMax() const { return 0x0F; }
int CEPSMSampleChannel::GetChannelType() const { return EPSM_SAMPLE; }

void CEPSMSampleChannel::RefreshChannel()
{
}

void CEPSMSampleChannel::ClearRegisters()
{
}

void CEPSMSampleChannel::RegWrite(unsigned char Reg, unsigned char Value)
{
}
