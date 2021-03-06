/*
	Base class for all game objects.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <AbstractClass.h>
#include <Audio.h>
#include <ObjectTypeClass.h>
#include <TagClass.h>

#include <Helpers/Template.h>

struct SHPStruct;
class LightConvertClass;

//forward declarations
class AnimClass;
class BombClass;
class BuildingTypeClass;
class CellClass;
class InfantryTypeClass;
class TechnoClass;
class TechnoTypeClass;
class WarheadTypeClass;

class HouseTypeClass;

class LineTrail;
struct WeaponStruct;

class ObjectClass : public AbstractClass
{
public:
	enum {AbsDerivateID = ABSFLAGS_ISOBJECT};

	//global arrays
	static DynamicVectorClass<ObjectClass*>* CurrentObjects;

	static DynamicVectorClass<ObjectClass*>* Logics;

	// this actually points to 5 vectors, one for each layer
	static DynamicVectorClass<ObjectClass*>* ObjectsInLayers;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;

	//Destructor
	virtual ~ObjectClass() RX;

	//AbstractClass

	//ObjectClass
	virtual void AnimPointerExpired(AnimClass* pAnim) RX;
	virtual bool IsSelectable() const R0;
	virtual VisualType::Value VisualCharacter(VARIANT_BOOL SpecificOwner, HouseClass * WhoIsAsking) const R0;
	virtual SHPStruct* GetImage() const R0;
	virtual eAction MouseOverCell(CellStruct uCell, bool bUnk1, bool bUnk2) const R0;
	virtual eAction MouseOverObject(ObjectClass* pObj, bool bUnk1) const R0;
	virtual Layer::Value InWhichLayer() const R0;
	virtual bool vt_entry_7C() R0;

 /*
  	Building returns if it is 1x1 and has UndeploysInto
  	inf returns 0
  	unit returns !NonVehicle
  	Aircraft returns IsOnFloor()

  users include:
  452656 - is this building click-repairable
  440C26 - should this building get considered in BaseSpacing
  445A8E - -""-
  51E7D1 - can a VehicleThief be clicked to steal this unit
  51E4D9 - can an engi be clicked to enter this to fix/takeover
  51F0D3 - -""-
  51EA06 - can this building be C4'd?
  51E243 - can a VehicleThief steal this on his own decision
  4F93F3 - should this building's damage raise a BaseUnderAttack?
  442286 - -""-
  44296A - -""-
  741117 - can this be healed by a vehicle?
  6F8242 - can this aircraft be auto-target
  6F85BE - can this aircraft be auto-attacked
  */
	virtual bool IsStrange() const R0;

	virtual TechnoTypeClass* GetTechnoType() const R0;
	virtual ObjectTypeClass* GetType() const R0;
	virtual IndexBitfield<HouseTypeClass *> GetTypeOwners() const R0;
	virtual wchar_t* GetUIName() const R0;
	virtual bool CanBeRepaired() const R0;
	virtual bool CanBeSold() const R0;
	virtual bool IsActive() const R0;

	// can the current player control this unit? (owned by him, not paralyzed, not spawned, not warping, not slaved...)
	virtual bool IsControllable() const R0;

	// stupid! return this->GetCoords(pCrd);
	virtual CoordStruct* GetPosition_0(CoordStruct* pCrd) const R0;

	// gets a building's free dock coordinates for a unit. falls back to this->GetCoords(pCrd);
	virtual CoordStruct* GetDockCoords(CoordStruct* pCrd, TechnoClass* docker) const R0;

	// stupid! guess what happens again?
	virtual CoordStruct* GetPosition_2(CoordStruct* pCrd) const R0;
	virtual CoordStruct* GetFLH(CoordStruct *pDest, int idxWeapon, CoordStruct BaseCoords) const R0;
	virtual CoordStruct* GetExitCoords(CoordStruct* pCrd, DWORD dwUnk) const R0;
	virtual int vt_entry_B8() const R0;
	virtual bool vt_entry_BC(DWORD dwUnk) const R0;
	virtual bool IsStandingStill() const R0;
	virtual bool IsDisguised() const R0;
	virtual bool IsDisguisedAs(HouseClass *target) const R0; // only works correctly on infantry!
	virtual ObjectTypeClass* GetDisguise(bool DisguisedAgainstAllies) const R0;
	virtual HouseClass* GetDisguiseHouse(bool DisguisedAgainstAllies) const R0;

	// remove object from the map
	virtual bool Remove() R0;

	// place the object on the map
	virtual bool Put(CoordStruct* pCrd, Direction::Value dFaceDir) R0;

	// cleanup things (lose line trail, deselect, etc)
	virtual void ReachedEndOfLife(bool Silently) RX;

	virtual void RegisterDestruction(TechnoClass *Destroyer) RX;

	 // maybe Object instead of Techno? Raises Map Events, grants veterancy, increments house kill counters
	virtual void RegisterKill(HouseClass *Destroyer) RX; // ++destroyer's kill counters , etc

	virtual bool SpawnParachuted(CoordStruct *coords) R0;
	virtual void DropAsBomb() RX;
	virtual void UnmarkAllOccupationBits(CoordStruct *coords) RX;
	virtual void MarkAllOccupationBits(CoordStruct *coords) RX;
	virtual void UnInit() RX;
	virtual void Uncloak2() RX;// just calls this->Uncloak(0) on TechnoClass and higher
	virtual int KickOutUnit(TechnoClass* pTechno, CellStruct *pCell) R0;
	virtual bool DrawIfVisible(RectangleStruct *pBounds, bool EvenIfCloaked, DWORD dwUnk3) const R0;
	virtual CellStruct * GetFoundationData(bool IncludeBib) const R0;
	virtual void DrawBehind(Point2D* pLocation, RectangleStruct* pBounds) const RX;
	virtual void DrawExtras(Point2D* pLocation, RectangleStruct* pBounds) const RX; // draws ivan bomb, health bar, talk bubble, etc
	virtual void Draw(Point2D* pLocation, RectangleStruct* pBounds) const RX;
	virtual void DrawAgain(Point2D* pLocation, RectangleStruct* pBounds) const RX; // just forwards the call to Draw
	virtual void Undiscover() RX;
	virtual void See(DWORD dwUnk, DWORD dwUnk2) RX;
	virtual bool UpdatePlacement(PlacementType::Value value) R0;
	virtual RectangleStruct* vt_entry_128(RectangleStruct* pRect) const R0;
	virtual RectangleStruct* vt_entry_12C(RectangleStruct* pRect) R0;
	virtual void DrawRadialIndicator(DWORD dwUnk) RX;
	virtual void MarkForRedraw() RX;
	virtual bool CanBeSelected() const R0;
	virtual bool CanBeSelectedNow() const R0;
	virtual bool vt_entry_140(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3, DWORD dwUnk4) R0;
	virtual bool ClickedAction(eAction Action, ObjectClass *Target, bool bUnk) R0;
	virtual void Flash(int Duration) RX;
	virtual bool Select() R0;
	virtual void Deselect() RX;
	virtual DamageState::Value IronCurtain(int nDuration, HouseClass *pSource, bool ForceShield) R0;
	virtual void StopAirstrikeTimer() RX;
	virtual void StartAirstrikeTimer(int Duration) RX;
	virtual bool IsIronCurtained() const R0;
	virtual bool IsCloseEnough3D(DWORD dwUnk, DWORD dwUnk2) const R0;
	virtual int GetWeaponRange(int idxWeapon) const R0;
	virtual DamageState::Value ReceiveDamage(int* pDamage, int DistanceFromEpicenter, WarheadTypeClass* pWH,
	  ObjectClass* Attacker, BOOL IgnoreDefenses, BOOL PreventPassengerEscape, HouseClass* pAttackingHouse) R0;
	virtual void Destroy() RX;
	virtual void Scatter(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3) RX;
	virtual bool Ignite() R0;
	virtual void Extinguish() RX;
	virtual DWORD GetPointsValue() const R0;
	virtual eMission GetCurrentMission() const R0;
	virtual void RestoreMission(eMission mission) RX;
	virtual void UpdatePosition(int dwUnk) RX;
	virtual BuildingTypeClass* GetFactoryType(bool bOverridePrereqs, bool bOverridePower) const R0;
	virtual void ReceiveCommand(TechnoClass *From, eRadioCommands rcDoThis, DWORD dwUnk3) RX;
	virtual bool DiscoveredBy(HouseClass *pHouse) R0;
	virtual void SetRepairState(int state) RX; // 0 - off, 1 - on, -1 - toggle
	virtual void Sell(DWORD dwUnk) RX;
	virtual void AssignPlanningPath(signed int idxPath, signed char idxWP) RX;
	virtual void vt_entry_1A8(DWORD dwUnk) RX;
	virtual Move::Value IsCellOccupied(CellClass *pDestCell, int facing, int level, CellClass* pSourceCell, bool alt) const R0;
	virtual DWORD vt_entry_1B0(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3, DWORD dwUnk4, DWORD dwUnk5) R0;
	virtual void SetLocation(CoordStruct* pCrd) RX;

