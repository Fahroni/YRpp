#ifndef TAG_H
#define TAG_H

#include <AbstractClass.h>
#include <TriggerClass.h>

//forward declarations
class TagTypeClass; // TODO: define

class TagClass : public AbstractClass
{
public:
	enum {AbsID = abs_Tag};

	//Static
	static DynamicVectorClass<TagClass*>* Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~TagClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//Constructor
	TagClass(TagTypeClass *pType) : AbstractClass(false)
		{ JMP_THIS(0x6E4DE0); }

	bool RaiseEvent(TriggerEvent::Value eventKind, ObjectClass* tagObject, CellStruct loc, bool isRepeating, TechnoClass* source)
		{ JMP_THIS(0x6E53A0); }

	bool IsTriggerRepeating() const
		{ JMP_THIS(0x6E57C0); }

protected:
	TagClass() : AbstractClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	TagTypeClass * Type;
	TriggerClass * AttachedTrigger;
	int InstanceCount;
	CellStruct * DefaultCoords;
	char unknown_34;
	bool IsExecuting;
	char unknown_36;
	char unknown_37;
};

#endif
