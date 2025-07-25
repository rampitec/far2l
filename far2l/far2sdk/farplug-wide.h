#pragma once
#ifndef __FAR2SDK_FARPLUG_WIDE_H__
#define __FAR2SDK_FARPLUG_WIDE_H__

#if !defined(FAR_USE_INTERNALS) && !defined(FAR_DONT_USE_INTERNALS)
#define FAR_USE_INTERNALS
#endif // END FAR_USE_INTERNALS
/*
  plugin.hpp

  Plugin API for FAR Manager <%VERSION%>
*/

/*
Copyright (c) 1996 Eugene Roshal
Copyright (c) 2000 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

EXCEPTION:
Far Manager plugins that use this header file can be distributed under any
other possible license with no implications from the above license on them.
*/

#define FARMANAGERVERSION_MAJOR 2
#define FARMANAGERVERSION_MINOR 6

#ifndef RC_INVOKED

#define MAKEFARVERSION(major,minor) ( ((major)<<16) | (minor))

#define FARMANAGERVERSION MAKEFARVERSION(FARMANAGERVERSION_MAJOR,FARMANAGERVERSION_MINOR)

#include "../../WinPort/windows.h"

#ifdef FAR_USE_INTERNALS
#else // ELSE FAR_USE_INTERNALS

#if 1
#else
#if !defined(_INC_WINDOWS) && !defined(_WINDOWS_)
#if (defined(__GNUC__) || defined(_MSC_VER)) && !defined(_WIN64)
#if !defined(_WINCON_H) && !defined(_WINCON_)
#define _WINCON_H
#define _WINCON_ // to prevent including wincon.h
#if defined(_MSC_VER)
#pragma pack(push,2)
#else
#pragma pack(2)
#endif
#include<windows.h>
#if defined(_MSC_VER)
#pragma pack(pop)
#else
#pragma pack()
#endif
#undef _WINCON_
#undef  _WINCON_H

#if defined(_MSC_VER)
#pragma pack(push,8)
#else
#pragma pack(8)
#endif
#include<wincon.h>
#if defined(_MSC_VER)
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
#define _WINCON_
#else
#include<windows.h>
#endif
#endif
#endif // END FAR_USE_INTERNALS
#endif

#if defined(__BORLANDC__)
#ifndef _WIN64
#pragma option -a2
#endif
#elif defined(__GNUC__) || (defined(__WATCOMC__) && (__WATCOMC__ < 1100)) || defined(__LCC__)
#ifndef _WIN64
#pragma pack(2)
#endif
#else
#ifndef _WIN64
#pragma pack(push,2)
#endif
#if _MSC_VER
#ifdef _export
#undef _export
#endif
#define _export
#endif
#endif

#undef DefDlgProc

#define FARMACRO_KEY_EVENT  (KEY_EVENT|0x8000)

#ifdef FAR_USE_INTERNALS
#ifndef _FAR_HAS_NAMELESS_UNIONS
#define _FAR_NO_NAMELESS_UNIONS
#endif
#else // ELSE FAR_USE_INTERNALS
// To ensure compatibility of plugin.hpp with compilers not supporting C++,
// you can #define _FAR_NO_NAMELESS_UNIONS. In this case, to access,
// for example, the Data field of the FarDialogItem structure
// you will need to use Data.Data, and the Selected field - Param.Selected
//#define _FAR_NO_NAMELESS_UNIONS
#endif // END FAR_USE_INTERNALS

#ifndef _WINCON_
typedef struct _INPUT_RECORD INPUT_RECORD;
typedef struct _CHAR_INFO    CHAR_INFO;
#endif

#include "farcommon.h"


#ifdef __cpp_inline_variables
#define FAR_INLINE_CONSTANT inline constexpr
#else
#define FAR_INLINE_CONSTANT static const
#endif

typedef uint32_t FARMESSAGEFLAGS;
typedef GUID UUID;

FAR_INLINE_CONSTANT FARMESSAGEFLAGS
	FMSG_WARNING             = 0x00000001,
	FMSG_ERRORTYPE           = 0x00000002,
	FMSG_KEEPBACKGROUND      = 0x00000004,
	FMSG_LEFTALIGN           = 0x00000010,

	FMSG_ALLINONE            = 0x00000020,
#ifdef FAR_USE_INTERNALS
	FMSG_COLOURS             = 0x00000040,
#endif // END FAR_USE_INTERNALS
	FMSG_DISPLAYNOTIFY       = 0x00000080,

	FMSG_MB_OK               = 0x00010000,
	FMSG_MB_OKCANCEL         = 0x00020000,
	FMSG_MB_ABORTRETRYIGNORE = 0x00030000,
	FMSG_MB_YESNO            = 0x00040000,
	FMSG_MB_YESNOCANCEL      = 0x00050000,
	FMSG_MB_RETRYCANCEL      = 0x00060000,
	FMSG_NONE                = 0;

typedef intptr_t ( *FARAPIMESSAGE)(
	INT_PTR PluginNumber,
	DWORD Flags,
	const wchar_t *HelpTopic,
	const wchar_t * const *Items,
	int ItemsNumber,
	int ButtonsNumber
);

enum DialogItemTypes
{
	DI_TEXT,
	DI_VTEXT,
	DI_SINGLEBOX,
	DI_DOUBLEBOX,
	DI_EDIT,
	DI_PSWEDIT,
	DI_FIXEDIT,
	DI_BUTTON,
	DI_CHECKBOX,
	DI_RADIOBUTTON,
	DI_COMBOBOX,
	DI_LISTBOX,
#ifdef FAR_USE_INTERNALS
	DI_MEMOEDIT,
#endif // END FAR_USE_INTERNALS

	DI_USERCONTROL=255,
};

/*
   Check diagol element type has inputstring?
   (DI_EDIT, DI_FIXEDIT, DI_PSWEDIT, etc)
*/
#ifdef FAR_USE_INTERNALS
# define FarIsEdit(Type)  ((Type) == DI_EDIT || (Type) == DI_FIXEDIT || (Type) == DI_PSWEDIT || (Type) == DI_COMBOBOX || (Type) == DI_MEMOEDIT)
#else
# define FarIsEdit(Type)  ((Type) == DI_EDIT || (Type) == DI_FIXEDIT || (Type) == DI_PSWEDIT || (Type) == DI_COMBOBOX)
#endif

enum FarDialogItemFlags
{
	DIF_NONE                  = 0,
	DIF_COLORMASK             = 0x000000ffUL,
	DIF_SETCOLOR              = 0x00000100UL,
	DIF_BOXCOLOR              = 0x00000200UL,
#ifdef FAR_USE_INTERNALS
	DIF_DEFAULT               = 0x00000200UL,
#endif // END FAR_USE_INTERNALS
	DIF_GROUP                 = 0x00000400UL,
	DIF_LEFTTEXT              = 0x00000800UL,
#ifdef FAR_USE_INTERNALS
	DIF_FOCUS                 = 0x00000800UL,
#endif // END FAR_USE_INTERNALS
	DIF_MOVESELECT            = 0x00001000UL,
	DIF_SHOWAMPERSAND         = 0x00002000UL,
	DIF_CENTERGROUP           = 0x00004000UL,
	DIF_NOBRACKETS            = 0x00008000UL,
	DIF_MANUALADDHISTORY      = 0x00008000UL,
	DIF_SEPARATOR             = 0x00010000UL,
	DIF_SEPARATOR2            = 0x00020000UL,
	DIF_EDITOR                = 0x00020000UL,
	DIF_LISTNOAMPERSAND       = 0x00020000UL,
	DIF_LISTNOBOX             = 0x00040000UL,
	DIF_HISTORY               = 0x00040000UL,
	DIF_BTNNOCLOSE            = 0x00040000UL,
	DIF_CENTERTEXT            = 0x00040000UL,
#ifdef FAR_USE_INTERNALS
	DIF_SEPARATORUSER         = 0x00080000UL,
#endif // END FAR_USE_INTERNALS
	DIF_SETSHIELD             = 0x00080000UL,
	DIF_EDITEXPAND            = 0x00080000UL,
	DIF_DROPDOWNLIST          = 0x00100000UL,
	DIF_USELASTHISTORY        = 0x00200000UL,
	DIF_MASKEDIT              = 0x00400000UL,
	DIF_SELECTONENTRY         = 0x00800000UL,
	DIF_3STATE                = 0x00800000UL,
	DIF_EDITPATH              = 0x01000000UL,
	DIF_LISTWRAPMODE          = 0x01000000UL,
	DIF_NOAUTOCOMPLETE        = 0x02000000UL,
	DIF_LISTAUTOHIGHLIGHT     = 0x02000000UL,
	DIF_LISTNOCLOSE           = 0x04000000UL,
#ifdef FAR_USE_INTERNALS
	DIF_AUTOMATION            = 0x08000000UL,
#endif // END FAR_USE_INTERNALS
	DIF_HIDDEN                = 0x10000000UL,
	DIF_READONLY              = 0x20000000UL,
	DIF_NOFOCUS               = 0x40000000UL,
	DIF_DISABLE               = 0x80000000UL,
};

enum FarMessagesProc
{
	DM_FIRST=0,
	DM_CLOSE,
	DM_ENABLE,
	DM_ENABLEREDRAW,
	DM_GETDLGDATA,
	DM_GETDLGITEM,
	DM_GETDLGRECT,
	DM_GETTEXT,
	DM_GETTEXTLENGTH,
	DM_KEY,
	DM_MOVEDIALOG,
	DM_SETDLGDATA,
	DM_SETDLGITEM,
	DM_SETFOCUS,
	DM_REDRAW,
	DM_SETREDRAW=DM_REDRAW,
	DM_SETTEXT,
	DM_SETMAXTEXTLENGTH,
	DM_SETTEXTLENGTH=DM_SETMAXTEXTLENGTH,
	DM_SHOWDIALOG,
	DM_GETFOCUS,
	DM_GETCURSORPOS,
	DM_SETCURSORPOS,
	DM_GETTEXTPTR,
	DM_SETTEXTPTR,
	DM_SHOWITEM,
	DM_ADDHISTORY,

	DM_GETCHECK,
	DM_SETCHECK,
	DM_SET3STATE,

	DM_LISTSORT,
	DM_LISTGETITEM,
	DM_LISTGETCURPOS,
	DM_LISTSETCURPOS,
	DM_LISTDELETE,
	DM_LISTADD,
	DM_LISTADDSTR,
	DM_LISTUPDATE,
	DM_LISTINSERT,
	DM_LISTFINDSTRING,
	DM_LISTINFO,
	DM_LISTGETDATA,
	DM_LISTSETDATA,
	DM_LISTSETTITLES,
	DM_LISTGETTITLES,

	DM_RESIZEDIALOG,
	DM_SETITEMPOSITION,

	DM_GETDROPDOWNOPENED,
	DM_SETDROPDOWNOPENED,

	DM_SETHISTORY,

	DM_GETITEMPOSITION,
	DM_SETMOUSEEVENTNOTIFY,

	DM_EDITUNCHANGEDFLAG,

	DM_GETITEMDATA,
	DM_SETITEMDATA,

	DM_LISTSET,
	DM_LISTSETMOUSEREACTION,

	DM_GETCURSORSIZE,
	DM_SETCURSORSIZE,

	DM_LISTGETDATASIZE,

	DM_GETSELECTION,
	DM_SETSELECTION,

	DM_GETEDITPOSITION,
	DM_SETEDITPOSITION,

	DM_SETCOMBOBOXEVENT,
	DM_GETCOMBOBOXEVENT,

	DM_GETCONSTTEXTPTR,
	DM_GETDLGITEMSHORT,
	DM_SETDLGITEMSHORT,

	DM_GETDIALOGINFO,

	DM_SETREADONLY,

//	DM_GETCOLOR,
//	DM_SETCOLOR,
	DM_GETDEFAULTCOLOR, // Param1 - Item ID, Param2 - uint64_t * -> uint64_t ItemColors[4]

