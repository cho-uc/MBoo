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

int find_video(TCHAR* result, UINT maxlen, TCHAR* path)
{
/*
UINT i = 0;
WIN32_FIND_DATA findata;
HANDLE hFind;
TCHAR videopath[MAX_PATH] = {0};

	//memset
	lstrcat(videopath, path);
	lstrcat(videopath, _T("\\bbk*"));

	hFind = FindFirstFile(videopath, &findata);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		result[0] = 0x00;
		return 0;
	}
	if(findata.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
	{

	}
	lstrcat(videopath, _T("\\"));
	lstrcat(videopath, _T("bbk*"));
	::MessageBox(hWndUI, videopath, _T("ϵͳ����"), MB_OK);
	hFind = FindFirstFile(videopath, &findata);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		::MessageBox(hWndUI, _T("��ָ��Ŀ¼���Ҳ�����Ƶ"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}
	if(findata.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
	{
		::MessageBox(hWndUI, _T("��ָ��Ŀ¼���Ҳ�����Ƶ"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}
*/	
	return 0;
}

void get_videoinfo_thread(void* data)
{
HWND hWndUI;
int i;
WIN32_FIND_DATA findata;
HANDLE hFind;
TCHAR videopath[MAX_PATH] = {0};

	hWndUI = (HWND)data;
	if(NULL == hWndUI) return;
/*
	lstrcat(videopath, g_MainDirectory);
	lstrcat(videopath, _T("\\"));
	lstrcat(videopath, _T("videos"));
	hFind = FindFirstFile(videopath, &findata);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		::MessageBox(hWndUI, _T("�Ҳ�����Ƶ���Ŀ¼"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}
	if(findata.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
	{
		::MessageBox(hWndUI, _T("�Ҳ�����Ƶ���Ŀ¼"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}
	lstrcat(videopath, _T("\\"));
	lstrcat(videopath, _T("bbk*"));
	::MessageBox(hWndUI, videopath, _T("ϵͳ����"), MB_OK);
	hFind = FindFirstFile(videopath, &findata);
	if(INVALID_HANDLE_VALUE == hFind)
	{
		::MessageBox(hWndUI, _T("��ָ��Ŀ¼���Ҳ�����Ƶ"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}
	if(findata.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
	{
		::MessageBox(hWndUI, _T("��ָ��Ŀ¼���Ҳ�����Ƶ"), _T("ϵͳ����"), MB_OK);
		goto exitthread;
	}

*/
/*
CURL *curl;
CURLcode res;
	curl_global_init(CURL_GLOBAL_WIN32);
	curl = curl_easy_init();

	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, DEFAULT_QUERY_URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "bbklist=BBKBEGIN|IP��ַ|CPU��ʶ|bbk1234|bbk4567|bbk7890|BBKEND");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
*/
	for(i=1; i<=10; i++)
	{
		PostMessage(hWndUI, WM_PROGRESS_SYNC_SHOW, 100, i*10);
		Sleep(1000);
	}

exitthread :
	PostMessage(hWndUI, WM_PROGRESS_SYNC_HIDE, 0, 0);
}

LRESULT CVideoList::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.ShowWindow(SW_HIDE);	
	pgs.SetRange(0, 100);

	::SkinSE_SubclassWindow(m_hWnd, _T("dlg.videolist"));
	::SkinSE_SetLayoutMainFrame(m_hWnd);

	//::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_TREE_VIDEO), _T("list.tree.video"));
	::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_BTN_SYNC), _T("list.btn.sync"));
	::SkinSE_SubclassWindow(GetDlgItem(IDC_LIST_PGS_SYNC).m_hWnd, _T("list.pgs.sync"));

	CTreeViewCtrlEx treeVideo = GetDlgItem(IDC_LIST_TREE_VIDEO);
	::SetWindowLong(treeVideo, GWL_STYLE, 
		treeVideo.GetStyle() | TVS_HASLINES | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP);

	PopulateVideoInfo();

	return TRUE;
}

