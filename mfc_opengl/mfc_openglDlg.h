
// mfc_openglDlg.h : ͷ�ļ�
//

#pragma once
#pragma comment(lib,"../thirdparty/glut/glut32.lib")

#include "../thirdparty/glew/include/GL/glew.h"
#include "../thirdparty/glut/glut.h"


// Cmfc_openglDlg �Ի���
class Cmfc_openglDlg : public CDialogEx
{
// ����
public:
	Cmfc_openglDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT nIDEvent);
private:
	BOOL SetWindowPixelFormat(HDC hDC);  //�趨���ظ�ʽ
	BOOL CreateViewGLContext(HDC hDC);   //view GL Context
	void RenderScene();  //���Ƴ���
private:
	HDC hrenderDC;  //�豸������
	HGLRC hrenderRC;  //��Ⱦ������
	float m_yRotate;  //ת��
	int PixelFormat;    //���ظ�ʽ
	float samples[2000][2];
};
