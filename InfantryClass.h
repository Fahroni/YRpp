/*
	Infantry
*/

#ifndef INFANTRY_H
#define INFANTRY_H

#include <FootClass.h>
#include <InfantryTypeClass.h>

class InfantryClass : public FootClass
{
public:
	enum {AbsID = abs_Infantry};

	//Static
	static DynamicVectorClass<InfantryClass*>* Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~InfantryClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int	Size() const R0;

	//InfantryClass
	virtual bool IsDeployed() const R0;
	virtual bool PlayAnim(Sequence::Value nAnimNumber, bool bUnk, DWORD dwUnk) R0;

	//Constructor
	InfantryClass(InfantryTypeClass* pType, HouseClass* pOwner) : FootClass(false)
		{ JMP_THIS(0x517A50); }

protected:
	InfantryClass() : FootClass(false)
		{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	InfantryTypeClass* Type;
	Sequence::Value SequenceAnim; //which is currently playing
	TimerStruct unknown_Timer_6C8;
	DWORD          PanicDurationLeft; // set in ReceiveDamage on panicky units
	bool           PermanentBerzerk; // set by script action, not cleared anywhere
	bool           Technician;
	bool           unknown_bool_6DA;
	bool           Crawling;
	bool           unknown_bool_6DC;
	bool           unknown_bool_6DD;
	DWORD          unknown_6E0;
	bool           ShouldDeploy;
	int            unknown_int_6E8;
	PROTECTED_PROPERTY(DWORD, unused_6EC); //??
};

#endif