	DM_GETTRUECOLOR,	// Param1 - Item ID, Param2 - uint64_t * -> uint64_t ItemColors[4]
	DM_GETCOLOR = DM_GETTRUECOLOR,
	DM_SETTRUECOLOR,	// Param1 - Item ID, Param2 - uint64_t * -> uint64_t ItemColors[4]
	DM_SETCOLOR = DM_SETTRUECOLOR,

	DM_SETTEXTPTRSILENT,

	DN_FIRST=0x1000,
	DN_BTNCLICK,
	DN_CTLCOLORDIALOG,
	DN_CTLCOLORDLGITEM,
	DN_CTLCOLORDLGLIST,
	DN_DRAWDIALOG,
	DN_DRAWDLGITEM,
	DN_EDITCHANGE,
	DN_ENTERIDLE,
	DN_GOTFOCUS,
	DN_HELP,
	DN_HOTKEY,
	DN_INITDIALOG,
	DN_KILLFOCUS,
	DN_LISTCHANGE,
	DN_MOUSECLICK,
	DN_DRAGGED,
	DN_RESIZECONSOLE,
	DN_MOUSEEVENT,
	DN_DRAWDIALOGDONE,
	DN_LISTHOTKEY,
	DN_DROPDOWNOPENED,

	DN_GETDIALOGINFO=DM_GETDIALOGINFO,

	DN_CLOSE=DM_CLOSE,
	DN_KEY=DM_KEY,


	DM_USER=0x4000,

#ifdef FAR_USE_INTERNALS
	DM_KILLSAVESCREEN=DN_FIRST-1,
	DM_ALLKEYMODE=DN_FIRST-2,
	DN_ACTIVATEAPP=DM_USER-1,
#endif // END FAR_USE_INTERNALS
};

enum FARCHECKEDSTATE
{
	BSTATE_UNCHECKED = 0,
	BSTATE_CHECKED   = 1,
	BSTATE_3STATE    = 2,
	BSTATE_TOGGLE    = 3,
};

enum FARLISTMOUSEREACTIONTYPE
{
	LMRT_ONLYFOCUS   = 0,
	LMRT_ALWAYS      = 1,
	LMRT_NEVER       = 2,
};

enum FARCOMBOBOXEVENTTYPE
{
	CBET_KEY         = 0x00000001,
	CBET_MOUSE       = 0x00000002,
};

enum LISTITEMFLAGS
{
	LIF_SELECTED           = 0x00010000UL,
	LIF_CHECKED            = 0x00020000UL,
	LIF_SEPARATOR          = 0x00040000UL,
	LIF_DISABLE            = 0x00080000UL,
	LIF_GRAYED             = 0x00100000UL,
	LIF_HIDDEN             = 0x00200000UL,
	LIF_DELETEUSERDATA     = 0x80000000UL,
};

struct FarListItem
{
	DWORD Flags;
	const wchar_t *Text;
	DWORD Reserved[3];
};

struct FarListUpdate
{
	int Index;
	struct FarListItem Item;
};

struct FarListInsert
{
	int Index;
	struct FarListItem Item;
};

struct FarListGetItem
{
	int ItemIndex;
	struct FarListItem Item;
};

struct FarListPos
{
	int SelectPos;
	int TopPos;
};

enum FARLISTFINDFLAGS
{
	LIFIND_EXACTMATCH = 0x00000001,
	LIFIND_KEEPAMPERSAND = 0x00000002,
};

struct FarListFind
{
	int StartIndex;
	const wchar_t *Pattern;
	DWORD Flags;
	DWORD Reserved;
};

struct FarListDelete
{
	int StartIndex;
	int Count;
};

enum FARLISTINFOFLAGS
{
	LINFO_SHOWNOBOX             = 0x00000400,
	LINFO_AUTOHIGHLIGHT         = 0x00000800,
	LINFO_REVERSEHIGHLIGHT      = 0x00001000,
	LINFO_WRAPMODE              = 0x00008000,
	LINFO_SHOWAMPERSAND         = 0x00010000,
};

struct FarListInfo
{
	DWORD Flags;
	int ItemsNumber;
	int SelectPos;
	int TopPos;
	int MaxHeight;
	int MaxLength;
	DWORD Reserved[6];
};

struct FarListItemData
{
	int   Index;
	int   DataSize;
	void *Data;
	DWORD Reserved;
};

struct FarList
{
	int ItemsNumber;
	struct FarListItem *Items;
};

struct FarListTitles
{
	int   TitleLen;
	const wchar_t *Title;
	int   BottomLen;
	const wchar_t *Bottom;
};

struct FarListColors
{
	DWORD  Flags;
	DWORD  Reserved;
	int    ColorCount;
	uint64_t *Colors;
};

struct FarDialogItem
{
	int Type;
	int X1,Y1,X2,Y2;
	int Focus;
	union
	{
		DWORD_PTR Reserved;
		int Selected;
		const wchar_t *History;
		const wchar_t *Mask;
		struct FarList *ListItems;
		int  ListPos;
		CHAR_INFO *VBuf;
	}
#ifdef _FAR_NO_NAMELESS_UNIONS
	Param
#endif
	;
	DWORD Flags;
	int DefaultButton;

	const wchar_t *PtrData;
	size_t MaxLen; // terminate 0 not included (if == 0 string size is unlimited)
};

struct FarDialogItemData
{
	size_t  PtrLength;
	wchar_t *PtrData;
};

struct FarDialogEvent
{
	HANDLE hDlg;
	int Msg;
	int Param1;
	LONG_PTR Param2;
	LONG_PTR Result;
};

struct OpenDlgPluginData
{
	int ItemNumber;
	HANDLE hDlg;
};

struct DialogInfo
{
	int StructSize;
	GUID Id;
};

#define Dlg_RedrawDialog(Info,hDlg)            Info.SendDlgMessage(hDlg,DM_REDRAW,0,0)

#define Dlg_GetDlgData(Info,hDlg)              Info.SendDlgMessage(hDlg,DM_GETDLGDATA,0,0)
#define Dlg_SetDlgData(Info,hDlg,Data)         Info.SendDlgMessage(hDlg,DM_SETDLGDATA,0,(LONG_PTR)Data)

#define Dlg_GetDlgItemData(Info,hDlg,ID)       Info.SendDlgMessage(hDlg,DM_GETITEMDATA,0,0)
#define Dlg_SetDlgItemData(Info,hDlg,ID,Data)  Info.SendDlgMessage(hDlg,DM_SETITEMDATA,0,(LONG_PTR)Data)

#define DlgItem_GetFocus(Info,hDlg)            Info.SendDlgMessage(hDlg,DM_GETFOCUS,0,0)
#define DlgItem_SetFocus(Info,hDlg,ID)         Info.SendDlgMessage(hDlg,DM_SETFOCUS,ID,0)
#define DlgItem_Enable(Info,hDlg,ID)           Info.SendDlgMessage(hDlg,DM_ENABLE,ID,TRUE)
#define DlgItem_Disable(Info,hDlg,ID)          Info.SendDlgMessage(hDlg,DM_ENABLE,ID,FALSE)
#define DlgItem_IsEnable(Info,hDlg,ID)         Info.SendDlgMessage(hDlg,DM_ENABLE,ID,-1)
#define DlgItem_SetText(Info,hDlg,ID,Str)      Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,ID,(LONG_PTR)Str)

#define DlgItem_GetCheck(Info,hDlg,ID)         Info.SendDlgMessage(hDlg,DM_GETCHECK,ID,0)
#define DlgItem_SetCheck(Info,hDlg,ID,State)   Info.SendDlgMessage(hDlg,DM_SETCHECK,ID,State)

#define DlgEdit_AddHistory(Info,hDlg,ID,Str)   Info.SendDlgMessage(hDlg,DM_ADDHISTORY,ID,(LONG_PTR)Str)

#define DlgList_AddString(Info,hDlg,ID,Str)    Info.SendDlgMessage(hDlg,DM_LISTADDSTR,ID,(LONG_PTR)Str)
#define DlgList_GetCurPos(Info,hDlg,ID)        Info.SendDlgMessage(hDlg,DM_LISTGETCURPOS,ID,0)
#define DlgList_SetCurPos(Info,hDlg,ID,NewPos) {struct FarListPos LPos={NewPos,-1};Info.SendDlgMessage(hDlg,DM_LISTSETCURPOS,ID,(LONG_PTR)&LPos);}
#define DlgList_ClearList(Info,hDlg,ID)        Info.SendDlgMessage(hDlg,DM_LISTDELETE,ID,0)
#define DlgList_DeleteItem(Info,hDlg,ID,Index) {struct FarListDelete FLDItem={Index,1}; Info.SendDlgMessage(hDlg,DM_LISTDELETE,ID,(LONG_PTR)&FLDItem);}
#define DlgList_SortUp(Info,hDlg,ID)           Info.SendDlgMessage(hDlg,DM_LISTSORT,ID,0)
#define DlgList_SortDown(Info,hDlg,ID)         Info.SendDlgMessage(hDlg,DM_LISTSORT,ID,1)
#define DlgList_GetItemData(Info,hDlg,ID,Index)          Info.SendDlgMessage(hDlg,DM_LISTGETDATA,ID,Index)
#define DlgList_SetItemStrAsData(Info,hDlg,ID,Index,Str) {struct FarListItemData FLID{Index,0,Str,0}; Info.SendDlgMessage(hDlg,DM_LISTSETDATA,ID,(LONG_PTR)&FLID);}

enum FARDIALOGFLAGS
{
	FDLG_WARNING             = 0x00000001,
	FDLG_SMALLDIALOG         = 0x00000002,
	FDLG_NODRAWSHADOW        = 0x00000004,
	FDLG_NODRAWPANEL         = 0x00000008,
#ifdef FAR_USE_INTERNALS
	FDLG_NONMODAL            = 0x00000010,
#endif // END FAR_USE_INTERNALS
	FDLG_KEEPCONSOLETITLE    = 0x00000020,
	FDLG_REGULARIDLE         = 0x00000040 // causes dialog to receive DN_ENTERIDLE at least once per second
};

typedef LONG_PTR(WINAPI *FARWINDOWPROC)(
	HANDLE   hDlg,
	int      Msg,
	int      Param1,
	LONG_PTR Param2
);

typedef LONG_PTR(WINAPI *FARAPISENDDLGMESSAGE)(
	HANDLE   hDlg,
	int      Msg,
	int      Param1,
	LONG_PTR Param2
);

typedef LONG_PTR(WINAPI *FARAPIDEFDLGPROC)(
	HANDLE   hDlg,
	int      Msg,
	int      Param1,
	LONG_PTR Param2
);

typedef HANDLE(WINAPI *FARAPIDIALOGINIT)(
	INT_PTR               PluginNumber,
	int                   X1,
	int                   Y1,
	int                   X2,
	int                   Y2,
	const wchar_t        *HelpTopic,
	struct FarDialogItem *Item,
	unsigned int          ItemsNumber,
	DWORD                 Reserved,
	DWORD                 Flags,
	FARWINDOWPROC         DlgProc,
	LONG_PTR              Param
);

typedef int (WINAPI *FARAPIDIALOGRUN)(
	HANDLE hDlg
);

typedef void (WINAPI *FARAPIDIALOGFREE)(
	HANDLE hDlg
);

struct FarMenuItem
{
	const wchar_t *Text;
	int  Selected;
	int  Checked;
	int  Separator;
};

enum MENUITEMFLAGS
{
	MIF_NONE   = 0,
	MIF_SELECTED   = 0x00010000UL,
	MIF_CHECKED    = 0x00020000UL,
	MIF_SEPARATOR  = 0x00040000UL,
	MIF_DISABLE    = 0x00080000UL,
	MIF_GRAYED     = 0x00100000UL,
	MIF_HIDDEN     = 0x00200000UL,
#ifdef FAR_USE_INTERNALS
	MIF_SUBMENU    = 0x00400000UL,
#endif // END FAR_USE_INTERNALS
};

struct FarMenuItemEx
{
	DWORD Flags;
	const wchar_t *Text;
	DWORD AccelKey;
	DWORD Reserved;
	DWORD_PTR UserData;
};

