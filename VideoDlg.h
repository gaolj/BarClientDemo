#pragma once


// CVideoDlg �Ի���
class CPlayer;
class CGdiPlusBitmapResource;
class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoDlg();
	CPlayer *m_pPlayer;
	CGdiPlusBitmapResource *m_bitmap;
	ULONG_PTR m_gdiplusToken;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg LRESULT OnPlayerEvent(WPARAM pUnkPtr, LPARAM lp);
};
