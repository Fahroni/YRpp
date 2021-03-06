#ifndef DVC_H
#define DVC_H

#include <YRPPCore.h>
#include <Helpers/Macro.h>
#include <Interfaces.h>
#include <Memory.h>

//========================================================================
//=== VectorClass ========================================================
//========================================================================

template <typename T> class VectorClass
{
public:
	virtual ~VectorClass() {
		Clear();
	}

	virtual bool IsEqual(VectorClass* pVec) const {
		if(this->Capacity == pVec->Capacity) {
			if(this->Capacity == 0) {
				return true;
			}

			for(int i = 0; i < this->Capacity; ++i) {
				if(this->Items[i] == pVec->Items[i]) {
					continue; // kapow! don't rewrite this to != unless you know why you're doing it
				}
				return false;
			}
			return true;
		}
		return false;
	}


	virtual bool SetCapacity(int nNewCapacity, T* pMem) {
		if(nNewCapacity != 0) {
			this->IsInitialized = false;

			bool bMustAllocate = (pMem == NULL);
			if(!pMem) {
				pMem = new T[nNewCapacity];
// in theory, as long as new/delete pairs are matched to the same allocator, shit should work just fine
//				GAME_ALLOC_ARR(T, nNewCapacity, pMem);
			}

			IsInitialized = true;
			if(!pMem) {
				return false;
			}

			if(this->Items) {
				int n = (nNewCapacity < this->Capacity) ? nNewCapacity : this->Capacity;
				for(int i = 0; i < n; ++i) {
					pMem[i] = this->Items[i];
				}

				if(IsAllocated) {
					delete [] this->Items;
//					GAME_DEALLOC_ARR(this->Items);
					this->Items = NULL;
				}
			}

			this->IsAllocated = bMustAllocate;
			this->Items = pMem;
			this->Capacity = nNewCapacity;
		} else {
			this->Clear();
		}
		return true;
	}

	virtual void Clear() {
		if(this->Items && this->IsAllocated) {
			delete[] this->Items;
//			GAME_DEALLOC_ARR(this->Items);
			this->Items = NULL;
		}
		this->IsAllocated = false;
		this->Capacity = 0;
	}

	virtual int FindItemIndex(T *tItem) const {
		if(!this->IsInitialized) {
			return 0;
		}

		for(int i = 0; i < this->Capacity; ++i) {
			if(this->Items[i] == *tItem) {
				return i;
			}
		}

		return -1;
	}

	virtual int GetItemIndex(T* pItem) const {
		if(!this->IsInitialized) return 0;
		return (pItem - this->Items) / sizeof(T);
	}

	virtual T GetItem(int i) {
		return this->Items[i];
	}

	T& operator [](int i) {
		return this->Items[i];
	}

	const T& operator [](int i) const {
		return this->Items[i];
	}

	VectorClass() {
		this->Items = NULL;
		this->Capacity = 0;
		this->IsInitialized = true;
		this->IsAllocated = false;
	}

	VectorClass(int nCapacity, T* pMem) {
		this->Items = NULL;
		this->Capacity = nCapacity;
		this->IsInitialized = true;
		this->IsAllocated = false;

		if(nCapacity != 0) {
			if(pMem) {
				this->Items = pMem;
			} else {
				this->Items = new T[nCapacity];
//				GAME_ALLOC_ARR(T, nCapacity, this->Items);
				this->IsAllocated = true;
			}
		}
	}

	inline void Load(IStream *pStm, bool bSwizzle);

	void Save(IStream *pStm) {
		int ii = this->Capacity;
		pStm->Write(&ii, 4u, 0);
		for ( ii = 0; ii < Capacity; ++ii ) {
			pStm->Write(&(this->Items[ii]), 4, 0);
		}
	}

	void Purge() {
		this->Items = NULL;
		this->IsAllocated = false;
		this->Capacity = 0;
	}

	T* Items;
	int Capacity;
	bool IsInitialized;
	bool IsAllocated;
};

//========================================================================
//=== DynamicVectorClass =================================================
//========================================================================

