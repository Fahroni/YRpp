#ifndef TRIGGER_H
#define TRIGGER_H

#include <AbstractClass.h>
#include <TeamTypeClass.h>

//forward declarations
class SuperClass;
class TechnoClass;
class TriggerTypeClass; // TODO: define

class TriggerClass : public AbstractClass
{
public:
	enum {AbsID = abs_Trigger};

	//Static
	static DynamicVectorClass<TriggerClass*>* Array;
	static TriggerTypeClass * __fastcall Find(TriggerTypeClass *pType)
		{ JMP_STD(0x726630); }

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~TriggerClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	// events include 25 (Cross_Horizontal_Line) ?
	bool InvolvesCrossingHorizontal() const
		{ JMP_THIS(0x726250); }

	// events include 26 (Cross_Vertical_Line) ?
	bool InvolvesCrossingVertical() const
		{ JMP_THIS(0x726290); }

	// events include 24 (Entered_Zone) ? // fuck knows what "Zone" is
	bool InvolvesZoneEntry() const
		{ JMP_THIS(0x7262D0); }

	// events include 14 (Allow_Win) ? // god awful logic, creator should curl up and die
	bool InvolvesAllowWin() const
		{ JMP_THIS(0x726310); }

	// events include 27/28 (Global_Set/Cleared) ?
	bool InvolvesGlobalChecking(int idx) const
		{ JMP_THIS(0x726350); }

	void GlobalUpdated(int idx) const
		{ JMP_THIS(0x7263A0); }
	void LocalUpdated(int idx) const
		{ JMP_THIS(0x7263D0); }

	void ResetTimers()
		{ JMP_THIS(0x726400); }

	void MarkEventAsOccured(int idx)
		{ this->EventsAlreadyFired |= (1 << idx); }
	void MarkEventAsNotOccured(int idx)
		{ this->EventsAlreadyFired &= ~(1 << idx); }
	bool HasEventOccured(int idx) const
		{ return (this->EventsAlreadyFired & (1 << idx)) != 0; }

	bool HasBeenDestroyed() const
		{ return this->Destroyed; }

	void SetHouse(HouseClass *House)
		{ this->House = House; }
	HouseClass * GetHouse() const
		{ return this->House; }

	// called whenever an event bubbles up , returns true if all of this trigger's events are up
	bool UpdateEvents(int eventKind, ObjectClass *Object, char a4, bool isRepeating, int a6)
		{ JMP_THIS(0x7246C0); }

	bool FireActions(ObjectClass *Obj, CellStruct Pos)
		{ JMP_THIS(0x7265C0); }

	//Constructor
	TriggerClass(TriggerTypeClass *pType) : AbstractClass(false)
		{ JMP_THIS(0x725FA0); }

protected:
	TriggerClass() : AbstractClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	TriggerTypeClass * Type;
	TriggerClass* AttachedTrigger;
	HouseClass * House;
	bool Destroyed; // ActionClass::DestroyTrigger called on
	bool padding_31;
	bool padding_32;
	bool padding_33;
	TimerStruct ExistenceTimer;
	int EventsAlreadyFired; // bitfield like TechnoClass::Owner
	bool                Enabled;

};

#endif
