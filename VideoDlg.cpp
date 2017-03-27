// VideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarClientDemo.h"
#include "VideoDlg.h"
#include "afxdialogex.h"
#include "AdManager.h"
#include "player.h"


// CVideoDlg �Ի���

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEODLG, pParent)
{
	m_pPlayer = NULL;
}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
	ON_MESSAGE(WM_APP_PLAYER_EVENT, &CVideoDlg::OnPlayerEvent)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVideoDlg ��Ϣ�������

LRESULT CVideoDlg::OnPlayerEvent(WPARAM pUnkPtr, LPARAM lp)
{
	HRESULT hr = m_pPlayer->HandleEvent(pUnkPtr);
	if (FAILED(hr))
	{
	}

	return 0;
}

BOOL CVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	AdManager& adManager = AdManager::getInstance();
	m_pPlayer = adManager.setVideoWnd(m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CVideoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_pPlayer)
	{
		m_pPlayer->ResizeVideo(cx, cy);
	}
}


void CVideoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_pPlayer && m_pPlayer->HasVideo())
	{
		// Video is playing. Ask the player to repaint.
		m_pPlayer->Repaint();
	}
	else
	{
		// The video is not playing, so we must paint the application window.
		RECT rc;
		GetClientRect(&rc);
		FillRect(dc, &rc, (HBRUSH)COLOR_WINDOW);
	}
}