enum FARMENUFLAGS
{
	FMENU_SHOWAMPERSAND        = 0x00000001,
	FMENU_WRAPMODE             = 0x00000002,
	FMENU_AUTOHIGHLIGHT        = 0x00000004,
	FMENU_REVERSEAUTOHIGHLIGHT = 0x00000008,
#ifdef FAR_USE_INTERNALS
	FMENU_SHOWNOBOX            = 0x00000010,
#endif // END FAR_USE_INTERNALS
	FMENU_USEEXT               = 0x00000020,
	FMENU_CHANGECONSOLETITLE   = 0x00000040,
};

typedef int (WINAPI *FARAPIMENU)(
	INT_PTR             PluginNumber,
	int                 X,
	int                 Y,
	int                 MaxHeight,
	DWORD               Flags,
	const wchar_t      *Title,
	const wchar_t      *Bottom,
	const wchar_t      *HelpTopic,
	const int          *BreakKeys,
	int                *BreakCode,
	const struct FarMenuItem *Item,
	int                 ItemsNumber
);


enum PLUGINPANELITEMFLAGS
{
	PPIF_PROCESSDESCR           = 0x80000000,
	PPIF_SELECTED               = 0x40000000,
	PPIF_USERDATA               = 0x20000000,
};

struct FAR_FIND_DATA
{
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	uint64_t nPhysicalSize;
	uint64_t nFileSize;
	DWORD    dwFileAttributes;
	DWORD    dwUnixMode;
#ifdef FAR_USE_INTERNALS
	wchar_t *lpwszFileName;
#else // ELSE FAR_USE_INTERNALS
	const wchar_t *lpwszFileName;
#endif // END FAR_USE_INTERNALS
};

struct PluginPanelItem
{
	struct FAR_FIND_DATA FindData;
	DWORD_PTR     UserData;
	DWORD         Flags;
	DWORD         NumberOfLinks;
	const wchar_t *Description;
	const wchar_t *Owner;
	const wchar_t *Group;
	const wchar_t * const *CustomColumnData;
	int           CustomColumnNumber;
	DWORD         CRC32;
	DWORD_PTR     Reserved[2];
};

enum PANELINFOFLAGS
{
	PFLAGS_SHOWHIDDEN         = 0x00000001,
	PFLAGS_HIGHLIGHT          = 0x00000002,
	PFLAGS_REVERSESORTORDER   = 0x00000004,
	PFLAGS_USESORTGROUPS      = 0x00000008,
	PFLAGS_SELECTEDFIRST      = 0x00000010,
	PFLAGS_REALNAMES          = 0x00000020,
	PFLAGS_NUMERICSORT        = 0x00000040,
	PFLAGS_PANELLEFT          = 0x00000080,
	PFLAGS_DIRECTORIESFIRST   = 0x00000100,
	PFLAGS_USECRC32           = 0x00000200,
	PFLAGS_CASESENSITIVESORT  = 0x00000400,
	PFLAGS_HL_MARKERS_NOSHOW  = 0x00000800,
	PFLAGS_HL_MARKERS_NOALIGN = 0x00001000,
};

enum PANELINFOTYPE
{
	PTYPE_FILEPANEL,
	PTYPE_TREEPANEL,
	PTYPE_QVIEWPANEL,
	PTYPE_INFOPANEL
};

struct PanelInfo
{
	int PanelType;
	int Plugin;
	RECT PanelRect;
	int ItemsNumber;
	int SelectedItemsNumber;
	int CurrentItem;
	int TopPanelItem;
	int Visible;
	int Focus;
	int ViewMode;
	int SortMode;
	DWORD Flags;
	DWORD Reserved;
};


struct PanelRedrawInfo
{
	int CurrentItem;
	int TopPanelItem;
};

struct CmdLineSelect
{
	int SelStart;
	int SelEnd;
};

struct FarPanelLocation
{
	const wchar_t *PluginName; // set to -1 if its plain directory navigation
	const wchar_t *HostFile; // if set the OpenFilePlugin is used and Item is ignored, otherwise its normal plugin
	LONG_PTR Item; // ignored if HostFile is not NULL
	const wchar_t *Path;
};

#define PANEL_NONE		((HANDLE)(-1))
#define PANEL_ACTIVE	((HANDLE)(-1))
#define PANEL_PASSIVE	((HANDLE)(-2))
#define PANEL_STOP		((HANDLE)(-1))

enum FILE_CONTROL_COMMANDS
{
	FCTL_CLOSEPLUGIN,
	FCTL_GETPANELINFO,
	FCTL_UPDATEPANEL,
	FCTL_REDRAWPANEL,
	FCTL_GETCMDLINE,
	FCTL_SETCMDLINE,
	FCTL_SETSELECTION,
	FCTL_SETVIEWMODE,
	FCTL_INSERTCMDLINE,
	FCTL_SETUSERSCREEN,
	FCTL_SETPANELDIR,
	FCTL_SETCMDLINEPOS,
	FCTL_GETCMDLINEPOS,
	FCTL_SETSORTMODE,
	FCTL_SETSORTORDER,
	FCTL_GETCMDLINESELECTEDTEXT,
	FCTL_SETCMDLINESELECTION,
	FCTL_GETCMDLINESELECTION,
	FCTL_CHECKPANELSEXIST,
	FCTL_SETNUMERICSORT,
	FCTL_GETUSERSCREEN,
	FCTL_ISACTIVEPANEL,
	FCTL_GETPANELITEM,
	FCTL_GETSELECTEDPANELITEM,
	FCTL_GETCURRENTPANELITEM,
	FCTL_GETPANELDIR,
	FCTL_GETCOLUMNTYPES,
	FCTL_GETCOLUMNWIDTHS,
	FCTL_BEGINSELECTION,
	FCTL_ENDSELECTION,
	FCTL_CLEARSELECTION,
	FCTL_SETDIRECTORIESFIRST,
	FCTL_GETPANELFORMAT,
	FCTL_GETPANELHOSTFILE,
	FCTL_SETCASESENSITIVESORT,
	FCTL_GETPANELPLUGINHANDLE, // Param2 points to value of type HANDLE, sets that value to handle of plugin that renders that panel or INVALID_HANDLE_VALUE
	FCTL_SETPANELLOCATION, // Param2 points to FarPanelLocation
};

typedef int (WINAPI *FARAPICONTROL)(
	HANDLE hPlugin,
	int Command,
	int Param1,
	LONG_PTR Param2
);

typedef void (WINAPI *FARAPITEXT)(
	int X,
	int Y,
	uint64_t Color,
	const wchar_t *Str
);

typedef HANDLE(WINAPI *FARAPISAVESCREEN)(int X1, int Y1, int X2, int Y2);

typedef void (WINAPI *FARAPIRESTORESCREEN)(HANDLE hScreen);


typedef int (WINAPI *FARAPIGETDIRLIST)(
	const wchar_t *Dir,
	struct FAR_FIND_DATA **pPanelItem,
	int *pItemsNumber
);

typedef int (WINAPI *FARAPIGETPLUGINDIRLIST)(
	INT_PTR PluginNumber,
	HANDLE hPlugin,
	const wchar_t *Dir,
	struct PluginPanelItem **pPanelItem,
	int *pItemsNumber
);

typedef void (WINAPI *FARAPIFREEDIRLIST)(struct FAR_FIND_DATA *PanelItem, int nItemsNumber);
typedef void (WINAPI *FARAPIFREEPLUGINDIRLIST)(struct PluginPanelItem *PanelItem, int nItemsNumber);

enum VIEWER_FLAGS
{
	VF_NONMODAL              = 0x00000001,
	VF_DELETEONCLOSE         = 0x00000002,
	VF_ENABLE_F6             = 0x00000004,
	VF_DISABLEHISTORY        = 0x00000008,
	VF_IMMEDIATERETURN       = 0x00000100,
	VF_DELETEONLYFILEONCLOSE = 0x00000200,
};

typedef int (WINAPI *FARAPIVIEWER)(
	const wchar_t *FileName,
	const wchar_t *Title,
	int X1,
	int Y1,
	int X2,
	int Y2,
	DWORD Flags,
	UINT CodePage
);

enum EDITOR_FLAGS
{
	EF_NONMODAL              = 0x00000001,
	EF_CREATENEW             = 0x00000002,
	EF_ENABLE_F6             = 0x00000004,
	EF_DISABLEHISTORY        = 0x00000008,
	EF_DELETEONCLOSE         = 0x00000010,
	EF_IMMEDIATERETURN       = 0x00000100,
	EF_DELETEONLYFILEONCLOSE = 0x00000200,
#ifdef FAR_USE_INTERNALS
	EF_LOCKED                = 0x00000400,

	EF_OPENMODE_MASK         = 0xF0000000,
	EF_OPENMODE_NEWIFOPEN    = 0x10000000,
	EF_OPENMODE_USEEXISTING  = 0x20000000,
	EF_OPENMODE_BREAKIFOPEN  = 0x30000000,
	EF_OPENMODE_RELOADIFOPEN = 0x40000000,
#endif // END FAR_USE_INTERNALS
#ifdef FAR_USE_INTERNALS
	EF_SERVICEREGION         = 0x00001000,
#endif // END FAR_USE_INTERNALS
};

enum EDITOR_EXITCODE
{
	EEC_OPEN_ERROR          = 0,
	EEC_MODIFIED            = 1,
	EEC_NOT_MODIFIED        = 2,
	EEC_LOADING_INTERRUPTED = 3,
#ifdef FAR_USE_INTERNALS
	EEC_OPENED_EXISTING     = 4,
	EEC_ALREADY_EXISTS      = 5,
	EEC_OPEN_NEWINSTANCE    = 6,
	EEC_RELOAD              = 7,
#endif // END FAR_USE_INTERNALS
};

typedef int (WINAPI *FARAPIEDITOR)(
	const wchar_t *FileName,
	const wchar_t *Title,
	int X1,
	int Y1,
	int X2,
	int Y2,
	DWORD Flags,
	int StartLine,
	int StartChar,
	UINT CodePage
);

typedef int (WINAPI *FARAPICMPNAME)(
	const wchar_t *Pattern,
	const wchar_t *String,
	int SkipPath
);


typedef const wchar_t*(WINAPI *FARAPIGETMSG)(
	INT_PTR PluginNumber,
	FarLangMsgID MsgId
);


enum FarHelpFlags
{
	FHELP_NOSHOWERROR = 0x80000000,
	FHELP_SELFHELP    = 0x00000000,
	FHELP_FARHELP     = 0x00000001,
	FHELP_CUSTOMFILE  = 0x00000002,
	FHELP_CUSTOMPATH  = 0x00000004,
	FHELP_USECONTENTS = 0x40000000,
};

typedef BOOL (WINAPI *FARAPISHOWHELP)(
	const wchar_t *ModuleName,
	const wchar_t *Topic,
	DWORD Flags
);

enum ADVANCED_CONTROL_COMMANDS
{
	ACTL_GETFARVERSION        = 0,
#ifdef FAR_USE_INTERNALS

#endif // END FAR_USE_INTERNALS
	ACTL_GETSYSWORDDIV        = 2,
	ACTL_WAITKEY              = 3,
	ACTL_GETCOLOR             = 4,
	ACTL_GETARRAYCOLOR        = 5,
	ACTL_EJECTMEDIA           = 6,
	ACTL_KEYMACRO             = 7,
	ACTL_POSTKEYSEQUENCE      = 8,
	ACTL_GETWINDOWINFO        = 9,
	ACTL_GETWINDOWCOUNT       = 10,
	ACTL_SETCURRENTWINDOW     = 11,
	ACTL_COMMIT               = 12,
	ACTL_GETFARHWND           = 13,
	ACTL_GETSYSTEMSETTINGS    = 14,
	ACTL_GETPANELSETTINGS     = 15,
	ACTL_GETINTERFACESETTINGS = 16,
	ACTL_GETCONFIRMATIONS     = 17,
	ACTL_GETDESCSETTINGS      = 18,
	ACTL_SETARRAYCOLOR        = 19,
#ifdef FAR_USE_INTERNALS

#endif // END FAR_USE_INTERNALS
	ACTL_GETPLUGINMAXREADDATA = 21,
	ACTL_GETDIALOGSETTINGS    = 22,
	ACTL_GETSHORTWINDOWINFO   = 23,
#ifdef FAR_USE_INTERNALS
	ACTL_REMOVEMEDIA          = 24,
	ACTL_GETMEDIATYPE         = 25,
	ACTL_GETPOLICIES          = 26,
#endif // END FAR_USE_INTERNALS
	ACTL_REDRAWALL            = 27,
	ACTL_SYNCHRO              = 28,
	ACTL_SETPROGRESSSTATE     = 29,
	ACTL_SETPROGRESSVALUE     = 30,
	ACTL_QUIT                 = 31,
	ACTL_GETFARRECT           = 32,
	ACTL_GETCURSORPOS         = 33,
	ACTL_SETCURSORPOS         = 34,
	ACTL_PROGRESSNOTIFY       = 35,
};