// these two work through the object's Location
	virtual CellStruct* GetMapCoords(CellStruct* pUCell) const R0;
	virtual CellClass* GetCell() const R0;

// these two call ::GetCoords_() instead
	virtual CellStruct* GetMapCoordsAgain(CellStruct* pUCell) const R0;
	virtual CellClass* GetCellAgain() const R0;

	virtual int GetHeight() const R0;
	virtual void SetHeight(DWORD dwUnk) RX;
	virtual int GetZ() const R0;
	virtual bool IsBeingWarpedOut() const R0;
	virtual bool IsWarpingIn() const R0;
	virtual bool IsWarpingSomethingOut() const R0;
	virtual bool IsNotWarping() const R0;
	virtual LightConvertClass *GetRemapColour() const R0;

	// technically it takes an ecx<this> , but it's not used and ecx is immediately overwritten on entry
	// draws the mind control line when unit is selected
	static void DrawALinkTo(int src_X, int src_Y, int src_Z, int dst_X, int dst_Y, int dst_Z, ColorStruct color)
		{ PUSH_VAR32(color); PUSH_VAR32(dst_Z); PUSH_VAR32(dst_Y); PUSH_VAR32(dst_X);
		  PUSH_VAR32(src_Z); PUSH_VAR32(src_Y); PUSH_VAR32(src_X); CALL(0x704E40); }

	int DistanceFrom(AbstractClass *that) const
		{ JMP_THIS(0x5F6440); }


	double GetHealthPercentage() const
		{ return double(this->Health) / this->GetType()->Strength; }

	bool IsRedHP() const
		{ JMP_THIS(0x5F5CD0); }

	bool IsYellowHP() const
		{ JMP_THIS(0x5F5D20); }

	bool IsGreenHP() const
		{ JMP_THIS(0x5F5D90); }

	HealthState::Value GetHealthStatus() const
		{ JMP_THIS(0x5F5DD0); }

	void BecomeUntargetable()
		{ JMP_THIS(0x70D4A0); }

	void ReplaceTag(TagClass* pTag)
		{ JMP_THIS(0x5F5B4C); }

	int GetCellLevel() const
		{ JMP_THIS(0x5F5F00); }

	//Constructor
	ObjectClass() : AbstractClass(false)
		{ JMP_THIS(0x5F3900); }

