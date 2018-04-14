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
#include "resource.h"
#include "3dsmaxport.h"


IMPLEMENT_APP_NO_MAIN(MyGuiApp)


bool MyGuiApp::OnInit()
{

	wxInitAllImageHandlers();
	wxWindow* wind = new wxWindow();
	wind->SetHWND((WXHWND)MatStore::GetInstance().ip->GetMAXHWnd());
	wind->AdoptAttributesFromHWND();
	wxGetApp().SetTopWindow(wind);

	frame = new MyFrame(wind, wxID_ANY, wxEmptyString);
	//SetTopWindow(frame);
	return true;
}

//
//int MyGuiApp::OnExit()
//{
//	return 0;
//}


MatStore MatStore::matstoreInst;

static MatStoreClassDesc matStoreDesc;
ClassDesc2* GetMatStoreDesc() {
	return &matStoreDesc;
}


static MatStoreAction MatStoreActions(
	MAXSTORE_ACT_INTERFACE, _T("MatStore"), IDS_CATEGORY, &matStoreDesc, FP_ACTIONS, kActionMainUIContext,
	MatStoreAction::pm_show, _T("show"), IDS_CLASS_NAME, 0,
	p_end,
	p_end);


MatStore::MatStore()
{

}

MatStore::~MatStore()
{

}

void MatStore::DeleteThis()
{
	wxEntryCleanup();
}

// Activate and Stay Resident
DWORD MatStore::Start()
{
	ip = Max();
	return GUPRESULT_KEEP;
}

void MatStore::Stop()
{
	#pragma message(TODO("Do plugin un-initialization here"))
}

DWORD_PTR MatStore::Control( DWORD parameter)
{
	if (parameter == 1)
		SetVisible(TRUE);
	else if (parameter == 0)
		SetVisible(FALSE);
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

void MatStore::SetVisible(BOOL show)
{
	if(show && !wxGetApp().isOpen)
	{
		wxTheApp->CallOnInit();
		wxGetApp().ShowDialog();
	}
	else if (show && wxGetApp().isOpen)
	{
		wxGetApp().CloseDialog();
	}
	else if (!show && wxGetApp().isOpen)
	{
		wxGetApp().CloseDialog();
	}
}