#ifdef FAR_USE_INTERNALS
enum FarPoliciesFlags
{
	FFPOL_MAINMENUSYSTEM        = 0x00000001,
	FFPOL_MAINMENUPANEL         = 0x00000002,
	FFPOL_MAINMENUINTERFACE     = 0x00000004,
	FFPOL_MAINMENULANGUAGE      = 0x00000008,
	FFPOL_MAINMENUPLUGINS       = 0x00000010,
	FFPOL_MAINMENUDIALOGS       = 0x00000020,
	FFPOL_MAINMENUCONFIRMATIONS = 0x00000040,
	FFPOL_MAINMENUPANELMODE     = 0x00000080,
	FFPOL_MAINMENUFILEDESCR     = 0x00000100,
	FFPOL_MAINMENUFOLDERDESCR   = 0x00000200,
	FFPOL_MAINMENUVIEWER        = 0x00000800,
	FFPOL_MAINMENUEDITOR        = 0x00001000,
	FFPOL_MAINMENUCOLORS        = 0x00004000,
	FFPOL_MAINMENUHILIGHT       = 0x00008000,
	FFPOL_MAINMENUSAVEPARAMS    = 0x00020000,

	FFPOL_CREATEMACRO           = 0x00040000,
	FFPOL_USEPSWITCH            = 0x00080000,
	FFPOL_PERSONALPATH          = 0x00100000,
	FFPOL_KILLTASK              = 0x00200000,
	FFPOL_SHOWHIDDENDRIVES      = 0x80000000,
};

#endif // END FAR_USE_INTERNALS

enum FarSystemSettings
{
	FSS_DELETETORECYCLEBIN             = 0x00000002,
	FSS_WRITETHROUGH                   = 0x00000004,
	FSS_RESERVED                       = 0x00000008,
	FSS_SAVECOMMANDSHISTORY            = 0x00000020,
	FSS_SAVEFOLDERSHISTORY             = 0x00000040,
	FSS_SAVEVIEWANDEDITHISTORY         = 0x00000080,
	FSS_USEWINDOWSREGISTEREDTYPES      = 0x00000100,
	FSS_AUTOSAVESETUP                  = 0x00000200,
	FSS_SCANSYMLINK                    = 0x00000400,
};

enum FarPanelSettings
{
	FPS_SHOWHIDDENANDSYSTEMFILES       = 0x00000001,
	FPS_HIGHLIGHTFILES                 = 0x00000002,
	FPS_AUTOCHANGEFOLDER               = 0x00000004,
	FPS_SELECTFOLDERS                  = 0x00000008,
	FPS_ALLOWREVERSESORTMODES          = 0x00000010,
	FPS_SHOWCOLUMNTITLES               = 0x00000020,
	FPS_SHOWSTATUSLINE                 = 0x00000040,
	FPS_SHOWFILESTOTALINFORMATION      = 0x00000080,
	FPS_SHOWFREESIZE                   = 0x00000100,
	FPS_SHOWSCROLLBAR                  = 0x00000200,
	FPS_SHOWBACKGROUNDSCREENSNUMBER    = 0x00000400,
	FPS_SHOWSORTMODELETTER             = 0x00000800,
};

enum FarDialogSettings
{
	FDIS_HISTORYINDIALOGEDITCONTROLS    = 0x00000001,
	FDIS_PERSISTENTBLOCKSINEDITCONTROLS = 0x00000002,
	FDIS_AUTOCOMPLETEININPUTLINES       = 0x00000004,
	FDIS_BSDELETEUNCHANGEDTEXT          = 0x00000008,
	FDIS_DELREMOVESBLOCKS               = 0x00000010,
	FDIS_MOUSECLICKOUTSIDECLOSESDIALOG  = 0x00000020,
};

enum FarInterfaceSettings
{
	FIS_CLOCKINPANELS                  = 0x00000001,
	FIS_CLOCKINVIEWERANDEDITOR         = 0x00000002,
	FIS_MOUSE                          = 0x00000004,
	FIS_SHOWKEYBAR                     = 0x00000008,
	FIS_ALWAYSSHOWMENUBAR              = 0x00000010,
	FIS_SHOWTOTALCOPYPROGRESSINDICATOR = 0x00000100,
	FIS_SHOWCOPYINGTIMEINFO            = 0x00000200,
	FIS_USECTRLPGUPTOCHANGEDRIVE       = 0x00000800,
	FIS_SHOWTOTALDELPROGRESSINDICATOR  = 0x00001000,
};

enum FarConfirmationsSettings
{
	FCS_COPYOVERWRITE                  = 0x00000001,
	FCS_MOVEOVERWRITE                  = 0x00000002,
	FCS_DRAGANDDROP                    = 0x00000004,
	FCS_DELETE                         = 0x00000008,
	FCS_DELETENONEMPTYFOLDERS          = 0x00000010,
	FCS_INTERRUPTOPERATION             = 0x00000020,
	FCS_DISCONNECTNETWORKDRIVE         = 0x00000040,
	FCS_RELOADEDITEDFILE               = 0x00000080,
	FCS_CLEARHISTORYLIST               = 0x00000100,
	FCS_EXIT                           = 0x00000200,
	FCS_OVERWRITEDELETEROFILES         = 0x00000400,
};

enum FarDescriptionSettings
{
	FDS_UPDATEALWAYS                   = 0x00000001,
	FDS_UPDATEIFDISPLAYED              = 0x00000002,
	FDS_SETHIDDEN                      = 0x00000004,
	FDS_UPDATEREADONLY                 = 0x00000008,
};

enum FAREJECTMEDIAFLAGS
{
	EJECT_NO_MESSAGE                    = 0x00000001,
	EJECT_LOAD_MEDIA                    = 0x00000002,
#ifdef FAR_USE_INTERNALS
	EJECT_NOTIFY_AFTERREMOVE            = 0x00000004,
	EJECT_READY                         = 0x80000000,
#endif // END FAR_USE_INTERNALS
};

struct ActlEjectMedia
{
	DWORD Letter;
	DWORD Flags;
};

#ifdef FAR_USE_INTERNALS
enum FARMEDIATYPE
{
	FMT_DRIVE_ERROR                =  -1,
	FMT_DRIVE_UNKNOWN              =  DRIVE_UNKNOWN,
	FMT_DRIVE_NO_ROOT_DIR          =  DRIVE_NO_ROOT_DIR,
	FMT_DRIVE_REMOVABLE            =  DRIVE_REMOVABLE,
	FMT_DRIVE_FIXED                =  DRIVE_FIXED,
	FMT_DRIVE_REMOTE               =  DRIVE_REMOTE,
	FMT_DRIVE_CDROM                =  DRIVE_CDROM,
	FMT_DRIVE_RAMDISK              =  DRIVE_RAMDISK,
	FMT_DRIVE_SUBSTITUTE           =  15,
	FMT_DRIVE_REMOTE_NOT_CONNECTED =  16,
	FMT_DRIVE_CD_RW                =  18,
	FMT_DRIVE_CD_RWDVD             =  19,
	FMT_DRIVE_DVD_ROM              =  20,
	FMT_DRIVE_DVD_RW               =  21,
	FMT_DRIVE_DVD_RAM              =  22,
	FMT_DRIVE_USBDRIVE             =  40,
	FMT_DRIVE_NOT_INIT             = 255,
};

enum FARMEDIATYPEFLAGS
{
	MEDIATYPE_NODETECTCDROM             = 0x80000000,
};

struct ActlMediaType
{
	DWORD Letter;
	DWORD Flags;
	DWORD Reserved[2];
};
#endif // END FAR_USE_INTERNALS

enum FARKEYSEQUENCEFLAGS
{
	KSFLAGS_DISABLEOUTPUT       = 0x00000001,
	KSFLAGS_NOSENDKEYSTOPLUGINS = 0x00000002,
	KSFLAGS_SILENTCHECK         = 0x00000001,
};

struct KeySequence
{
	DWORD Flags;
	int Count;
	const DWORD *Sequence;
};

enum FARMACROCOMMAND
{
	MCMD_LOADALL           = 0,
	MCMD_SAVEALL           = 1,
	MCMD_POSTMACROSTRING   = 2,
#ifdef FAR_USE_INTERNALS
	MCMD_COMPILEMACRO      = 3,
#endif // END FAR_USE_INTERNALS
	MCMD_CHECKMACRO        = 4,
	MCMD_GETSTATE          = 5,
	MCMD_GETAREA           = 6,
#ifdef FAR_USE_INTERNALS
	MCMD_RUNMACROSTRING    = 7,
#endif // END FAR_USE_INTERNALS
};

enum FARMACROAREA
{
	MACROAREA_OTHER             = 0,
	MACROAREA_SHELL             = 1,
	MACROAREA_VIEWER            = 2,
	MACROAREA_EDITOR            = 3,
	MACROAREA_DIALOG            = 4,
	MACROAREA_SEARCH            = 5,
	MACROAREA_DISKS             = 6,
	MACROAREA_MAINMENU          = 7,
	MACROAREA_MENU              = 8,
	MACROAREA_HELP              = 9,
	MACROAREA_INFOPANEL         =10,
	MACROAREA_QVIEWPANEL        =11,
	MACROAREA_TREEPANEL         =12,
	MACROAREA_FINDFOLDER        =13,
	MACROAREA_USERMENU          =14,
	MACROAREA_AUTOCOMPLETION    =15,
};

enum FARMACROSTATE
{
	MACROSTATE_NOMACRO          = 0,
	MACROSTATE_EXECUTING        = 1,
	MACROSTATE_EXECUTING_COMMON = 2,
	MACROSTATE_RECORDING        = 3,
	MACROSTATE_RECORDING_COMMON = 4,
};

enum FARMACROPARSEERRORCODE
{
	MPEC_SUCCESS                = 0,
	MPEC_UNRECOGNIZED_KEYWORD   = 1,
	MPEC_UNRECOGNIZED_FUNCTION  = 2,
	MPEC_FUNC_PARAM             = 3,
	MPEC_NOT_EXPECTED_ELSE      = 4,
	MPEC_NOT_EXPECTED_END       = 5,
	MPEC_UNEXPECTED_EOS         = 6,
	MPEC_EXPECTED_TOKEN         = 7,
	MPEC_BAD_HEX_CONTROL_CHAR   = 8,
	MPEC_BAD_CONTROL_CHAR       = 9,
	MPEC_VAR_EXPECTED           =10,
	MPEC_EXPR_EXPECTED          =11,
	MPEC_ZEROLENGTHMACRO        =12,
	MPEC_INTPARSERERROR         =13,
	MPEC_CONTINUE_OTL           =14,
};

struct MacroParseResult
{
	DWORD ErrCode;
	COORD ErrPos;
	const wchar_t *ErrSrc;
};

struct ActlKeyMacro
{
	int Command;
	union
	{
		struct
		{
			const wchar_t *SequenceText;
			DWORD Flags;
			DWORD AKey;
		} PlainText;
#ifdef FAR_USE_INTERNALS
		struct KeySequence Compile;
#endif // END FAR_USE_INTERNALS
		struct MacroParseResult MacroResult;
		DWORD_PTR Reserved[3];
	} Param;
};