protected:
	ObjectClass(bool) : AbstractClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	PROTECTED_PROPERTY(BYTE,     unknown_24[0x8]);
	int                FallRate; //how fast is it falling down? only works if FallingDown is set below, and actually positive numbers will move the thing UPWARDS
	ObjectClass*       NextObject;	//Next Object in the same cell or transport. This is a linked list of Objects.
	TagClass*          AttachedTag; //Should be TagClass , TODO: change when implemented
	BombClass*         AttachedBomb; //Ivan's little friends.

	AudioController Audio1; // the "mofo" struct, evil evil stuff
	AudioController Audio2; // the "mofo" struct, evil evil stuff

	int                unknown_64;		//idx of OverlayType this is posing as (Mirage Tank)
	bool               BombVisible; // In range of player's bomb seeing units, so should draw it
	int                Health;		//The current Health.
	DWORD              unknown_70;
	bool               IsOnMap; // has this object been placed on the map?
	PROTECTED_PROPERTY(BYTE,     unknown_75[0x3]);
	DWORD              unknown_78;
	DWORD              unknown_7C;
	bool               NeedsRedraw;
	bool               InLimbo; // act as if it doesn't exist - e.g., post mortem state before being deleted
	bool               InOpenToppedTransport;
	bool               IsSelected;	//Has the player selected this Object?
	bool               HasParachute;	//Is this Object parachuting?
	AnimClass*         Parachute;		//Current parachute Anim.
	bool               OnBridge;
	bool               IsFallingDown;
	bool               WasFallingDown; // last falling state when FootClass::Update executed. used to find out whether it changed.
	bool               IsABomb; // if set, will explode after FallingDown brings it to contact with the ground
	bool               IsAlive;		//Self-explanatory.
	PROTECTED_PROPERTY(BYTE,     unknown_91[0xB]);
	CoordStruct Location;		//Absolute current 3D location (in leptons?)
	LineTrail*         LineTrailer;
 };

#endif
