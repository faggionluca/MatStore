#pragma once

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
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <vector>
#include "dialog.h"
#include "warn_dlg.h"
//SIMPLE TYPE


#include <guplib.h>


extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;


#define MatStore_CLASS_ID	Class_ID(0x446205cf, 0x3d8707f)


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

	Interface* ip;
	MatStoreDlg* dlg;

	std::vector<Mtl*> mats;
	std::vector<INode*> nodes;
	void StoreMat();
	void ReStoreMat();
	void SaveMat();
	void LoadMat();

	//SINGLETON ACCESS
	static MatStore matstoreInst;
	static MatStore& GetInstance() { return matstoreInst; }

	void SetVisible(BOOL show = TRUE);

};


class MatStoreClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return &(MatStore::GetInstance()); }
	virtual const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() { return GUP_CLASS_ID; }
	virtual Class_ID ClassID() { return MatStore_CLASS_ID; }
	virtual const TCHAR* Category() { return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() { return _T("MatStore"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle


};


#define MAXSTORE_ACT_INTERFACE Interface_ID(0x446205cf, 0x3d8707f)
class MatStoreAction : public FPStaticInterface {
public:
	FPStatus ShowmaxTool()
	{
		MatStore::GetInstance().SetVisible();
		return FPS_OK;
	}

	// action dispatch
	DECLARE_DESCRIPTOR(MatStoreAction)
	enum ActionID { pm_show };
	BEGIN_FUNCTION_MAP
		FN_ACTION(pm_show, ShowmaxTool);
	END_FUNCTION_MAP
};


class GuiApp : public wxApp {
public:
	bool OnInit();
	//int OnExit();

	wxFrame* getDialog() { return frame; }
	void ShowDialog() { 
		isOpen = true;
		MatStore::GetInstance().ip->RegisterDlgWnd(frame->GetHWND());
		frame->Show();}
	void CloseDialog() {
		isOpen = false;
		frame->GetParent()->DestroyChildren();
		MatStore::GetInstance().ip->UnRegisterDlgWnd(frame->GetHWND());
	}
	bool isOpen = false;
private:
	MatStoreDlg* frame;
};

DECLARE_APP(GuiApp)