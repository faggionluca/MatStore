//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "MatStore.h"

#define MatStore_CLASS_ID	Class_ID(0x949169bd, 0x81e0f0ab)


class MatStore : public GUP
{
public:
	//Constructor/Destructor
	MatStore();
	virtual ~MatStore();

	// GUP Methods
	virtual DWORD     Start();
	virtual void      Stop();
	virtual DWORD_PTR Control(DWORD parameter);
	virtual void      DeleteThis();

	// Loading/Saving
	virtual IOResult Save(ISave* isave);
	virtual IOResult Load(ILoad* iload);
};



class MatStoreClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new MatStore(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GUP_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return MatStore_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("MatStore"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetMatStoreDesc() { 
	static MatStoreClassDesc MatStoreDesc;
	return &MatStoreDesc; 
}




MatStore::MatStore()
{

}

MatStore::~MatStore()
{

}

void MatStore::DeleteThis()
{
	delete this;
}

// Activate and Stay Resident
DWORD MatStore::Start()
{
	#pragma message(TODO("Do plugin initialization here"))
	#pragma message(TODO("Return if you want remain loaded or not"))
	return GUPRESULT_KEEP;
}

void MatStore::Stop()
{
	#pragma message(TODO("Do plugin un-initialization here"))
}

DWORD_PTR MatStore::Control( DWORD /*parameter*/ )
{
	return 0;
}

IOResult MatStore::Save(ISave* /*isave*/)
{
	return IO_OK;
}

IOResult MatStore::Load(ILoad* /*iload*/)
{
	return IO_OK;
}