LRESULT CVideoList::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc;

	GetClientRect(&rc);
	CTreeViewCtrlEx treeVideo = GetDlgItem(IDC_LIST_TREE_VIDEO);
	treeVideo.MoveWindow(0, 0, rc.right - rc.left - 3, rc.bottom -rc.top - DIALOG_PANEL_HEIGHT); 

	return TRUE;
}

LRESULT CVideoList::OnVideoSelected(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	if(NM_DBLCLK != pnmh->code) return FALSE;
	MessageBox(_T("ѡ��һ����Ƶ��"));
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
	CButton btnSync = GetDlgItem(IDC_LIST_BTN_SYNC);
	btnSync.EnableWindow(1);
	//btnSync.ShowWindow(SW_SHOW);
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

	CButton btnSync = GetDlgItem(IDC_LIST_BTN_SYNC);
	//btnSync.ShowWindow(SW_HIDE);
	btnSync.EnableWindow(0);
	CProgressBarCtrl pgs = GetDlgItem(IDC_LIST_PGS_SYNC);
	pgs.SetRange(0, 100);
	pgs.ShowWindow(SW_SHOW);	

	_beginthread(get_videoinfo_thread, 0, m_hWnd);
	return 0;
}

#define SQL_MAX_LEN	1024
void CVideoList::PopulateVideoInfo()
{
	sqlite3 *db;
	sqlite3_stmt *stmt = NULL;
	sqlite3_stmt *stmt1 = NULL;
    char *pcol = NULL;
	int rc,  cols;
	TCHAR msg[256] = {0};
	char sql[SQL_MAX_LEN] = {0};

	CTreeViewCtrlEx treeVideo = GetDlgItem(IDC_LIST_TREE_VIDEO);
	CTreeItem ti1, ti2;

	//WideCharToMultiByte(CP_ACP, WC_DISCARDNS, DEFAULT_VIDEO_DB, -1, buffer, SQL_MAX_LEN, NULL, NULL);

	rc = sqlite3_open(CT2A(DEFAULT_VIDEO_DB), &db);
	if( rc )
	{
		_stprintf_s(msg, 256, _T("�޷������ݿ��ļ�: %s\n"), DEFAULT_VIDEO_DB);
		sqlite3_close(db);
		MessageBox(msg);
		return;
	}
	sprintf_s(sql, SQL_MAX_LEN, "SELECT sid, tid, total, title, summary FROM series ORDER BY 1");
	if(SQLITE_OK != sqlite3_prepare_v2(db, sql, -1, &stmt,NULL))
	{
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		MessageBox(_T("ִ��SQL��ѯ����"));
		return;
	}
	
	cols = sqlite3_column_count(stmt);
	while(TRUE)
	{
		rc = sqlite3_step(stmt);
		if(SQLITE_ROW != rc)
		{
			break;
		}
		pcol = (char*)sqlite3_column_text(stmt,0);
		sprintf_s(sql, SQL_MAX_LEN, "SELECT vid, idx, title, summary FROM video WHERE sid=\'%s\' ORDER BY idx", pcol);
		pcol = (char*)sqlite3_column_text(stmt,3);
		CA2T szText(pcol, CP_ACP);
		ti1 = treeVideo.InsertItem(szText, TVI_ROOT, TVI_LAST);
		if(SQLITE_OK != sqlite3_prepare_v2(db, sql, -1, &stmt1,NULL))
		{
			sqlite3_finalize(stmt1);
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			MessageBox(_T("ִ��SQL��ѯ����"));
			return;
		}
		while(TRUE)
		{
			rc = sqlite3_step(stmt1);
			if(SQLITE_ROW != rc)
			{
				break;
			}
			pcol = (char*)sqlite3_column_text(stmt1,2);
			CA2T szText1(pcol, CP_ACP);
			ti2 = ti1.AddTail(szText1, 0);
		}
		sqlite3_finalize(stmt1);
		treeVideo.Expand(ti1);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

/*
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
*/

}
