
// mfc_openglDlg.h : 头文件
//

#pragma once
#pragma comment(lib,"../thirdparty/glut/glut32.lib")

#include "../thirdparty/glew/include/GL/glew.h"
#include "../thirdparty/glut/glut.h"


// Cmfc_openglDlg 对话框
class Cmfc_openglDlg : public CDialogEx
{
// 构造
public:
	Cmfc_openglDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT nIDEvent);
private:
	BOOL SetWindowPixelFormat(HDC hDC);  //设定像素格式
	BOOL CreateViewGLContext(HDC hDC);   //view GL Context
	void RenderScene();  //绘制场景
private:
	HDC hrenderDC;  //设备上下文
	HGLRC hrenderRC;  //渲染上下文
	float m_yRotate;  //转速
	int PixelFormat;    //像素格式
	float samples[2000][2];
};
