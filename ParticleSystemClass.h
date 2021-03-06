/*
	ParticleSystems
*/

#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include <ObjectClass.h>
#include <ParticleSystemTypeClass.h>
#include <ParticleClass.h>

class ParticleSystemClass : public ObjectClass
{
public:
	enum {AbsID = abs_ParticleSystem};

	//Static
	static DynamicVectorClass<ParticleSystemClass*>* Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleSystemClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//Constructor
	ParticleSystemClass(
		ParticleSystemTypeClass* pParticleSystemType,
		CoordStruct* Crd1,
		AbstractClass* pTarget,
		TechnoClass* pOwner,
		CoordStruct* Crd2,
		DWORD dwUnk) : ObjectClass(false)
			{ JMP_THIS(0x62DC50); }

protected:
	ParticleSystemClass() : ObjectClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ParticleSystemTypeClass* Type;
	CoordStruct  unknown_coords_B0;
	DynamicVectorClass<ParticleClass*> Particles;
	CoordStruct unknown_coords_D4;
	TechnoClass* Owner;
	AbstractClass* Target; // CellClass or TechnoClass
	int          SpawnFrames; //from ParSysTypeClass
	int          Lifetime; //from ParSysTypeClass
	int          SparkSpawnFrames; //from ParSysTypeClass
	int          unknown_int_F4; //defaults to 29
	bool         unknown_bool_F8;
	bool         unknown_bool_F9;
	HouseClass*  OwnerHouse;
};

#endif
