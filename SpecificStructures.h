#ifndef SPECIAL_STRUCTURES_H
#define SPECIAL_STRUCTURES_H

// this file contains a few structures representing function arguments on the stack (normally all except `this`)

// i.e. this struct can be used to read the args to ObjectClass::ReceiveDamage
struct args_ReceiveDamage {
	int *Damage;
	int DistanceToEpicenter;
	WarheadTypeClass *WH;
	TechnoClass *Attacker;
	BOOL IgnoreDefenses;
	/* don't lowercase these - padding voodoo */
	BOOL PreventsPassengerEscape;
	HouseClass *SourceHouse;
};


// this helper class is meant to represent a FPU fcomp or similar instruction result
// hook it after fnstsw $reg, feed it the $reg, and call the info functions
// need to know what you're comparing with what, though... oh well, leave it alone then
class FPUControl {
	private:
		DWORD statusWord;
	public:
		FPUControl(DWORD fnstsw): statusWord(fnstsw) { };

		bool isEqual() {
			return (this->statusWord & 0x4000) != 0;
		}

		bool isLess() {
			return (this->statusWord & 0x100) != 0;
		}
};

#endif
