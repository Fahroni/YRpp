/*
	[TeamTypes]
*/

#ifndef TEAMTYPE_H
#define TEAMTYPE_H

#include <AbstractTypeClass.h>
#include <ScriptTypeClass.h>
#include <TaskForceClass.h>

//forward declarations
class TechnoTypeClass;
class TeamClass;
class FootClass;

class TeamTypeClass : public AbstractTypeClass
{
public:
	enum {AbsID = abs_TeamType};

	//Array
	ABSTRACTTYPE_ARRAY(TeamTypeClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TeamTypeClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	static bool LoadFromINIList(CCINIClass *pINI, bool IsGlobal)
		{ PUSH_VAR8(IsGlobal); SET_REG32(ECX, pINI); CALL(0x6F19B0); }

	TeamClass * CreateTeam(HouseClass *pHouse)
		{ JMP_THIS(0x6F09C0); }

	void DestroyAllInstances()
		{ JMP_THIS(0x6F0A70); }

	int GetGroup() const
		{ JMP_THIS(0x6F1870); }

	CellStruct* GetWaypoint(CellStruct *buffer) const
		{ JMP_THIS(0x6F18A0); }

	CellStruct* GetTransportWaypoint(CellStruct *buffer) const
		{ JMP_THIS(0x6F18E0); }

	bool CanRecruitUnit(FootClass *Unit, HouseClass *Owner) const
		{ JMP_THIS(0x6F1320); }

	void FlashAllInstances(int Duration)
		{ JMP_THIS(0x6F1F30); }

	TeamClass * FindFirstInstance() const
		{ JMP_THIS(0x6F1F70); }

	void ProcessTaskForce()
		{ JMP_THIS(0x6F1FA0); }

	static void ProcessAllTaskforces()
		{ JMP_STD(0x6F2040); }

	HouseClass* GetHouse() const
		{ JMP_THIS(0x6F2070); }

	//Constructor
	TeamTypeClass(const char* pID) : AbstractTypeClass(false)
		{ JMP_THIS(0x6F06E0); }

protected:
	TeamTypeClass() : AbstractTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int      ArrayIndex;
	int      Group;
	int      VeteranLevel;
	bool     Loadable;
	bool     Full;
	bool     Annoyance;
	bool     GuardSlower;
	bool     Recruiter;
	bool     Autocreate;
	bool     Prebuild;
	bool     Reinforce;
	bool     Whiner;
	bool     Aggressive;
	bool     LooseRecruit;
	bool     Suicide;
	bool     Droppod;
	bool     UseTransportOrigin;
	bool     field_B2;
	bool     OnTransOnly;
	int      Priority;
	int      Max;
	int      field_BC;
	int      MindControlDecision;
	HouseClass *     Owner;
	int      idxHouse; // idx for MP
	int      TechLevel;
	DWORD    Tag; // TagClass *
	int      Waypoint;
	int      TransportWaypoint;
	int      cntInstances;
	ScriptTypeClass*  ScriptType;
	TaskForceClass*   TaskForce;
	int      IsGlobal;
	int      field_EC;
	bool     field_F0;
	bool     field_F1;
	bool     AvoidThreats;
	bool     IonImmune;
	bool     TransportsReturnOnUnload;
	bool     AreTeamMembersRecruitable;
	bool     IsBaseDefense;
	bool     OnlyTargetHouseEnemy;

};

#endif
