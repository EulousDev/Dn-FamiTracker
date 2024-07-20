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

#pragma once

//
// Derived channels, EPSM
//

enum epsm_channel_type {
	EPSM_FM,
	EPSM_SSG,
	EPSM_SAMPLE
};

class CChannelHandlerInterfaceEPSM;

class CChannelHandlerEPSM : public FrequencyChannelHandler, public CChannelHandlerInterfaceEPSM {		// // //
public:
	CChannelHandlerEPSM();
	void	SetChannelID(int ID) override;

protected:
	void	HandleNoteData(stChanNote *pNoteData, int EffColumns) override;
	bool	HandleEffect(effect_t EffNum, unsigned char EffParam) override;		// // //
	void	HandleEmptyNote() override;
	void	HandleCut() override;
	void	HandleRelease() override;
	void	HandleNote(int Note, int Octave) override;
	int		RunNote(int Octave, int Note) override;		// // //
	bool	CreateInstHandler(inst_type_t Type) override;		// // //
	void	SetupSlide() override;		// // //
	int		CalculateVolume() const override;
	int		CalculatePeriod(bool MultiplyByHarmonic = true) const override;		// // //

	void	UpdateNoteRelease() override;		// // //
	int		TriggerNote(int Note) override;

protected:
	unsigned char m_iChannel;
};


class CEPSMSSGChannel : public CChannelHandlerEPSM {
public:
	CEPSMSSGChannel() : CChannelHandlerEPSM() { }
	void RefreshChannel();

	int getDutyMax() const override;
	int GetChannelType() const;
protected:

	void ClearRegisters();
private:
	void RegWrite(unsigned char Reg, unsigned char Value);
};

class CEPSMFMChannel : public CChannelHandlerEPSM {
public:
	CEPSMFMChannel() : CChannelHandlerEPSM() { }
	void RefreshChannel();

	int getDutyMax() const override;
	int GetChannelType() const;
protected:

	void ClearRegisters();
private:
	void RegWrite(unsigned char Reg, unsigned char Value);
};

class CEPSMSampleChannel : public CChannelHandlerEPSM {
public:
	CEPSMSampleChannel() : CChannelHandlerEPSM() { }
	void RefreshChannel();

	int getDutyMax() const override;
	int GetChannelType() const;
protected:
	void ClearRegisters();
private:
	void RegWrite(unsigned char Reg, unsigned char Value);
};