#ifdef FAR_USE_INTERNALS
#if defined(PROCPLUGINMACROFUNC)
enum FARMACROVARTYPE
{
	FMVT_INTEGER                = 0,
	FMVT_STRING                 = 1,
	FMVT_DOUBLE                 = 2,
};

struct FarMacroValue
{
	enum FARMACROVARTYPE type;
	union
	{
		int64_t  i;
		double   d;
		const wchar_t *s;
	} v;
};

struct OpenMacroInfo
{
	size_t StructSize;
	size_t Count;
	struct FarMacroValue *Values;
};

struct FarMacroFunction
{
	DWORD Flags;
	const wchar_t *Name;
	int nParam;
	int oParam;
	const wchar_t *Syntax;
	const wchar_t *Description;
};
#endif
#endif // END FAR_USE_INTERNALS

enum FARCOLORFLAGS
{
	FCLR_REDRAW                 = 0x00000001,
};

struct FarSetColors
{
	DWORD Flags;
	int StartIndex;
	int ColorCount;
	uint64_t *Colors;
};

struct FarTrueColor
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char Flags; // bit one - 'active' flag, others - ignored and must be set to zero
};

struct FarTrueColorForeAndBack
{
	struct FarTrueColor Fore;
	struct FarTrueColor Back;
};

struct DialogItemTrueColors
{
	struct FarTrueColorForeAndBack Normal;
	struct FarTrueColorForeAndBack Hilighted;
	struct FarTrueColorForeAndBack Frame;
	struct FarTrueColorForeAndBack Reserved;
};

enum WINDOWINFO_TYPE
{
#ifdef FAR_USE_INTERNALS
	WTYPE_VIRTUAL,
	// ПРОСЬБА НЕ ЗАБЫВАТЬ СИНХРОНИЗИРОВАТЬ ИЗМЕНЕНИЯ
	// WTYPE_* и MODALTYPE_* (frame.hpp)!!!
	// (и не надо убирать этот комментарий, пока ситуация не изменится ;)
#endif // END FAR_USE_INTERNALS
	WTYPE_PANELS=1,
	WTYPE_VIEWER,
	WTYPE_EDITOR,
	WTYPE_DIALOG,
	WTYPE_VMENU,
	WTYPE_HELP,
#ifdef FAR_USE_INTERNALS
	WTYPE_COMBOBOX,
	WTYPE_FINDFOLDER,
	WTYPE_USER,
#endif // END FAR_USE_INTERNALS
};

struct WindowInfo
{
	int  Pos;
	int  Type;
	int  Modified;
	int  Current;
	wchar_t *TypeName;
	int TypeNameSize;
	wchar_t *Name;
	int NameSize;
};

typedef uint32_t PROGRESSTATE;

static const PROGRESSTATE
	PGS_NOPROGRESS   =0x0,
	PGS_INDETERMINATE=0x1,
	PGS_NORMAL       =0x2,
	PGS_ERROR        =0x4,
	PGS_PAUSED       =0x8;

struct PROGRESSVALUE
{
	uint64_t Completed;
	uint64_t Total;
};

typedef INT_PTR(WINAPI *FARAPIADVCONTROL)(
	INT_PTR ModuleNumber,
	int Command,
	void *Param1,
	void *Param2
);

enum VIEWER_CONTROL_COMMANDS
{
	VCTL_GETINFO,
	VCTL_QUIT,
	VCTL_REDRAW,
	VCTL_SETKEYBAR,
	VCTL_SETPOSITION,
	VCTL_SELECT,
	VCTL_SETMODE,
};

enum VIEWER_OPTIONS
{
	VOPT_SAVEFILEPOSITION=1,
	VOPT_AUTODETECTCODEPAGE=2,
};

enum VIEWER_SETMODE_TYPES
{
	VSMT_HEX,
	VSMT_WRAP,
	VSMT_WORDWRAP,
};

enum VIEWER_SETMODEFLAGS_TYPES
{
	VSMFL_REDRAW    = 0x00000001,
};

struct ViewerSetMode
{
	int Type;
	union
	{
		int iParam;
		wchar_t *wszParam;
	} Param;
	DWORD Flags;
	DWORD Reserved;
};

struct ViewerSelect
{
	int64_t BlockStartPos;
	int     BlockLen;
};

enum VIEWER_SETPOS_FLAGS
{
	VSP_NOREDRAW    = 0x0001,
	VSP_PERCENT     = 0x0002,
	VSP_RELATIVE    = 0x0004,
	VSP_NORETNEWPOS = 0x0008,
};

struct ViewerSetPosition
{
	DWORD Flags;
	int64_t StartPos;
	int64_t LeftPos;
};

struct ViewerMode
{
	UINT CodePage;
	int Wrap;
	int WordWrap;
	int Hex;
	int Processed;
	DWORD Reserved[3];
};

struct ViewerInfo
{
	int    StructSize;
	int    ViewerID;
	const wchar_t *FileName;
	int64_t FileSize;
	int64_t FilePos;
	int    WindowSizeX;
	int    WindowSizeY;
	DWORD  Options;
	int    TabSize;
	struct ViewerMode CurMode;
	int64_t LeftPos;
};

typedef int (WINAPI *FARAPIVIEWERCONTROL)(
	int Command,
	void *Param
);

enum VIEWER_EVENTS
{
	VE_READ       =0,
	VE_CLOSE      =1,

	VE_GOTFOCUS   =6,
	VE_KILLFOCUS  =7,
};


enum EDITOR_EVENTS
{
	EE_READ       =0,
	EE_SAVE       =1,
	EE_REDRAW     =2,
	EE_CLOSE      =3,

	EE_GOTFOCUS   =6,
	EE_KILLFOCUS  =7,
};

enum DIALOG_EVENTS
{
	DE_DLGPROCINIT    =0,
	DE_DEFDLGPROCINIT =1,
	DE_DLGPROCEND     =2,
};

enum SYNCHRO_EVENTS
{
	SE_COMMONSYNCHRO  =0,
};

#define EEREDRAW_ALL    (void*)0
#define EEREDRAW_CHANGE (void*)1
#define EEREDRAW_LINE   (void*)2

enum EDITOR_CONTROL_COMMANDS
{
	ECTL_GETSTRING,
	ECTL_SETSTRING,
	ECTL_INSERTSTRING,
	ECTL_DELETESTRING,
	ECTL_DELETECHAR,
	ECTL_INSERTTEXT,
	ECTL_GETINFO,
	ECTL_SETPOSITION,
	ECTL_SELECT,
	ECTL_REDRAW,
	ECTL_TABTOREAL,
	ECTL_REALTOTAB,
	ECTL_EXPANDTABS,
	ECTL_SETTITLE,
	ECTL_READINPUT,
	ECTL_PROCESSINPUT,
	ECTL_ADDCOLOR,
	ECTL_GETCOLOR,
	ECTL_SAVEFILE,
	ECTL_QUIT,
	ECTL_SETKEYBAR,
	ECTL_PROCESSKEY,
	ECTL_SETPARAM,
	ECTL_GETBOOKMARKS,
	ECTL_TURNOFFMARKINGBLOCK,
	ECTL_DELETEBLOCK,
	ECTL_ADDSTACKBOOKMARK,
	ECTL_PREVSTACKBOOKMARK,
	ECTL_NEXTSTACKBOOKMARK,
	ECTL_CLEARSTACKBOOKMARKS,
	ECTL_DELETESTACKBOOKMARK,
	ECTL_GETSTACKBOOKMARKS,
	ECTL_UNDOREDO,
	ECTL_GETFILENAME,
	ECTL_ADDTRUECOLOR,
	ECTL_GETTRUECOLOR,
};
//#ifdef FAR_USE_INTERNALS
//	ECTL_SERVICEREGION, // WTF
//#endif // END FAR_USE_INTERNALS

enum EDITOR_SETPARAMETER_TYPES
{
	ESPT_TABSIZE,
	ESPT_EXPANDTABS,
	ESPT_AUTOINDENT,
	ESPT_CURSORBEYONDEOL,
	ESPT_CHARCODEBASE,
	ESPT_CODEPAGE,
	ESPT_SAVEFILEPOSITION,
	ESPT_LOCKMODE,
	ESPT_SETWORDDIV,
	ESPT_GETWORDDIV,
	ESPT_SHOWWHITESPACE,
	ESPT_SETBOM,
};

#ifdef FAR_USE_INTERNALS
struct EditorServiceRegion
{
	int Command;
	DWORD Flags;
};
#endif // END FAR_USE_INTERNALS


struct EditorSetParameter
{
	int Type;
	union
	{
		int iParam;
		wchar_t *wszParam;
		DWORD Reserved1;
	} Param;
	DWORD Flags;
	DWORD Size;
};


enum EDITOR_UNDOREDO_COMMANDS
{
	EUR_BEGIN,
	EUR_END,
	EUR_UNDO,
	EUR_REDO
};


struct EditorUndoRedo
{
	int Command;
	DWORD_PTR Reserved[3];
};

struct EditorGetString
{
	int StringNumber;
#ifdef FAR_USE_INTERNALS
	wchar_t *StringText;
	wchar_t *StringEOL;
#else // ELSE FAR_USE_INTERNALS
	const wchar_t *StringText;
	const wchar_t *StringEOL;
#endif // END FAR_USE_INTERNALS
	int StringLength;
	int SelStart;
	int SelEnd;
};


struct EditorSetString
{
	int StringNumber;
	const wchar_t *StringText;
	const wchar_t *StringEOL;
	int StringLength;
};

enum EXPAND_TABS
{
	EXPAND_NOTABS,
	EXPAND_ALLTABS,
	EXPAND_NEWTABS
};


enum EDITOR_OPTIONS
{
	EOPT_EXPANDALLTABS     = 0x00000001,
	EOPT_PERSISTENTBLOCKS  = 0x00000002,
	EOPT_DELREMOVESBLOCKS  = 0x00000004,
	EOPT_AUTOINDENT        = 0x00000008,
	EOPT_SAVEFILEPOSITION  = 0x00000010,
	EOPT_AUTODETECTCODEPAGE= 0x00000020,
	EOPT_CURSORBEYONDEOL   = 0x00000040,
	EOPT_EXPANDONLYNEWTABS = 0x00000080,
	EOPT_SHOWWHITESPACE    = 0x00000100,
	EOPT_BOM               = 0x00000200,
};


enum EDITOR_BLOCK_TYPES
{
	BTYPE_NONE,
	BTYPE_STREAM,
	BTYPE_COLUMN
};

enum EDITOR_CURRENTSTATE
{
	ECSTATE_MODIFIED       = 0x00000001,
	ECSTATE_SAVED          = 0x00000002,
	ECSTATE_LOCKED         = 0x00000004,
};


struct EditorInfo
{
	int EditorID;
	int WindowSizeX;
	int WindowSizeY;
	int TotalLines;
	int CurLine;
	int CurPos;
	int CurTabPos;
	int TopScreenLine;
	int LeftPos;
	int Overtype;
	int BlockType;
	int BlockStartLine;
	DWORD Options;
	int TabSize;
	int BookMarkCount;
	DWORD CurState;
	UINT CodePage;
	DWORD Reserved[5];
};

struct EditorBookMarks
{
	long *Line;
	long *Cursor;
	long *ScreenLine;
	long *LeftPos;
	DWORD Reserved[4];
};

struct EditorSetPosition
{
	int CurLine;
	int CurPos;
	int CurTabPos;
	int TopScreenLine;
	int LeftPos;
	int Overtype;
};


struct EditorSelect
{
	int BlockType;
	int BlockStartLine;
	int BlockStartPos;
	int BlockWidth;
	int BlockHeight;
};


struct EditorConvertPos
{
	int StringNumber;
	int SrcPos;
	int DestPos;
};


enum EDITORCOLORFLAGS
{
	ECF_TAB1 = 0x10000,
};

struct EditorColor
{
	int StringNumber;
	int ColorItem;
	int StartPos;
	int EndPos;
	int Color;
};

struct EditorTrueColor
{
	struct EditorColor Base;
	struct FarTrueColorForeAndBack TrueColor;
};

