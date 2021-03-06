#ifndef MEMORY_H
#define MEMORY_H

#include <ASMMacros.h>
//include <Unsorted.h>

/*
 * The memory (de)allocators have to match!
 * Do not allocate memory in the DLL and hand it to the game to deallocate, or vice versa.
 * Kapiche?

 * A simple |auto foo = new IngameClass();| allocates memory from the DLL's pool.
 * But |delete foo;| deallocates memory from the game's own pool. (assuming the class you're freeing has a virtual SDDTOR)

 * So use the macros to make sure game classes go to the game's pool.
 * The custom classes like ExtMap do not need this treatment so you can use the plain old new/delete on them.

 * For the ObjectClass derivates, if you use the game's built-in allocators like | Type->CreateObject() | ,
 * you can use plain | delete |;

 */

/*
 * OK, new plan - the game's operator new/delete has been hooked to redirect to the DLL's
 * so GAME_(DE)ALLOC is now just a wrapper. Don't remove it though, just in case this fails
 * and I need to run those allocations differently.
 */

/*
 * Newer plan - previous hook screwed performance, so going back
 */

// allocate scalars
template<typename T>
static void * __cdecl Allocate(bool inDLL) {
	size_t sz = sizeof(T);

	if(inDLL) {
		return operator new(sz);
	}

	PUSH_VAR32(sz);
	CALL(0x7C8E17);
	ADD_ESP(4);
};

#define DO_ALLOC(inDLL, TT, var, ...) \
{ \
	var = nullptr; \
	if(void *p = Allocate<TT>(inDLL)) { \
		var = new (p) TT(__VA_ARGS__); \
	} \
	if(!var) { \
		ExitProcess(1); \
	} \
} \

// allocate in the game's pool
#define GAME_ALLOC(TT, var, ...) \
{ \
	DO_ALLOC(0, TT, var, __VA_ARGS__); \
}

//	var = new TT(__VA_ARGS__);

// allocate in the DLL's pool
// not sure if this is ever going to be needed
#define DLL_ALLOC(TT, var, ...) \
{ \
	DO_ALLOC(1, TT, var, __VA_ARGS__);\
} \

// allocate vectors
template<typename T>
static void * __cdecl Allocate_Array(bool inDLL, size_t Capacity) {
	size_t sz = sizeof(T) * Capacity;

	if(inDLL) {
		return operator new(sz);
	}

	PUSH_VAR32(sz);
	CALL(0x7C8E17);
	ADD_ESP(4);
};

// allocate arrays
#define DO_ALLOC_ARR(inDLL, TT, Capacity, var) \
{ \
	var = nullptr; \
	if(void *p = Allocate_Array<TT>(inDLL, Capacity)) { \
		var = new (p) TT[Capacity]; \
	} \
	if(!var) { \
		ExitProcess(1); \
	} \
} \

// allocate array in the game's pool
#define GAME_ALLOC_ARR(TT, Capacity, var) \
{ \
	DO_ALLOC_ARR(0, TT, Capacity, var); \
}

// deallocate scalars
template<typename T>
static void __cdecl Deallocate(T* Tptr, bool inDLL) {
	if(Tptr) {
		Tptr->~T();
	}
	if(inDLL) {
		operator delete(Tptr);
		return;
	}
	PUSH_VAR32(Tptr);
	CALL(0x7C8B3D);
	ADD_ESP(4);
};

// deallocate from the game's pool
#define GAME_DEALLOC(var) \
{ \
	Deallocate(var, 0); \
} \

//	delete var;

// deallocate from the DLL's pool
#define DLL_DEALLOC(var) \
{ \
	Deallocate(var, 1); \
} \

// deallocate vectors
template<typename T>
static void __cdecl Deallocate_Array(T* Tptr, bool inDLL) {
	if(Tptr) {
		T *iter = Tptr;
		// ye olde black magick
		size_t *p = reinterpret_cast<size_t *>(iter) - 1;
		size_t amount = *p;
		while(amount > 0 && iter) {
			iter->~T();
			++iter;
			--amount;
		}
	}
	if(inDLL) {
		operator delete[](Tptr);
		return;
	}
	PUSH_VAR32(Tptr);
	CALL(0x7C8B3D);
	ADD_ESP(4);
};

// deallocate from the game's pool
#define GAME_DEALLOC_ARR(var) \
{ \
	Deallocate_Array(var, 0); \
} \

#endif
