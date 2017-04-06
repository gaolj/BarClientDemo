1、	定义CPlayer *m_pPlayer为视频显示窗口类的成员
	重要：使用m_pPlayer时，要判断m_pPlayer是否为NULL

2、在视频显示窗口创建完成后（OnInitDialog中）调用
	AdManager& adManager = AdManager::getInstance();
	m_pPlayer = adManager.setVideoWnd(m_hWnd);
	说明：
		setVideoWnd的返回值可能为NULL，所以在使用m_pPlayer的地方都需要判断是否为NULL
		m_hWnd为视频窗口的窗口句柄

3、增加三个消息处理函数
	afx_msg void OnSize(UINT nType, int cx, int cy);	// 如果视频显示窗口大小不会变，则可以不处理
	afx_msg void OnPaint();
	afx_msg LRESULT OnPlayerEvent(WPARAM pUnkPtr, LPARAM lp);

	及消息映射:
	BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
		ON_WM_SIZE()
		ON_WM_PAINT()
		ON_MESSAGE(WM_APP_PLAYER_EVENT, &CVideoDlg::OnPlayerEvent)
	END_MESSAGE_MAP()

4、三个消息处理函数中写入相同代码