struct EditorSaveFile
{
	const wchar_t *FileName;
	const wchar_t *FileEOL;
	UINT CodePage;
};

typedef int (WINAPI *FARAPIEDITORCONTROL)(
	int Command,
	void *Param
);

enum INPUTBOXFLAGS
{
	FIB_NONE             = 0x00000000,
	FIB_ENABLEEMPTY      = 0x00000001,
	FIB_PASSWORD         = 0x00000002,
	FIB_EXPANDENV        = 0x00000004,
	FIB_NOUSELASTHISTORY = 0x00000008,
	FIB_BUTTONS          = 0x00000010,
	FIB_NOAMPERSAND      = 0x00000020,
#ifdef FAR_USE_INTERNALS
	FIB_CHECKBOX         = 0x00010000,
#endif // END FAR_USE_INTERNALS
	FIB_EDITPATH         = 0x01000000,
};

typedef int (WINAPI *FARAPIINPUTBOX)(
	const wchar_t *Title,
	const wchar_t *SubTitle,
	const wchar_t *HistoryName,
	const wchar_t *SrcText,
	wchar_t *DestText,
	int   DestLength,
	const wchar_t *HelpTopic,
	DWORD Flags
);

typedef int (WINAPI *FARAPIPLUGINSCONTROL)(
	HANDLE hHandle,
	int Command,
	int Param1,
	LONG_PTR Param2
);

typedef int (WINAPI *FARAPIFILEFILTERCONTROL)(
	HANDLE hHandle,
	int Command,
	int Param1,
	LONG_PTR Param2
);

typedef int (WINAPI *FARAPIREGEXPCONTROL)(
	HANDLE hHandle,
	int Command,
	LONG_PTR Param
);

// <C&C++>
typedef int (WINAPIV *FARSTDSNPRINTF)(wchar_t *Buffer,size_t Sizebuf,const wchar_t *Format,...);
typedef int (WINAPIV *FARSTDSSCANF)(const wchar_t *Buffer, const wchar_t *Format,...);
// </C&C++>
typedef void (WINAPI *FARSTDQSORT)(void *base, size_t nelem, size_t width, int (__cdecl *fcmp)(const void *, const void *));
typedef void (WINAPI *FARSTDQSORTEX)(void *base, size_t nelem, size_t width, int (__cdecl *fcmp)(const void *, const void *,void *userparam),void *userparam);
typedef void   *(WINAPI *FARSTDBSEARCH)(const void *key, const void *base, size_t nelem, size_t width, int (__cdecl *fcmp)(const void *, const void *));
typedef int (WINAPI *FARSTDGETFILEOWNER)(const wchar_t *Computer,const wchar_t *Name,wchar_t *Owner,int Size);
typedef int (WINAPI *FARSTDGETFILEGROUP)(const wchar_t *Computer,const wchar_t *Name,wchar_t *Group,int Size);
typedef int (WINAPI *FARSTDGETNUMBEROFLINKS)(const wchar_t *Name);
typedef int (WINAPI *FARSTDATOI)(const wchar_t *s);
typedef int64_t (WINAPI *FARSTDATOI64)(const wchar_t *s);
typedef wchar_t   *(WINAPI *FARSTDITOA64)(int64_t value, wchar_t *string, int radix);
typedef wchar_t   *(WINAPI *FARSTDITOA)(int value, wchar_t *string, int radix);
typedef wchar_t   *(WINAPI *FARSTDLTRIM)(wchar_t *Str);
typedef wchar_t   *(WINAPI *FARSTDRTRIM)(wchar_t *Str);
typedef wchar_t   *(WINAPI *FARSTDTRIM)(wchar_t *Str);
// truncation functions below uses console cells count as limiting unit
typedef wchar_t   *(WINAPI *FARSTDTRUNCSTR)(wchar_t *Str,int MaxCells);
typedef wchar_t   *(WINAPI *FARSTDTRUNCPATHSTR)(wchar_t *Str,int MaxCells);
typedef wchar_t   *(WINAPI *FARSTDQUOTESPACEONLY)(wchar_t *Str);
typedef const wchar_t*(WINAPI *FARSTDPOINTTONAME)(const wchar_t *Path);
typedef int (WINAPI *FARSTDGETPATHROOT)(const wchar_t *Path,wchar_t *Root, int DestSize);
typedef BOOL (WINAPI *FARSTDADDENDSLASH)(wchar_t *Path);
typedef int (WINAPI *FARSTDCOPYTOCLIPBOARD)(const wchar_t *Data);
typedef wchar_t *(WINAPI *FARSTDPASTEFROMCLIPBOARD)(void);
typedef FarKey (WINAPI *FARSTDINPUTRECORDTOKEY)(const INPUT_RECORD *r);
typedef int (WINAPI *FARSTDLOCALISLOWER)(wchar_t Ch);
typedef int (WINAPI *FARSTDLOCALISUPPER)(wchar_t Ch);
typedef int (WINAPI *FARSTDLOCALISALPHA)(wchar_t Ch);
typedef int (WINAPI *FARSTDLOCALISALPHANUM)(wchar_t Ch);
typedef wchar_t (WINAPI *FARSTDLOCALUPPER)(wchar_t LowerChar);
typedef wchar_t (WINAPI *FARSTDLOCALLOWER)(wchar_t UpperChar);
typedef void (WINAPI *FARSTDLOCALUPPERBUF)(wchar_t *Buf,int Length);
typedef void (WINAPI *FARSTDLOCALLOWERBUF)(wchar_t *Buf,int Length);
typedef void (WINAPI *FARSTDLOCALSTRUPR)(wchar_t *s1);
typedef void (WINAPI *FARSTDLOCALSTRLWR)(wchar_t *s1);
typedef int (WINAPI *FARSTDLOCALSTRICMP)(const wchar_t *s1,const wchar_t *s2);
typedef int (WINAPI *FARSTDLOCALSTRNICMP)(const wchar_t *s1,const wchar_t *s2,int n);
typedef int (WINAPI *FARSTDLOCALSTRCMP)(const wchar_t *s1,const wchar_t *s2);
typedef int (WINAPI *FARSTDLOCALSTRNCMP)(const wchar_t *s1,const wchar_t *s2,int n);

enum PROCESSNAME_FLAGS
{
	PN_CMPNAME          = 0x00000000UL,
	PN_CMPNAMELIST      = 0x00010000UL,
	PN_GENERATENAME     = 0x00020000UL,
	PN_CHECKMASK        = 0x00030000UL,
	PN_SKIPPATH         = 0x01000000UL,
	PN_SHOWERRORMESSAGE = 0x02000000UL,
	PN_RESERVED1        = 0x04000000UL,
	PN_CASESENSITIVE    = 0x08000000UL,
	PN_NONE             = 0
};


typedef int (WINAPI *FARSTDPROCESSNAME)(const wchar_t *param1, wchar_t *param2, DWORD size, DWORD flags);

typedef void (WINAPI *FARSTDUNQUOTE)(wchar_t *Str);

enum XLATMODE
{
	XLAT_SWITCHKEYBLAYOUT  = 0x00000001UL, // unsupported
	XLAT_SWITCHKEYBBEEP    = 0x00000002UL, // unsupported
	XLAT_USEKEYBLAYOUTNAME = 0x00000004UL, // unsupported
	XLAT_CONVERTALLCMDLINE = 0x00010000UL, // deprecated
};

typedef size_t (WINAPI *FARSTDKEYTOKEYNAME)(FarKey Key,wchar_t *KeyText,size_t Size);

typedef wchar_t*(WINAPI *FARSTDXLAT)(wchar_t *Line,int StartPos,int EndPos,DWORD Flags);

typedef FarKey (WINAPI *FARSTDKEYNAMETOKEY)(const wchar_t *Name);

typedef int (WINAPI *FRSUSERFUNC)(
	const struct FAR_FIND_DATA *FData,
	const wchar_t *FullName,
	void *Param
);

enum FRSMODE
{
	FRS_NONE                 = 0x00,
	FRS_RETUPDIR             = 0x01,
	FRS_RECUR                = 0x02,
	FRS_SCANSYMLINK          = 0x04,
};

typedef void (WINAPI *FARSTDRECURSIVESEARCH)(const wchar_t *InitDir,const wchar_t *Mask,FRSUSERFUNC Func,DWORD Flags,void *Param);
typedef int (WINAPI *FARSTDMKTEMP)(wchar_t *Dest, DWORD size, const wchar_t *Prefix);
typedef void (WINAPI *FARSTDDELETEBUFFER)(void *Buffer);

enum MKLINKOP
{
	FLINK_HARDLINK         = 1,
	FLINK_JUNCTION         = 2,
	FLINK_VOLMOUNT         = 3,
	FLINK_SYMLINKFILE      = 4,
	FLINK_SYMLINKDIR       = 5,
	FLINK_SYMLINK          = 6,

	FLINK_SHOWERRMSG       = 0x10000,
	FLINK_DONOTUPDATEPANEL = 0x20000,
};
typedef int (WINAPI *FARSTDMKLINK)(const wchar_t *Src,const wchar_t *Dest,DWORD Flags);
typedef int (WINAPI *FARGETREPARSEPOINTINFO)(const wchar_t *Src, wchar_t *Dest,int DestSize);

enum CONVERTPATHMODES
{
	CPM_FULL,
	CPM_REAL,
	CPM_NATIVE,
};

typedef int (WINAPI *FARCONVERTPATH)(enum CONVERTPATHMODES Mode, const wchar_t *Src, wchar_t *Dest, int DestSize);

typedef DWORD (WINAPI *FARGETCURRENTDIRECTORY)(DWORD Size,wchar_t* Buffer);


enum EXECUTEFLAGS
{
	EF_HIDEOUT = 0x01,    // dont display output of the command
	EF_NOWAIT = 0x02,     // dont wait for command completion
	EF_SUDO = 0x04,       // command must be run with root privileges
	EF_NOTIFY = 0x08,     // notify when command completed (if such notifications enabled in settings)
	EF_NOCMDPRINT = 0x10, // dont print command in command line nor include it to history
	EF_OPEN = 0x20,       // use desktop shell (if present) to open command (e.g. URLs, documents..)
	EF_MAYBGND = 0x40,     // allow put command to background mode
	EF_EXTERNALTERM = 0x80 // execute command in configured external terminal
};

typedef int (WINAPI *FAREXECUTE)(const wchar_t *CmdStr, unsigned int ExecFlags);
typedef int (WINAPI *FAREXECUTE_LIBRARY)(const wchar_t *Library, const wchar_t *Symbol, const wchar_t *CmdStr, unsigned int ExecFlags);
typedef void (WINAPI *FARDISPLAYNOTIFICATION)(const wchar_t *action, const wchar_t *object);
typedef int (WINAPI *FARDISPATCHNTRTHRDCALLS)();
// If plugin implements tasks running in background it may invoke this function to indicate about
// pending task in left-top corner. Info is a short description of task or just its owner and must
// be same string when invoked with Started TRUE or FALSE.
typedef void (WINAPI *FARBACKGROUNDTASK)(const wchar_t *Info, BOOL Started);
// Returns count of console cells which will be used to display given string of CharsCount characters.
typedef size_t (WINAPI *FARSTRCELLSCOUNT)(const wchar_t *Str, size_t CharsCount);
// Returns count of characters which will be used for fill up to *CellsCount cells from given string
// of CharsCount characters.
// RoundUp argument tells what to do with full-width characters that crossed by *CellsCount.
// On return *CellsCount contains cells count that will be filled by returned characters count, that:
//  Can be smaller than initial value if string has too few characters to fill all *CellsCount cells
//  or if RoundUp was set to FALSE and last character would then overflow wanted amount.
//  Can be larger by one than initial value if RoundUp was set to TRUE and last full-width character
//  crossed initial value specified in *CellsCount.
typedef size_t (WINAPI *FARSTRSIZEOFCELLS)(const wchar_t *Str, size_t CharsCount, size_t *CellsCount, BOOL RoundUp);

//int WINAPI farGetFileOwner(const wchar_t *Computer, const wchar_t *Name, wchar_t *Owner, int Size)

