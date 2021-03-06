/*
	Warheads
*/

#ifndef WARHEADTYPE_H
#define WARHEADTYPE_H

#include <AbstractTypeClass.h>

//forward declarations
class AnimTypeClass;
class ParticleTypeClass;
class VoxelAnimTypeClass;

struct WarheadFlags {
	bool ForceFire;
	bool Retaliate;
	bool PassiveAcquire;

	WarheadFlags(bool FF = true, bool Retal = true, bool Acquire = true) : ForceFire(FF), Retaliate(Retal), PassiveAcquire(Acquire) {};
};

class WarheadTypeClass : public AbstractTypeClass
{
public:
	enum {AbsID = abs_WarheadType};

	//Array
	ABSTRACTTYPE_ARRAY(WarheadTypeClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~WarheadTypeClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//AbstractTypeClass

	//Constructor
	WarheadTypeClass(const char* pID) : AbstractTypeClass(false)
		{ JMP_THIS(0x75CEC0); }

protected:
	WarheadTypeClass() : AbstractTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	double  Deform;

	double Verses [0xB];

	double  ProneDamage;
	int     DeformTreshold;

	TypeList<AnimTypeClass*> AnimList;

	InfDeath::Value InfDeath;
	float   CellSpread;
	float   CellInset;
	float   PercentAtMax;
	bool    CausesDelayKill;
	int     DelayKillFrames;
	float   DelayKillAtMax;
	float   CombatLightSize;
	ParticleTypeClass* Particle;
	bool    Wall;
	bool    WallAbsoluteDestroyer;
	bool    PenetratesBunker;
	bool    Wood;
	bool    Tiberium;
	bool    unknown_bool_149;
	bool    Sparky;
	bool    Sonic;
	bool    Fire;
	bool    Conventional;
	bool    Rocker;
	bool    DirectRocker;
	bool    Bright;
	bool    CLDisableRed;
	bool    CLDisableGreen;
	bool    CLDisableBlue;
	bool    EMEffect;
	bool    MindControl;
	bool    Poison;
	bool    IvanBomb;
	bool    ElectricAssault;
	bool    Parasite;
	bool    Temporal;
	bool    IsLocomotor;
	_GUID   Locomotor;
	bool    Airstrike;
	bool    Psychedelic;
	bool    BombDisarm;
	int     Paralyzes;
	bool    Culling;
	bool    MakesDisguise;
	bool    NukeMaker;
	bool    Radiation;
	bool    PsychicDamage;
	bool    AffectsAllies;
	bool    Bullets;
	bool    Veinhole;
	int     ShakeXlo;
	int     ShakeXhi;
	int     ShakeYlo;
	int     ShakeYhi;

	TypeList<VoxelAnimTypeClass*> DebrisTypes;
	TypeList<int> DebrisMaximums;

	int     MaxDebris;
	int     MinDebris;
	PROTECTED_PROPERTY(DWORD, unused_1CC); //???
};

#endif
