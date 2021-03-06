/*
	OverlayTypes are initialized by INI files.
*/

#ifndef OVERLAYTYPE_H
#define OVERLAYTYPE_H

#include <ObjectTypeClass.h>

//forward declarations
class AnimTypeClass;

class OverlayTypeClass : public ObjectTypeClass
{
public:
	enum {AbsID = abs_OverlayType};

	//Array
	ABSTRACTTYPE_ARRAY(OverlayTypeClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~OverlayTypeClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//ObjectTypeClass
	virtual CoordStruct* vt_entry_6C(CoordStruct* pDest,CoordStruct* pSrc) R0;

	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords,HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//OverlayTypeClass
	virtual void Draw(Point2D* pClientCoords, RectangleStruct* pClipRect, int nFrame) RX;

	//Constructor
	OverlayTypeClass(const char* pID) : ObjectTypeClass(false)
		{ JMP_THIS(0x5FE250); }

protected:
	OverlayTypeClass() : ObjectTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int                ArrayIndex;
	eLandType          LandType;
	AnimTypeClass*     CellAnim;
	int                DamageLevels;
	int                Strength;
	bool               Wall;
	bool               Tiberium;
	bool               Crate;
	bool               CrateTrigger;
	bool               NoUseTileLandType;
	bool               IsVeinholeMonster;
	bool               IsVeins;
	bool               ImageLoaded;	//not INI
	bool               Explodes;
	bool               ChainReaction;
	bool               Overrides;
	bool               DrawFlat;
	bool               IsRubble;
	bool               IsARock;
	ColorStruct RadarColor;

};

#endif