typedef int (WINAPI *FARGETFILEOWNER)(const wchar_t *Computer, const wchar_t *Name, wchar_t *Owner, int Size);
typedef int (WINAPI *FARSETFILEGROUP)(const wchar_t *Computer, const wchar_t *Name, wchar_t *Group, int Size);
typedef int (WINAPI *FARESETFILEMODE)(const wchar_t *Name, DWORD Mode, int SkipMode);
typedef int (WINAPI *FARESETFILETIME)(const wchar_t *Name, FILETIME *AccessTime, FILETIME *ModifyTime, DWORD FileAttr, int SkipMode);
typedef int (WINAPI *FARESETFILEGROUP)(const wchar_t *Name, const wchar_t *Group, int SkipMode);
typedef int (WINAPI *FARESETFILEOWNER)(const wchar_t *Name, const wchar_t *Owner, int SkipMode);
typedef const char *(WINAPI *FAROWNERNAMEBYID)(uid_t id);
typedef const char *(WINAPI *FARGROUPNAMEBYID)(uid_t id);
typedef size_t (WINAPI *FARREADLINK)(const char *path, char *buf, size_t bufsiz);
typedef BOOL (WINAPI *FARSDCLSTAT)(const wchar_t *path, void *s);
typedef int (WINAPI *FARSDCSYMLINK)(const char *path1, const char *path2);
typedef BOOL (WINAPI *FARGETFINDDATA)(const wchar_t *lpwszFileName, WIN32_FIND_DATAW *FindDataW);

typedef int (WINAPI *FARGETDATEFORMAT)(void);
typedef wchar_t (WINAPI *FARGETDATESEPARATOR)(void);
typedef wchar_t (WINAPI *FARGETTIMESEPARATOR)(void);
typedef wchar_t (WINAPI *FARGETDECIMALSEPARATOR)(void);



// Exports to file virtual terminal history of given VT console
//  con_hnd - NULL means active console, otherise - must be one of handles obtained from VTEnumBackground
//  flags - is a combination of VT_LOGEXPORT_* constants
//  file - is a file path to be exported, if it points to empty string (i.e. *file = 0) then
//    it MUST be buffer of size at least MAX_PATH (4096) characters and VT history log will be
//    exported to file at autogenerated temporary path that will be copied into that buffer
// Returns TRUE on success
typedef BOOL (WINAPI *FARAPIVT_LOGEXPORT)(HANDLE con_hnd, DWORD flags, const wchar_t *file);

enum BOX_DEF_SYMBOLS
{
	BS_X_B0,          // 0xB0
	BS_X_B1,          // 0xB1
	BS_X_B2,          // 0xB2
	BS_V1,            // 0xB3
	BS_R_H1V1,        // 0xB4
	BS_R_H2V1,        // 0xB5
	BS_R_H1V2,        // 0xB6
	BS_RT_H1V2,       // 0xB7
	BS_RT_H2V1,       // 0xB8
	BS_R_H2V2,        // 0xB9
	BS_V2,            // 0xBA
	BS_RT_H2V2,       // 0xBB
	BS_RB_H2V2,       // 0xBC
	BS_RB_H1V2,       // 0xBD
	BS_RB_H2V1,       // 0xBE
	BS_RT_H1V1,       // 0xBF
	BS_LB_H1V1,       // 0xC0
	BS_B_H1V1,        // 0xC1
	BS_T_H1V1,        // 0xC2
	BS_L_H1V1,        // 0xC3
	BS_H1,            // 0xC4
	BS_C_H1V1,        // 0xC5
	BS_L_H2V1,        // 0xC6
	BS_L_H1V2,        // 0xC7
	BS_LB_H2V2,       // 0xC8
	BS_LT_H2V2,       // 0xC9
	BS_B_H2V2,        // 0xCA
	BS_T_H2V2,        // 0xCB
	BS_L_H2V2,        // 0xCC
	BS_H2,            // 0xCD
	BS_C_H2V2,        // 0xCE
	BS_B_H2V1,        // 0xCF
	BS_B_H1V2,        // 0xD0
	BS_T_H2V1,        // 0xD1
	BS_T_H1V2,        // 0xD2
	BS_LB_H1V2,       // 0xD3
	BS_LB_H2V1,       // 0xD4
	BS_LT_H2V1,       // 0xD5
	BS_LT_H1V2,       // 0xD6
	BS_C_H1V2,        // 0xD7
	BS_C_H2V1,        // 0xD8
	BS_RB_H1V1,       // 0xD9
	BS_LT_H1V1,       // 0xDA
	BS_X_DB,          // 0xDB
	BS_X_DC,          // 0xDC
	BS_X_DD,          // 0xDD
	BS_X_DE,          // 0xDE
	BS_X_DF,          // 0xDF
};


typedef struct FarStandardFunctions
{
	int StructSize;

	FARSTDATOI                 atoi;
	FARSTDATOI64               atoi64;
	FARSTDITOA                 itoa;
	FARSTDITOA64               itoa64;
	// <C&C++>
	FARSTDSSCANF               sscanf;
	// </C&C++>
	FARSTDQSORT                qsort;
	FARSTDBSEARCH              bsearch;
	FARSTDQSORTEX              qsortex;
	// <C&C++>
	FARSTDSNPRINTF             snprintf;
	// </C&C++>

	DWORD_PTR                  Reserved[7];
	const WCHAR *              BoxSymbols; // indexed via BOX_DEF_SYMBOLS

	FARSTDLOCALISLOWER         LIsLower;
	FARSTDLOCALISUPPER         LIsUpper;
	FARSTDLOCALISALPHA         LIsAlpha;
	FARSTDLOCALISALPHANUM      LIsAlphanum;
	FARSTDLOCALUPPER           LUpper;
	FARSTDLOCALLOWER           LLower;
	FARSTDLOCALUPPERBUF        LUpperBuf;
	FARSTDLOCALLOWERBUF        LLowerBuf;
	FARSTDLOCALSTRUPR          LStrupr;
	FARSTDLOCALSTRLWR          LStrlwr;
	FARSTDLOCALSTRICMP         LStricmp;
	FARSTDLOCALSTRNICMP        LStrnicmp;

	FARSTDUNQUOTE              Unquote;
	FARSTDLTRIM                LTrim;
	FARSTDRTRIM                RTrim;
	FARSTDTRIM                 Trim;
	FARSTDTRUNCSTR             TruncStr;
	FARSTDTRUNCPATHSTR         TruncPathStr;
	FARSTDQUOTESPACEONLY       QuoteSpaceOnly;
	FARSTDPOINTTONAME          PointToName;
	FARSTDGETPATHROOT          GetPathRoot;
	FARSTDADDENDSLASH          AddEndSlash;
	FARSTDCOPYTOCLIPBOARD      CopyToClipboard;
	FARSTDPASTEFROMCLIPBOARD   PasteFromClipboard;
	FARSTDKEYTOKEYNAME         FarKeyToName;
	FARSTDKEYNAMETOKEY         FarNameToKey;
	FARSTDINPUTRECORDTOKEY     FarInputRecordToKey;
	FARSTDXLAT                 XLat;
	FARSTDGETFILEOWNER         GetFileOwner;
	FARSTDGETNUMBEROFLINKS     GetNumberOfLinks;
	FARSTDRECURSIVESEARCH      FarRecursiveSearch;
	FARSTDMKTEMP               MkTemp;
	FARSTDDELETEBUFFER         DeleteBuffer;
	FARSTDPROCESSNAME          ProcessName;
	FARSTDMKLINK               MkLink;
	FARCONVERTPATH             ConvertPath;
	FARGETREPARSEPOINTINFO     GetReparsePointInfo;
	FARGETCURRENTDIRECTORY     GetCurrentDirectory;
	FAREXECUTE                 Execute;
	FAREXECUTE_LIBRARY         ExecuteLibrary;
	FARDISPLAYNOTIFICATION     DisplayNotification;
	FARDISPATCHNTRTHRDCALLS    DispatchInterThreadCalls;
	FARBACKGROUNDTASK          BackgroundTask;
	FARSTRCELLSCOUNT           StrCellsCount;
	FARSTRSIZEOFCELLS          StrSizeOfCells;

	FARSTDLOCALSTRICMP         LStrcmp;
	FARSTDLOCALSTRNICMP        LStrncmp;

	FARAPIVT_ENUM_BACKGROUND   VTEnumBackground;
	FARAPIVT_LOGEXPORT         VTLogExport;

//	FARSETFILEGROUP			   GetFileOwner;
	FARSETFILEGROUP			   GetFileGroup;
	FARESETFILEMODE			   ESetFileMode;
	FARESETFILETIME			   ESetFileTime;
	FARESETFILEGROUP		   ESetFileGroup;
	FARESETFILEOWNER		   ESetFileOwner;
	FAROWNERNAMEBYID		   OwnerNameByID;
	FARGROUPNAMEBYID		   GroupNameByID;
	FARGETFINDDATA			   GetFindData;
	FARGETDATEFORMAT		   GetDateFormat;
	FARGETDATESEPARATOR		   GetDateSeparator;
	FARGETTIMESEPARATOR		   GetTimeSeparator;
	FARGETDECIMALSEPARATOR	   GetDecimalSeparator;

} FARSTANDARDFUNCTIONS;

struct PluginStartupInfo
{
	int StructSize;
	const wchar_t *ModuleName;
	INT_PTR ModuleNumber;
	const wchar_t *RootKey;
	FARAPIMENU             Menu;
	FARAPIMESSAGE          Message;
	FARAPIGETMSG           GetMsg;
	FARAPICONTROL          Control;
	FARAPISAVESCREEN       SaveScreen;
	FARAPIRESTORESCREEN    RestoreScreen;
	FARAPIGETDIRLIST       GetDirList;
	FARAPIGETPLUGINDIRLIST GetPluginDirList;
	FARAPIFREEDIRLIST      FreeDirList;
	FARAPIFREEPLUGINDIRLIST FreePluginDirList;
	FARAPIVIEWER           Viewer;
	FARAPIEDITOR           Editor;
	FARAPICMPNAME          CmpName;
	FARAPITEXT             Text;
	FARAPIEDITORCONTROL    EditorControl;

	FARSTANDARDFUNCTIONS  *FSF;

	FARAPISHOWHELP         ShowHelp;
	FARAPIADVCONTROL       AdvControl;
	FARAPIADVCONTROL       AdvControlAsync;
	FARAPIINPUTBOX         InputBox;
	FARAPIDIALOGINIT       DialogInit;
	FARAPIDIALOGRUN        DialogRun;
	FARAPIDIALOGFREE       DialogFree;

	FARAPISENDDLGMESSAGE   SendDlgMessage;
	FARAPIDEFDLGPROC       DefDlgProc;
	DWORD_PTR              Reserved;
	FARAPIVIEWERCONTROL    ViewerControl;
	FARAPIPLUGINSCONTROL   PluginsControl;
	FARAPIFILEFILTERCONTROL FileFilterControl;
	FARAPIREGEXPCONTROL    RegExpControl;
};


enum PLUGIN_FLAGS
{
	PF_PRELOAD        = 0x0001, // early dlopen and initialize plugin
	PF_DISABLEPANELS  = 0x0002,
	PF_EDITOR         = 0x0004,
	PF_VIEWER         = 0x0008,
	PF_FULLCMDLINE    = 0x0010,
	PF_DIALOG         = 0x0020,
	PF_PREOPEN        = 0x8000 // early dlopen plugin but initialize it later, when it will be really needed
};

struct PluginInfo
{
	int StructSize;
	DWORD Flags;
	const wchar_t * const *DiskMenuStrings;
	int *Reserved0;
	int DiskMenuStringsNumber;
	const wchar_t * const *PluginMenuStrings;
	int PluginMenuStringsNumber;
	const wchar_t * const *PluginConfigStrings;
	int PluginConfigStringsNumber;
	const wchar_t *CommandPrefix;
#ifdef FAR_USE_INTERNALS
	DWORD SysID;
#else // ELSE FAR_USE_INTERNALS
	DWORD Reserved;
#endif // END FAR_USE_INTERNALS
#ifdef FAR_USE_INTERNALS
#if defined(PROCPLUGINMACROFUNC)
	int MacroFunctionNumber;
	const struct FarMacroFunction *MacroFunctions;
#endif
#endif // END FAR_USE_INTERNALS
};



