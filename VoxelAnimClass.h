/*
	Voxel Animations
*/

#ifndef VOXELANIM_H
#define VOXELANIM_H

#include <ObjectClass.h>
#include <VoxelAnimTypeClass.h>
#include <BounceClass.h>

//forward declarations
class HouseClass;
class ParticleSystemClass;

class VoxelAnimClass : public ObjectClass
{
public:
	enum {AbsID = abs_VoxelAnim};

	//Static
	static DynamicVectorClass<VoxelAnimClass*>* Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~VoxelAnimClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int	Size() const R0;

	//ObjectClass
	//VoxelAnimClass

	//Constructor
	VoxelAnimClass(VoxelAnimTypeClass* pVoxelAnimType, CoordStruct* pLocation, HouseClass* pOwnerHouse)
		: ObjectClass(false)
	{
		JMP_THIS(0x7493B0);
	}

protected:
	VoxelAnimClass() : ObjectClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	PROTECTED_PROPERTY(DWORD, unused_AC);
	BounceClass Bounce;
	int unknown_int_100;
	VoxelAnimTypeClass* Type;
	ParticleSystemClass* AttachedSystem;
	HouseClass* OwnerHouse;
	bool TimeToDie; // remove on next update
	PROTECTED_PROPERTY(BYTE, unused_111[3]);
	AudioController Audio3;
	AudioController Audio4;
	bool Invisible; // don't draw, but Update state anyway
	PROTECTED_PROPERTY(BYTE, unused_13D[3]);
	int Duration; // counting down to zero
	PROTECTED_PROPERTY(DWORD, unused_144);
};

#endif
