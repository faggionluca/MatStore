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
// DESCRIPTION: MATStore Plugin allow the user to keep a copy of the previus 
//				nodes materials for future restores
// AUTHOR: Luca Faggion (DarkImage)
//***************************************************************************/

#include "MatStore.h"
#include "resource.h"
#include "3dsmaxport.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

IMPLEMENT_APP_NO_MAIN(GuiApp)


bool GuiApp::OnInit()
{

	wxInitAllImageHandlers();

	wxWindow* wind = new wxWindow();
	wind->SetHWND((WXHWND)MatStore::GetInstance().ip->GetMAXHWnd());
	wind->AdoptAttributesFromHWND();
	wxTopLevelWindows.Append(wind);
	Warndlg = new WarnDlg(wind, wxID_ANY, "Warning Dialog");

	return true;
}

MatStore MatStore::matstoreInst;

static MatStoreClassDesc matStoreDesc;
ClassDesc2* GetMatStoreDesc() {
	return &matStoreDesc;
}


static MatStoreAction MatStoreActions(
	MAXSTORE_ACT_INTERFACE, _T("MatStore"), IDS_CATEGORY, &matStoreDesc, 
	FP_ACTIONS, kActionMainUIContext,
		MatStoreAction::pm_show, _T("show"), IDS_CLASS_NAME, 0, f_icon, _T("MatStoreIcon"),1, p_end,
	p_end);

MatStore::MatStore()
{
	ext = FilterList();
	ext.Append(_M("MAT LAYOUT(*.xml)"));
	ext.Append(_M("*.xml"));
}

MatStore::~MatStore(){}

void MatStore::DeleteThis(){}

// Activate and Stay Resident
DWORD MatStore::Start()
{
	ip = Max();
	wxTheApp->CallOnInit();
	return GUPRESULT_KEEP;
}

void MatStore::Stop()
{
	wxEntryCleanup();
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

const wchar_t * MatStore::toWideString(std::string msg)
{
	wstring* widestr = new wstring(msg.begin(), msg.end());
	return widestr->c_str();
}

void MatStore::StoreMat()
{
	int res;
	{
		if (material_lib.materials.size() != 0)
			res = wxGetApp().ShowWarnDialog();
		else
			res = wxID_YES;
	}

	if (res != wxID_NO && res != wxID_CANCEL)
	{
		material_lib.materials.clear();
		int skip = 0;
		string skipped;
		for (int i = 0; i < ip->GetSelNodeCount(); i++)
		{
			INode* node = ip->GetSelNode(i);
			Mtl* mtl = node->GetMtl();
			if (mtl) {
				material_lib.materials.push_back(MAT(wchar_tosting(node->GetName()), wchar_tosting(mtl->GetName())));
			}
			else skip++;
		}
		if (skip > 0) skipped = "Skipped " + to_string(skip) + " Objects";
		else skipped = "";
		string msg = "Stored " + to_string(material_lib.materials.size()) + " objects materials " + skipped;
		ip->PushPrompt(toWideString(msg));
	}
	else
		ip->DisplayTempPrompt(_M("Keeping current mat layout"), 2000);
}

void MatStore::ReStoreMat()
{
	int i = 0;
	int skip = 0;
	int objs = 0;
	string skipped;
	for each (MAT var in material_lib.materials)
	{
		INode* cnode = ip->GetINodeByName(toWideString(var.first));
		ULONG hd = cnode->GetHandle();
		if (ip->GetINodeByHandle(hd)) {
			cnode->SetMtl(getSceneMat(var.second));
			objs++;
		}
		else skip++;
		i++;
	}
	if (skip > 0) skipped = "Skipped " + to_string(skip) + " Objects";
	else skipped = "";
	string msg = "Restored " + to_string(objs) + " objects materials " + skipped;
	ip->PushPrompt(toWideString(msg));
}

void MatStore::SaveMat()
{
	WStr dir, name;
	if (((Interface8*)ip)->DoMaxSaveAsDialog(ip->GetMAXHWnd(), _M("Save Mat Layout to File"), name, dir, ext))
	{
		{
			ofstream savefile(name);
			if (savefile.is_open()) {
				cereal::XMLOutputArchive archive(savefile);
				archive(CEREAL_NVP(material_lib));
				ip->PushPrompt(toWideString("Saved " + to_string(material_lib.materials.size()) + " objects materials"));
			}
			else
				MessageBox(ip->GetMAXHWnd(),"Save to file " + name + " failed, Cannot open file!", NULL, MB_OK);
		}
	}
}

void MatStore::LoadMat()
{
	WStr filename, dir;
	if (((Interface8*)ip)->DoMaxOpenDialog(ip->GetMAXHWnd(), _M("Open Mat layout"), filename, dir, ext))
	{
		{
			ifstream openfile(filename);
			if (openfile.is_open())
			{
				cereal::XMLInputArchive archive(openfile);
				archive(CEREAL_NVP(material_lib));
				ip->PushPrompt(toWideString("Loaded " + to_string(material_lib.materials.size()) + " objects materials"));
			}
			else
				MessageBox(ip->GetMAXHWnd(), "Cannot open file " + filename, NULL, MB_OK);
		}
	}
}

std::string MatStore::wchar_tosting(const wchar_t * text)
{
	wstring ws(text);
	string str(ws.begin(), ws.end());
	return str;
}

Mtl * MatStore::getSceneMat(std::string name)
{
	MtlBaseLib* lib = ip->GetSceneMtls();
	Mtl* mtl = (Mtl*)lib->GetReference(lib->FindMtlByName(WStr(toWideString(name))));
	return mtl;
}

void MatStore::SetVisible(BOOL show)
{
	if(show && !wxGetApp().isOpen)
	{
		wxGetApp().InitDialog();
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