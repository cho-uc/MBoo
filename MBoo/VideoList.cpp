// VideoList.cpp : implementation of the CVideoList class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "define.h"

#include "VideoList.h"
#include "VideoWnd.h"

#define VIDEO_BUFFER_MAX_LEN	102400
static TCHAR request_buf[VIDEO_BUFFER_MAX_LEN];
static TCHAR response_buf[VIDEO_BUFFER_MAX_LEN];

void get_videoinfo_thread(void* data)
{
HWND hWndUI;
int i;
	hWndUI = (HWND)data;

	if(NULL == hWndUI) return;

	for(i=1; i<=10; i++)
	{
		PostMessage(hWndUI, WM_PROGRESS_SYNC_SHOW, 100, i*10);
		Sleep(1000);
	}
	PostMessage(hWndUI, WM_PROGRESS_SYNC_HIDE, 0, 0);
}

LRESULT CVideoList::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.ShowWindow(SW_HIDE);	
	pgs.SetRange(0, 100);

	::SkinSE_SubclassWindow(m_hWnd, _T("dlg.videolist"));
	::SkinSE_SetLayoutMainFrame(m_hWnd);

	::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_TREE_VIDEO), _T("list.tree.video"));
	::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_BTN_SYNC), _T("list.btn.sync"));
	::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_PGS_SYNC).m_hWnd, _T("list.pgs.sync"));

	CTreeViewCtrlEx treeVideo = GetDlgItem(IDC_LIST_TREE_VIDEO);
	CTreeItem ti1, ti2;
	ti1 = treeVideo.InsertItem(_T("Oracle��ѵ��Ƶ"), TVI_ROOT, TVI_LAST);
	ti2 = ti1.AddTail(_T("[С����ʦ]Oracle 12C Fundamental��ѵ��Ƶ"), 0);
	ti2.AddTail(_T("[bbk1109]��һ�� : Oracle 12C��Linux�µİ�װ"), 0);
	ti2.AddTail(_T("[bbk1312]�ڶ��� : Oracle��ϵ�ṹ����"), 0);
	ti2.AddTail(_T("[bbk1322]������ : ʹ��DBCA���ֹ�����"), 0);
	ti2.AddTail(_T("[bbk2341]���ļ� : ��ռ�������ļ�"), 0);
	ti2.AddTail(_T("[bbk3018]���弯 : ����Redo�ļ��͹鵵�ļ�"), 0);
	ti2 = ti1.AddTail(_T("[������ʦ]����RMAN���ݲ�������ѵ��Ƶ"), 0);
	ti2.AddTail(_T("[bbk1359]��һ�� : Oracle���ݸ���"), 0);
	ti2.AddTail(_T("[bbk1360]�ڶ��� : RMAN�Ļ���֪ʶ"), 0);
	ti2.AddTail(_T("[bbk1361]������ : �����Oracle���ݿ��ȫ��"), 0);
	ti2.AddTail(_T("[bbk1362]���ļ� : �����Oracle��������"), 0);
	ti2.AddTail(_T("[bbk1363]���弯 : �����������֮ʹ�ýű��Զ�������"), 0);
	ti1 = treeVideo.InsertItem(_T("Linux��ѵ��Ƶ"), TVI_ROOT, TVI_LAST);
	ti2 = ti1.AddTail(_T("[������ʦ]Ubuntu Linux���񲻷�����ѵ��Ƶ"), 0);
	ti2.AddTail(_T("[bbk1239]��һ�� : Linux�����ͷ�չ��ʷ"), 0);
	ti2.AddTail(_T("[bbk1240]�ڶ��� : Ubuntu Linux�Ļ���֪ʶ"), 0);
	ti2.AddTail(_T("[bbk5401]������ : Ubuntu Linux�İ�װ"), 0);
	ti2.AddTail(_T("[bbk5402]���ļ� : Linux������������"), 0);
	ti2.AddTail(_T("[bbk5403]���弯 : ����������棬�������θ"), 0);
	ti1 = treeVideo.InsertItem(_T("Java��ѵ��Ƶ"), TVI_ROOT, TVI_LAST);
	ti2 = ti1.AddTail(_T("[�ڹ���ʦ]Java�����ŵ���ͨ��ѵ��Ƶ"), 0);
	ti2.AddTail(_T("[bbk5239]��һ�� : Java�����ͷ�չ��ʷ"), 0);
	ti2.AddTail(_T("[bbk5240]�ڶ��� : ���Ŀ�������"), 0);
	ti2.AddTail(_T("[bbk5501]������ : һ�н��Ƕ���OOP����"), 0);
	ti2.AddTail(_T("[bbk5502]���ļ� : ���������±�����������Eclips����"), 0);
	ti2.AddTail(_T("[bbk5503]���弯 : ������Ĺ������������θ��ʹ��Git������Ĵ���"), 0);

	return TRUE;
}

LRESULT CVideoList::OnProgressShow(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.SetPos(lParam);
	return 0;
}

LRESULT CVideoList::OnProgressHide(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.ShowWindow(SW_HIDE);
	return 0;
}

BOOL CVideoList::WindowMove(UINT x, UINT y, UINT cx, UINT cy)
{
	if(NULL == m_hWnd) return FALSE;

	return (::SetWindowPos(m_hWnd, NULL, x, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE));
}

LRESULT CVideoList::OnBtnSyncVideo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
/*
	MessageBox(_T("�Ӳ�������վ���ݿ��ѯ��ƵĿ¼��Ϣ�����±�����ƵĿ¼��"));
	return 0;
	sqlite3 *db;
    char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("video.db", &db);
	if( rc )
	{
		MessageBox(_T("Cannot Open DB"));
		sqlite3_close(db);
		return 0;
	}

	rc = sqlite3_exec(db, "insert into t values(8)", callback, 0, &zErrMsg);
	if(SQLITE_OK != rc)
	{
		MessageBox(_T("INSERT err!"));
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
	MessageBox(_T("successfully!"));
*/
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.ShowWindow(SW_SHOW);	
	pgs.SetRange(0, 100);

	_beginthread(get_videoinfo_thread, 0, m_hWnd);
	return 0;
}

