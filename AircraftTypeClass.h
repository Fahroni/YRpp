#ifndef AIRCRAFTTYPE_H
#define AIRCRAFTTYPE_H

#include <TechnoTypeClass.h>

class AircraftTypeClass : public TechnoTypeClass
{
public:
	enum {AbsID = abs_AircraftType};

	//Array
	ABSTRACTTYPE_ARRAY(AircraftTypeClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//Destructor
	virtual ~AircraftTypeClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int	Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//TechnoTypeClass

	//Constructor
	AircraftTypeClass(const char* pID) : TechnoTypeClass(false)
		{ JMP_THIS(0x41C8B0); }

protected:
	//default contructor, only used by polymorphism
	AircraftTypeClass() : TechnoTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	bool Carryall;
	AnimTypeClass* Trailer;
	int SpawnDelay;
	bool Rotors;
	bool CustomRotor;
	bool Landable;
	bool FlyBy;
	bool FlyBack;
	bool AirportBound;
	bool Fighter;
};

#endif
