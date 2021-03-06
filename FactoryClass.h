/*
	Factories are responsible for producing units and buildings.
*/

#ifndef FACTORY_H
#define FACTORY_H

#include <AbstractClass.h>
#include <ProgressTimer.h>

class HouseClass;
class TechnoClass;
class TechnoTypeClass;

class FactoryClass : public AbstractClass
{
public:
	enum {AbsID = abs_Factory};

	static DynamicVectorClass<FactoryClass *> *Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~FactoryClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//Constructor
	FactoryClass() : AbstractClass(false)
		JMP_THIS(0x4C98B0);

	//non-virtual
	bool DemandProduction(TechnoTypeClass* pType, HouseClass* pOwner, bool bShouldQueue)
		{ JMP_THIS(0x4C9C70); }
	bool AbandonProduction()
		{ JMP_THIS(0x4C9FF0); }
	unsigned int CountQueued(TechnoTypeClass * pType)
		{ JMP_THIS(0x4CA670); }

	int GetProgress() const
		{ JMP_THIS(0x4CA120); }

	signed int GetBuildTimeFrames() const
		{ JMP_THIS(0x4C9FB0); }

	static bool FindThisOwnerAndProduct(HouseClass *pHouse, TechnoTypeClass *pItem)
	{
		for(int i = 0; i < Array->Count; ++i) {
			FactoryClass *Fact = Array->GetItem(i);
			if(Fact->Owner == pHouse) {
				if(Fact->CountQueued(pItem) > 0) {
					return true;
				}
			}
		}
		return false;
	}

protected:
	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ProgressTimer      Production; // hardcoded to be 54 steps (so cameo clock should be 54 frames)
	DynamicVectorClass<TechnoTypeClass*> QueuedObjects;
	TechnoClass*       InProduction;
	bool               OnHold; // paused when out of money, restored when funds available
	bool               IsDifferent;	//Not sure what this means.
	int                Balance; // credits house still owes us for building this
	int                OriginalBalance;
	int                SpecialItem; // only case of it being used is 0x6AB2D9:
	                                           // if(SpecialItem != -1) { Map->CurrentSWType = 1; }
	HouseClass*        Owner;
	bool               IsCompleteAndSuspended;	//completed production, before next (or waiting to place)
};

#endif
