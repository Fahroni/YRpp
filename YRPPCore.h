//strcpy is "unsafe"? wtf?
// DC: yeah, no length limit so char foo[3]; strcpy(foo, "roflcakes") works and smashes stack
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef YRPPCore_H
#define YRPPCore_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//Syringe interaction header - also includes <windows.h>
#include <Syringe.h>

//Assembly macros
#include <ASMMacros.h>

#include <Memory.h>

#include <wchar.h>
#include <cstdio>

#define PROPERTY_PTR(type,name)\
	public: \
		type name;\
	public:\
		type get_ ## name() \
			{ return name; }\
		void set_ ## name(type value)\
			{ name = value; } \
		type* lea_ ## name() \
			{ return &name; }

//Not gettable/settable members
#define PROTECTED_PROPERTY(type,name)\
	protected:\
		type name; \
	public:

// following westwood's style
#define VALIDTAG(str) \
	(_strcmpi("<none>", str) && _strcmpi("none", str))

/*
Operation: The Cleansing

These two replace a function's implementation.

R0 is used for functions which return a numeric value or a pointer.
RX is for functions without a return type.
Functions that return struct instances will have to be written manually.

I chose short names to keep things clean.

Example usage:
virtual int foo(int bar) R0;
virtual void alla(double malla) RX;
*/

#define R0 {return 0;}
#define RX {}

#endif
