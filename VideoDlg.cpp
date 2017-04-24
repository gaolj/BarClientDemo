// VideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarClientDemo.h"
#include "VideoDlg.h"
#include "afxdialogex.h"
#include "AdManager.h"
#include "player.h"
#include "cgdiplusbitmap.h"


// CVideoDlg �Ի���

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEODLG, pParent)
{
	m_pPlayer = NULL;
	m_bitmap = NULL;
	m_gdiplusToken = 0;
}

CVideoDlg::~CVideoDlg()
{
	if (m_gdiplusToken)
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	if (m_bitmap)
		delete m_bitmap;

	AdManager::getInstance().closeVideoWnd();	// �ͷŲ�������ռ���ڴ�
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

	return 0;
}

BOOL CVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	AdManager& adManager = AdManager::getInstance();
	m_pPlayer = adManager.setVideoWnd(m_hWnd);
	if (!m_pPlayer)
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		auto status = Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
		if (status != Gdiplus::Status::Ok)
			AfxMessageBox("Gdiplus ��ʼ��ʧ��!");

		std::string strImage =  AdManager::getInstance().getLockImage();
		m_bitmap = new CGdiPlusBitmapResource;
		m_bitmap->Load(strImage);
	}

	return TRUE;  // return TRUE unless you set the focus to a control				  // �쳣: OCX ����ҳӦ���� FALSE
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
	else if (m_bitmap)
	{
		RECT rect;
		GetClientRect(&rect);

		Gdiplus::Graphics graphics(dc);
		graphics.DrawImage(*m_bitmap, 0, 0, rect.right, rect.bottom);
	}
	else
	{
		// The video is not playing, so we must paint the application window.
		RECT rc;
		GetClientRect(&rc);
		FillRect(dc, &rc, (HBRUSH)COLOR_WINDOW);
	}
}