template <typename T> class DynamicVectorClass : public VectorClass<T>
{
public:
	virtual ~DynamicVectorClass() {
		this->Clear();
	}

	inline void Load(IStream *pStm, bool bSwizzle);

	inline bool ValidIndex(signed int idx) const {
		return idx > -1 && idx < this->Count;
	}

	void Save(IStream *pStm) const {
		int ii = this->Count;
		pStm->Write(&ii, 4u, 0);
		for ( ii = 0; ii < this->Count; ++ii ) {
			pStm->Write(&(this->Items[ii]), 4, 0);
		}
	}

	T* start() const {
		if(!this->IsInitialized) {
			return NULL;
		}
		return &this->Items[0];
	}

	T* end() const {
		if(!this->IsInitialized) {
			return NULL;
		}
		return &this->Items[this->Count];
	}

	virtual bool SetCapacity(int nNewCapacity, T* pMem) {
		bool bRet = VectorClass<T>::SetCapacity(nNewCapacity, pMem);

		if(this->Capacity < this->Count) {
			this->Count = this->Capacity;
		}

		return bRet;
	}

	virtual void Clear() {
		this->Count = 0;
		VectorClass<T>::Clear();
	}

	void Purge() {
		this->Count = 0;
		VectorClass<T>::Purge();
	}

	// aaaaaurgh , this takes T* , not plain T... what a silly mistake
	virtual int FindItemIndex(T *tItem) const {
		if(!this->IsInitialized) {
			return -1;
		}

		for(int i = 0; i < Count; i++) {
			if(this->Items[i] == *tItem) {
				return i;
			}
		}

		return -1;
	}

	DynamicVectorClass<T>() : VectorClass<T>() {
		this->Count = 0;
		this->CapacityIncrement = 10;
/*
	lolhax
		if(VT<T>::Set()) {
			*(DWORD *)this = VT<T>::Get();
		}
*/
	}

	DynamicVectorClass<T>(int nCapacity, T* pMem) : VectorClass<T>(nCapacity, pMem) {
		this->Count = 0;
		this->CapacityIncrement = 10;
	}

public:
	bool AddItem(T tItem) {
		if(this->Count >= this->Capacity) {
			if(this->IsAllocated || this->Capacity == 0) {
				if(this->CapacityIncrement > 0) {
					if(!this->SetCapacity(this->Capacity + this->CapacityIncrement, NULL)) {
						return false;
					}
				} else {
					return false;
				}
			} else {
				return false;
			}
		}

		this->Items[Count++] = tItem;
		return true;
	}

	bool RemoveItem(int nIndex) {
		if(nIndex >= 0 && nIndex < this->Count) {
			--this->Count;
			if(nIndex < this->Count) {
				for(int i = nIndex; i < this->Count; i++) {
					this->Items[i] = this->Items[i+1];
				}
			}
			return true;
		}
		return false;
	}

	int Count;
	int CapacityIncrement;
};

//========================================================================
//=== TypeList ===========================================================
//========================================================================

template <typename T> class TypeList : public DynamicVectorClass<T>
{
public:
	virtual ~TypeList() {
		this->Clear();
	}

	TypeList<T>() : DynamicVectorClass<T>() {

	}

	TypeList<T>(int nCapacity, T* pMem) : DynamicVectorClass<T>(nCapacity, pMem) {

	}

	DWORD unknown_18;
};

//========================================================================
//=== CounterClass =======================================================
//========================================================================

class CounterClass : public VectorClass<int>
{
public:
	virtual ~CounterClass() {
		if(this->Items && this->IsAllocated) {
			delete [] this->Items;
//			GAME_DEALLOC_ARR(this->Items);
			this->Items = NULL;
		}

		this->IsAllocated = false;
		this->Capacity = 0;
		this->Count = 0;
	}

	virtual void Clear() {
		for(int i = 0; i < this->Capacity; ++i){
			this->Items[i] = 0;
		}

		this->Count = 0;
	}

	int GetItemCount(int nIndex) const
		{ JMP_THIS(0x49FAE0); }

	CounterClass() : VectorClass<int>()
		{ this->Count = 0; }

	int Increment(int nIndex)
		{ JMP_THIS(0x49FA00); }

	int Decrement(int nIndex)
		{ JMP_THIS(0x49FA70); }

	int Count;	//not sure what this is, but it's different from DVC's count
};

#include <SwizzleManagerClass.h>

template<typename T>
void VectorClass<T>::Load(IStream *pStm, bool bSwizzle = 1) {
	int ii = 0;
	this->Purge();
	pStm->Read(&ii, 4u, 0);
	this->SetCapacity(ii, NULL);
	for ( ii = 0; ii < this->Capacity; ++ii ) {
		pStm->Read(&(this->Items[ii]), 4, 0);
	}
	if(bSwizzle) {
		for ( ii = 0; ii < this->Capacity; ++ii ) {
			SWIZZLE(this->Items[ii]);
		}
	}
}

#include <SwizzleManagerClass.h>
template<typename T>
void DynamicVectorClass<T>::Load(IStream *pStm, bool bSwizzle) {
	int ii = 0;
	this->Purge();
	pStm->Read(&ii, 4u, 0);
	this->SetCapacity(ii, NULL);
	for ( int jj = 0; jj < ii; ++jj ) {
		pStm->Read(&(this->Items[jj]), 4, 0);
	}
	this->Count = ii;
	if(bSwizzle) {
		for ( ii = 0; ii < this->Count; ++ii ) {
			SWIZZLE(this->Items[ii]);
		}
	}
}

#endif
