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
#include <string>
using namespace  std;

IMPLEMENT_APP_NO_MAIN(GuiApp)


bool GuiApp::OnInit()
{

	wxInitAllImageHandlers();
	wxWindow* wind = new wxWindow();
	wind->SetHWND((WXHWND)MatStore::GetInstance().ip->GetMAXHWnd());
	wind->AdoptAttributesFromHWND();
	wxTopLevelWindows.Append(wind);

	frame = new MatStoreDlg(wind, wxID_ANY, wxEmptyString);
	return true;
}

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

void MatStore::StoreMat()
{
	WarnDlg* dlg = new WarnDlg(wxGetApp().getDialog()->GetParent(), wxID_ANY, "Test");
	dlg->ShowModal();
	//mats.clear();
	//nodes.clear();
	//int skip = 0;
	//string skipped;
	//for (int i = 0; i < ip->GetSelNodeCount(); i++)
	//{
	//	INode* node = ip->GetSelNode(i);
	//	Mtl* mtl = node->GetMtl();
	//	if (mtl) {
	//		mats.push_back(mtl);
	//		nodes.push_back(node);
	//	}
	//	else skip++;
	//}
	//if (skip > 0) skipped = "Skipped " + to_string(skip) + " Objects";
	//else skipped = "";
	//string msg = "Stored " + to_string(nodes.size()) + " objects materials " + skipped;
	//std::wstring widestr = std::wstring(msg.begin(), msg.end());
	//ip->PushPrompt(widestr.c_str());
}

void MatStore::ReStoreMat()
{
	int i = 0;
	int skip = 0;
	int objs = 0;
	string skipped;
	for each (INode* var in nodes)
	{
		const wchar_t* t = var->GetName();
		ULONG hd = var->GetHandle();
		if (ip->GetINodeByHandle(hd)) {
			var->SetMtl(mats[i]);
			objs++;
		}
		else skip++;
		i++;
	}
	if (skip > 0) skipped = "Skipped " + to_string(skip) + " Objects";
	else skipped = "";
	string msg = "Restored " + to_string(objs) + " objects materials " + skipped;
	std::wstring widestr = std::wstring(msg.begin(), msg.end());
	ip->PushPrompt(widestr.c_str());
}

void MatStore::SaveMat()
{
	WStr dir, name;
	FilterList ext = FilterList();
	ext.Append(_M("MAT LAYOUT(*.csv)"));
	ext.Append(_M("*.csv"));
	((Interface8*)ip)->DoMaxSaveAsDialog(ip->GetMAXHWnd(), L"Save Mat Layout to File", dir, name, ext);
	#pragma message(TODO("Do SAVE TO FILE HERE"))
}

void MatStore::LoadMat()
{
	WStr name, dir;
	FilterList ext = FilterList();
	ext.Append(_M("MAT LAYOUT(*.csv)"));
	ext.Append(_M("*.csv"));
	((Interface8*)ip)->DoMaxOpenDialog(ip->GetMAXHWnd(), L"Open Mat layout", name, dir, ext);
	#pragma message(TODO("Do OPEN FILE HERE"))
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
		wxGetApp().isOpen = false;
	}
}