struct InfoPanelLine
{
	const wchar_t *Text;
	const wchar_t *Data;
	int  Separator;
};

struct PanelMode
{
	const wchar_t *ColumnTypes;
	const wchar_t *ColumnWidths;
	const wchar_t * const *ColumnTitles;
	int    FullScreen;
	int    DetailedStatus;
	int    AlignExtensions;
	int    CaseConversion;
	const wchar_t *StatusColumnTypes;
	const wchar_t *StatusColumnWidths;
	DWORD  Reserved[2];
};


enum OPENPLUGININFO_FLAGS
{
	OPIF_NONE                    = 0,
	OPIF_USEFILTER               = 0x00000001,
	OPIF_USESORTGROUPS           = 0x00000002,
	OPIF_USEHIGHLIGHTING         = 0x00000004,
	OPIF_ADDDOTS                 = 0x00000008,
	OPIF_RAWSELECTION            = 0x00000010,
	OPIF_REALNAMES               = 0x00000020,
	OPIF_SHOWNAMESONLY           = 0x00000040,
	OPIF_SHOWRIGHTALIGNNAMES     = 0x00000080,
	OPIF_SHOWPRESERVECASE        = 0x00000100,
#ifdef FAR_USE_INTERNALS
#endif // END FAR_USE_INTERNALS
	OPIF_COMPAREFATTIME          = 0x00000400,
	OPIF_EXTERNALGET             = 0x00000800,
	OPIF_EXTERNALPUT             = 0x00001000,
	OPIF_EXTERNALDELETE          = 0x00002000,
	OPIF_EXTERNALMKDIR           = 0x00004000,
	OPIF_USEATTRHIGHLIGHTING     = 0x00008000,
	OPIF_USECRC32                = 0x00010000,
	OPIF_HL_MARKERS_NOSHOW       = 0x00020000,
	OPIF_HL_MARKERS_NOALIGN      = 0x00040000,

	OPIF_USEFREESIZE             = 0x00080000,
	OPIF_SHORTCUT                = 0x00100000,
	//
	OPIF_RECURSIVEPANEL          = 0x00200000,
	OPIF_DELETEFILEONCLOSE       = 0x00400000,
	OPIF_DELETEDIRONCLOSE        = 0x00800000,
};


enum OPENPLUGININFO_SORTMODES
{
	SM_DEFAULT,
	SM_UNSORTED,
	SM_NAME,
	SM_EXT,
	SM_MTIME,
	SM_CTIME,
	SM_ATIME,
	SM_SIZE,
	SM_DESCR,
	SM_OWNER,
	SM_COMPRESSEDSIZE,
	SM_NUMLINKS,
	SM_FULLNAME,
	SM_CHTIME,
};


struct KeyBarTitles
{
	wchar_t *Titles[12];
	wchar_t *CtrlTitles[12];
	wchar_t *AltTitles[12];
	wchar_t *ShiftTitles[12];

	wchar_t *CtrlShiftTitles[12];
	wchar_t *AltShiftTitles[12];
	wchar_t *CtrlAltTitles[12];
};

typedef uint32_t OPERATION_MODES;
FAR_INLINE_CONSTANT OPERATION_MODES
	OPM_SILENT     =0x0000000000000001ULL,
	OPM_FIND       =0x0000000000000002ULL,
	OPM_VIEW       =0x0000000000000004ULL,
	OPM_EDIT       =0x0000000000000008ULL,
	OPM_TOPLEVEL   =0x0000000000000010ULL,
	OPM_DESCR      =0x0000000000000020ULL,
	OPM_QUICKVIEW  =0x0000000000000040ULL,
	OPM_PGDN       =0x0000000000000080ULL,
	OPM_COMMANDS   =0x0000000000000100ULL,
	OPM_NONE       =0;

struct OpenPluginInfo
{
	int                   StructSize;
	DWORD                 Flags;
	const wchar_t           *HostFile;
	const wchar_t           *CurDir;
	const wchar_t           *Format;
	const wchar_t           *PanelTitle;
	const struct InfoPanelLine *InfoLines;
	int                   InfoLinesNumber;
	const wchar_t * const   *DescrFiles;
	int                   DescrFilesNumber;
	const struct PanelMode *PanelModesArray;
	int                   PanelModesNumber;
	int                   StartPanelMode;
	int                   StartSortMode;
	int                   StartSortOrder;
	const struct KeyBarTitles *KeyBar;
	const wchar_t           *ShortcutData;
	long                  Reserved;
};

struct AnalyseInfo
{
	size_t          StructSize;
	const wchar_t  *FileName;
	void           *Buffer;
	size_t          BufferSize;
	uint32_t     	OpMode;
	void			*Instance;
};

struct CloseAnalyseInfo
{
	size_t StructSize;
	HANDLE Handle;
	void* Instance;
};

struct OpenAnalyseInfo
{
	size_t StructSize;
	struct AnalyseInfo* Info;
	HANDLE Handle;
};

enum OPENPLUGIN_OPENFROM
{
	OPEN_FROM_MASK          = 0x000000FF,

	OPEN_DISKMENU           = 0,
	OPEN_PLUGINSMENU        = 1,
	OPEN_FINDLIST           = 2,
	OPEN_SHORTCUT           = 3,
	OPEN_COMMANDLINE        = 4,
	OPEN_EDITOR             = 5,
	OPEN_VIEWER             = 6,
	OPEN_FILEPANEL          = 7,
	OPEN_DIALOG             = 8,
	OPEN_ANALYSE            = 9,

	OPEN_FROMMACRO_MASK     = 0x000F0000,

	OPEN_FROMMACRO          = 0x00010000,
	OPEN_FROMMACROSTRING    = 0x00020000,
};

enum FAR_PKF_FLAGS
{
	PKF_CONTROL     = 0x00000001,
	PKF_ALT         = 0x00000002,
	PKF_SHIFT       = 0x00000004,
	PKF_PREPROCESS  = 0x00080000, // for "Key", function ProcessKey()
};

enum FAR_EVENTS
{
	FE_CHANGEVIEWMODE =0,
	FE_REDRAW         =1,
	FE_IDLE           =2,
	FE_CLOSE          =3,
	FE_BREAK          =4,
	FE_COMMAND        =5,

	FE_GOTFOCUS       =6,
	FE_KILLFOCUS      =7,
};

enum FAR_PLUGINS_CONTROL_COMMANDS
{
	PCTL_LOADPLUGIN         = 0,
	PCTL_UNLOADPLUGIN       = 1,
	PCTL_FORCEDLOADPLUGIN   = 2,

	PCTL_CACHEFORGET		= 3 // forgets cached information for specified plugin
};

enum FAR_PLUGIN_LOAD_TYPE
{
	PLT_PATH = 0,
};

enum FAR_FILE_FILTER_CONTROL_COMMANDS
{
	FFCTL_CREATEFILEFILTER = 0,
	FFCTL_FREEFILEFILTER,
	FFCTL_OPENFILTERSMENU,
	FFCTL_STARTINGTOFILTER,
	FFCTL_ISFILEINFILTER,
};

enum FAR_FILE_FILTER_TYPE
{
	FFT_PANEL = 0,
	FFT_FINDFILE,
	FFT_COPY,
	FFT_SELECT,
	FFT_CUSTOM,
};

enum FAR_REGEXP_CONTROL_COMMANDS
{
	RECTL_CREATE=0,
	RECTL_FREE,
	RECTL_COMPILE,
	RECTL_OPTIMIZE,
	RECTL_MATCHEX,
	RECTL_SEARCHEX,
	RECTL_BRACKETSCOUNT
};

struct RegExpMatch
{
	int start,end;
};

struct RegExpSearch
{
	const wchar_t* Text;
	int Position;
	int Length;
	struct RegExpMatch* Match;
	int Count;
	void* Reserved;
};


#if defined(__BORLANDC__) || defined(_MSC_VER) || defined(__GNUC__) || defined(__WATCOMC__)
#ifdef __cplusplus
extern "C"
{
#endif
// Exported Functions
	void   WINAPI _export PluginModuleOpen(const char *path);
	void   WINAPI _export ClosePluginW(HANDLE hPlugin);
	int    WINAPI _export CompareW(HANDLE hPlugin,const struct PluginPanelItem *Item1,const struct PluginPanelItem *Item2,unsigned int Mode);
	int    WINAPI _export ConfigureW(int ItemNumber);
	int    WINAPI _export DeleteFilesW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int OpMode);
	void   WINAPI _export ExitFARW(void);
	int    WINAPI _export MayExitFARW(void);
	void   WINAPI _export FreeFindDataW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber);
	void   WINAPI _export FreeVirtualFindDataW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber);
	int    WINAPI _export GetFilesW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int Move,const wchar_t **DestPath,int OpMode);
	int    WINAPI _export GetFindDataW(HANDLE hPlugin,struct PluginPanelItem **pPanelItem,int *pItemsNumber,int OpMode);
	int    WINAPI _export GetLinkTargetW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,wchar_t *Target,size_t TargetSize,int OpMode);
	int    WINAPI _export GetMinFarVersionW(void);
	void   WINAPI _export GetOpenPluginInfoW(HANDLE hPlugin,struct OpenPluginInfo *Info);
	void   WINAPI _export GetPluginInfoW(struct PluginInfo *Info);
	int    WINAPI _export GetVirtualFindDataW(HANDLE hPlugin,struct PluginPanelItem **pPanelItem,int *pItemsNumber,const wchar_t *Path);
	int    WINAPI _export MakeDirectoryW(HANDLE hPlugin,const wchar_t **Name,int OpMode);
	HANDLE WINAPI _export OpenFilePluginW(const wchar_t *Name,const unsigned char *Data,int DataSize,int OpMode);
	HANDLE WINAPI _export OpenPluginW(int OpenFrom,INT_PTR Item);
	int    WINAPI _export ProcessDialogEventW(int Event,void *Param);
	int    WINAPI _export ProcessEditorEventW(int Event,void *Param);
	int    WINAPI _export ProcessEditorInputW(const INPUT_RECORD *Rec);
	int    WINAPI _export ProcessEventW(HANDLE hPlugin,int Event,void *Param);
	int    WINAPI _export ProcessHostFileW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int OpMode);
	int    WINAPI _export ProcessKeyW(HANDLE hPlugin,int Key,unsigned int ControlState);
#ifdef FAR_USE_INTERNALS
	#if defined(PROCPLUGINMACROFUNC)
	int    WINAPI _export ProcessMacroFuncW(const wchar_t *Name, const struct FarMacroValue *Params, int nParams, struct FarMacroValue **Results, int *nResults);
	#endif
#endif // END FAR_USE_INTERNALS
	int    WINAPI _export ProcessSynchroEventW(int Event,void *Param);
	int    WINAPI _export ProcessViewerEventW(int Event,void *Param);
	int    WINAPI _export PutFilesW(HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int Move,const wchar_t *SrcPath,int OpMode);
	int    WINAPI _export SetDirectoryW(HANDLE hPlugin,const wchar_t *Dir,int OpMode);
	int    WINAPI _export SetFindListW(HANDLE hPlugin,const struct PluginPanelItem *PanelItem,int ItemsNumber);
	void   WINAPI _export SetStartupInfoW(const struct PluginStartupInfo *Info);

#ifdef __cplusplus
};
#endif
#endif

#ifndef _WIN64
#if defined(__BORLANDC__)
#pragma option -a.
#elif defined(__GNUC__) || (defined(__WATCOMC__) && (__WATCOMC__ < 1100)) || defined(__LCC__)
#pragma pack()
#else
#pragma pack(pop)
#endif
#endif

#endif /* RC_INVOKED */

#define EXP_NAME(p) _export p ## W

#endif /* __FAR2SDK_FARPLUG_WIDE_H__ */

