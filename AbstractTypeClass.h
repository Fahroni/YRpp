/*
	AbstractTypes are abstract template objects initialized by INI files
*/
#ifndef ABSTRACTTYPE_H
#define ABSTRACTTYPE_H

#include <AbstractClass.h>

//forward declarations
class CCINIClass;

//Macro for the static Array of every AbstractTypeClass!
#define ABSTRACTTYPE_ARRAY(class_name)	public:\
	static DynamicVectorClass<class_name*>* Array;\
	static class_name* Find(const char* pID)\
	{\
		for(int i = 0; i < Array->Count; ++i)\
			if(!_strcmpi(Array->GetItem(i)->ID, pID))\
				return Array->GetItem(i);\
		return NULL;\
	}\
	static class_name* FindOrAllocate(const char* pID)\
	{\
		class_name* pRet = Find(pID);\
		if(pRet)\
			return pRet;\
		else\
			return new class_name(pID);\
	}\
	static int FindIndex(const char* pID)\
	{\
		for(int i = 0; i < Array->Count; ++i)\
			if(!_strcmpi(Array->GetItem(i)->ID, pID))\
				return i;\
		return -1;\
	}
//---

class AbstractTypeClass : public AbstractClass
{
public:
	enum {AbsID = abs_Abstract};

	//Static
	static DynamicVectorClass<AbstractTypeClass*>* Array;

	//Destructor
	virtual ~AbstractTypeClass() RX;

	//AbstractTypeClass
	virtual void LoadTheaterSpecificArt(TheaterType::Value th_type) RX;
	virtual bool LoadFromINI(CCINIClass* pINI) R0;
	virtual bool SaveToINI(CCINIClass* pINI) R0;

	//Constructor
	AbstractTypeClass(const char* pID) : AbstractClass(false)
		{ JMP_THIS(0x410800); }

	char *get_ID()
		{ return this->ID; }

protected:
	AbstractTypeClass() : AbstractClass(false) { }
	AbstractTypeClass(bool X) : AbstractClass(X) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	char ID [0x18];
	PROTECTED_PROPERTY(BYTE, zero_3C);
	char UINameLabel [0x20];
	wchar_t* UIName;
	char Name [0x31];
};

#endif
