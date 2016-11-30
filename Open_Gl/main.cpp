//#include <iostream>
#include <windows.h>
#include "glew.h"
#include "glut.h"
#include "ximage.h"


#define NEHE_OPENGL_LESSON_1
#define M_PI       3.14159265358979323846   // pi
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
HGLRC hRc = NULL;//������ɫ���������
HDC hDc = NULL;//OpenGL��Ⱦ����������
HWND hWnd = NULL;//���洰�ھ��
HINSTANCE hInstance = NULL;//�������ʵ��

bool keys[256];//������̰���������
bool active = true;//���ڵĻ��־
bool fullscreen = true;//ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ
GLfloat rtri; // ���������εĽǶ�
GLfloat rquad; // �����ı��εĽǶ�
CxImage img;
GLfloat xrot; // X ��ת��
GLfloat yrot; // Y ��ת��
GLfloat zrot; // Z ��ת��
GLuint texture[1]; // �洢һ������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//WndProc�Ķ���						 
GLvoid KillGLWindow(GLvoid);//�������ٴ���
BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag);//
GLvoid ReSizeGLScene(GLsizei w, GLsizei h)
{
	if (h == 0)
	{
		h = 1;
	}
	glViewport(0, 0, w, h);//���õ�ǰ���ӿ�
	glMatrixMode(GL_PROJECTION);//ѡ��ͶӰ����
	glLoadIdentity();//����ͶӰ����
	//�����ӿڵĴ�С
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);//ѡ��ģ�͹۲����
	glLoadIdentity();
}
int LoadGLTextures() // ����λͼ(��������Ĵ���)��ת��������
{
	int Status = FALSE;
	if (img.Load("tupian1.jpg", CXIMAGE_FORMAT_JPG))
	{
		Status = TRUE;
		glGenTextures(1, &texture[0]); // ��������
		// ʹ������λͼ�������� �ĵ�������
#if 1
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, img.GetBits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // �����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // �����˲�
#else
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.GetWidth(), img.GetHeight(),
			GL_RGB, GL_UNSIGNED_BYTE, img.GetBits());
#endif
	}
	return Status;
}

//�˴���OpenGL������������
int InitGL(GLvoid)
{
	if (!LoadGLTextures()) // ������������������
	{
		return FALSE; // ���δ�����룬����FALSE
	}
	glEnable(GL_TEXTURE_2D); // ��������ӳ��
	glShadeModel(GL_SMOOTH);//������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��ɫ����
	glClearDepth(1.0f);//������Ȼ���
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glDepthFunc(GL_LEQUAL);//������Ȳ�������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//����ϵͳ��͸�ӽ�������

	return TRUE;
}
//�˴���ʼ���л���
int DrawGLScene(GLvoid)
{
#if 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ļ����Ȼ���
	glLoadIdentity(); // ���õ�ǰ��ģ�͹۲����
	glTranslatef(0.0f, 0.0f, -5.0f); // ������Ļ 5 ����λ
	glRotatef(xrot, 0.0f, 0.0f, 1.0f); // ��X����ת
	//glRotatef(yrot, 0.0f, 1.0f, 0.0f); // ��Y����ת
	//glRotatef(zrot, 0.0f, 0.0f, 1.0f); // ��Z����ת

	glBindTexture(GL_TEXTURE_2D, texture[0]); // ѡ������
#if 1
	glBegin(GL_QUADS);
	// ǰ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
															 // ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
															  // ����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
															 // ����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
															  // ����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // ������ı��ε�����
															 // ����
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // ������ı��ε�����
	glEnd();
#else
	GLfloat vertex[4];
	GLfloat texcoord[2];
	GLfloat radius = 1.0;
	GLuint num_vertex = 160;
	const GLfloat delta_angle = 2.0 * M_PI / num_vertex;
	glBegin(GL_TRIANGLE_FAN);
	{
		//draw the vertex at the center of the circle  
		texcoord[0] = 0.5;
		texcoord[1] = 0.5;
		glTexCoord2fv(texcoord);
		vertex[0] = vertex[1] = vertex[2] = 0.0;
		vertex[3] = 1.0;
		glVertex4fv(vertex);

		//draw the vertex on the contour of the circle  
		for (GLuint i = 0; i < num_vertex; i++)
		{
			texcoord[0] = (cos(delta_angle * i) + 1.0) * 0.5;
			texcoord[1] = (sin(delta_angle * i) + 1.0) * 0.5;
			glTexCoord2fv(texcoord);

			vertex[0] = cos(delta_angle * i) * radius;
			vertex[1] = sin(delta_angle * i) * radius;
			vertex[2] = 0.0;
			vertex[3] = 1.0;
			glVertex4fv(vertex);
		}

		texcoord[0] = (1.0 + 1.0) * 0.5;
		texcoord[1] = (0.0 + 1.0) * 0.5;
		glTexCoord2fv(texcoord);

		vertex[0] = 1.0 * radius;
		vertex[1] = 0.0 * radius;
		vertex[2] = 0.0;
		vertex[3] = 1.0;
		glVertex4fv(vertex);
	}
	glEnd();
#endif
	xrot += 0.1f; // X ����ת
	//yrot += 0.2f; // Y ����ת
	//zrot += 0.4f; // Z ����ת

#else
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����Ļ����Ȼ���
	glLoadIdentity();//���õ�ǰ��ģ�͹۲����
	
	glTranslatef(-1.5f, 0.0f, -6.0f); // ���� 1.5 ��λ����������Ļ 6.0
	glRotatef(rtri, 0.0f, 1.0f, 0.0f); // ��Y����ת������
	glBegin(GL_TRIANGLES);//����������
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//�϶���
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//����
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//����

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//�϶���
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//����
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//����

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//�϶���
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//����
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//����

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//�϶���
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//����
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//����

	glEnd();

	glLoadIdentity(); // ����ģ�͹۲����
	glTranslatef(1.5f, 0.0f, -6.0f); // ����1.5��λ,��������Ļ 6.0
	glRotatef(rquad, 1.0f, 1.0f, 1.0f); // ��X����ת�ı���
	
	glBegin(GL_QUADS);//�����ı���
	//ǰ��
	glColor3f(1.0f, 0.0f, 0.0f);//red
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	//����
	glColor3f(1.0f, 1.0f, 0.0f);//yellow
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	//����
	glColor3f(0.0f, 1.0f, 0.0f);//green
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	//����
	glColor3f(0.0f, 1.0f, 1.0f);//green
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	
	//����
	glColor3f(0.0f, 0.0f, 1.0f);//blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	//����
	glColor3f(1.0f, 0.0f, 1.0f);//green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glEnd();

	rtri += 0.2f; // ���������ε���ת����
	rquad -= 0.15f; // �����ı��ε���ת����

	if (keys[VK_F1]) // F1��������ô?
	{
		keys[VK_F1] = FALSE; // ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
		KillGLWindow(); // ���ٵ�ǰ�Ĵ���
		fullscreen = !fullscreen; // �л� ȫ�� / ���� ģʽ
								  // �ؽ� OpenGL ����(�޸�)
		if (!CreateGLWindow("NeHe's ��һ������γ���", 640, 480, 16, fullscreen))
		{
			return 0; // �������δ�ܴ����������˳�
		}
	}
#endif
	return true;
}
//�������ٴ���
GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)//�Ƿ���ȫ��ģʽ
	{
		ChangeDisplaySettings(NULL, 0);//�ǵĻ����л�������
		ShowCursor(true);//��ʾ���ָ��
	}
	if (hRc) //�Ƿ�ӵ��OpenGL��Ⱦ������
	{
		if (!wglMakeCurrent(NULL,NULL))//�Ƿ�����ͷ�DC��RC������
		{
			MessageBox(NULL, "�ͷ�DC��RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRc))//�Ƿ����ɾ��RC
		{
			MessageBox(NULL, "�ͷ�RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		hRc = NULL;//��RC��ΪNULL
	}

	if (hDc && !ReleaseDC(hWnd,hDc))//�Ƿ�����ͷ�DC
	{
		MessageBox(NULL, "�ͷ�DCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION);
		hDc = NULL;//��hDc��ΪNULL
	}

	if (hWnd && !DestroyWindow(hWnd))//�Ƿ�������ٴ���
	{
		MessageBox(NULL, "�ͷŴ��ھ��ʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;//��hWnd��ΪNULL
	}

	if (!UnregisterClass("OpenGL",hInstance))
	{
		MessageBox(NULL, "����ע�������ࡣ", "�رմ���", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;//��hInstance��ΪNULL
	}
}

BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat; //�������ƥ��Ľ��
	WNDCLASS wc;//������ṹ
	DWORD dwExStyle;//��չ���ڷ��
	DWORD dwStyle;//���ڷ��

	RECT WindowRect;//ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left = (long)0;//��Left��Ϊ0
	WindowRect.right = (long)width;//��Right��ΪҪ��Ŀ��
	WindowRect.top = (long)0;//��top��Ϊ0
	WindowRect.bottom = (long)height;//��bottom��ΪҪ��ĸ߶�

	fullscreen = fullscreenflag;//����ȫ�ֱ���

	hInstance = GetModuleHandle(NULL);//ȡ�����ǵĴ��ڵ�ʵ��
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//�ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc = (WNDPROC)WndProc;//wndproc������Ϣ
	wc.cbClsExtra = 0;//�޶��ⴰ������
	wc.cbWndExtra = 0;//�޶��ⴰ������
	wc.hInstance = hInstance;//����ʵ��
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);//װ��ȱʡͼ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//װ�����ָ��
	wc.hbrBackground = NULL;//GL����Ҫ����
	wc.lpszMenuName = NULL;//����Ҫ�˵�
	wc.lpszClassName = "OpenGL";//�趨������

	if (!RegisterClass(&wc))//ע�ᴰ��
	{
		MessageBox(NULL, "ע�ᴰ��ʧ��", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}


	if (fullscreen)//����ȫ��ģʽ
	{
		DEVMODE dmScreenSettings;//�豸ģʽ
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));//����ڴ�
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);//DEVMODE�ṹ��Ĵ�С
		dmScreenSettings.dmPelsWidth = width;//��ѡ��Ļ�߶�
		dmScreenSettings.dmPelsHeight = height;//��ѡ��Ļ���
		dmScreenSettings.dmBitsPerPel = bits;//ÿ������ѡ�Ĳ�ɫ���
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//����������ʾģʽ�����ؽ����ע��CDS_FULLSCREEN��ȥ��״̬��
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��","NeHeG",MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;//ѡ�񴰿�ģʽ
			}
			else
			{
				//�����Ի��򣬸����û��������
				MessageBox(NULL, "���򽫱��ر�", "����", MB_YESNO | MB_ICONSTOP);
				return FALSE;
			}

		}
	}

	if (fullscreen) //�Ƿ���ȫ��ģʽ
	{
		dwExStyle = WS_EX_APPWINDOW;//��չ������
		dwStyle = WS_POPUP;//������
		ShowCursor(FALSE);//�������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;//��չ������
		dwStyle = WS_OVERLAPPEDWINDOW;//������
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);//�������ڴﵽ����Ҫ���С

	if (!(hWnd = CreateWindowEx(dwExStyle,//��չ������
								"OpenGL",//������
								title,//���ڱ���
								WS_CLIPSIBLINGS |//����Ĵ���������
								WS_CLIPCHILDREN	|//����Ĵ���������
								dwStyle,//ѡ��Ĵ�������
								0,0,//����λ��
								WindowRect.right-WindowRect.left,//��������õĴ��ڿ��
								WindowRect.bottom-WindowRect.top,//��������õĴ��ڿ��
								NULL,//�޸�����
								NULL,//�޲˵�
								hInstance,//ʵ��
								NULL)))//����WM_CREATE�����κζ���
	{
		KillGLWindow();//������ʾ��
		MessageBox(NULL, "���ܴ���һ�������豸������", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static PIXELFORMATDESCRIPTOR pfd = //pfd���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),//������ʽ�������Ĵ�С
		1,//�汾��
		PFD_DRAW_TO_WINDOW |//��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |//��ʽ֧��OpenGL
		PFD_DOUBLEBUFFER,//֧��˫����
		PFD_TYPE_RGBA,//����RGBA��ʽ
		bits,//ѡ��ɫ�����
		0,0,0,0,0,0,//���Ե�ɫ��λ
		0,//��Alpha����
		0,//����shiftbit
		0,//���ۼӻ���
		0,0,0,0,//���Ծۼ�λ
		16,//16λz���壨��Ȼ��棩
		0,//���ɰ滺��
		0,//�޸�������
		PFD_MAIN_PLANE,//����ͼ��
		0,//Reserved
		0,0,0//���Բ�����
	};

	if (!(hDc = GetDC(hWnd)))//ȡ���豸��������
	{
		KillGLWindow();//������ʾ��
		MessageBox(NULL, "���ܴ���һ����ƥ������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDc,&pfd)))//windows�ҵ���Ӧ�����ظ�ʽ
	{
		KillGLWindow();//������ʾ��
		MessageBox(NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDc, PixelFormat, &pfd)) // �ܹ��������ظ�ʽô?
	{
		KillGLWindow(); // ������ʾ��
		MessageBox(NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // ���� FALSE
	}

	if (!(hRc = wglCreateContext(hDc))) // �ܷ�ȡ����ɫ������?
	{
		KillGLWindow(); // ������ʾ��
		MessageBox(NULL, "���ܴ���OpenGL��Ⱦ������", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // ���� FALSE
	}

	if (!wglMakeCurrent(hDc, hRc)) // ���Լ�����ɫ������
	{
		KillGLWindow(); // ������ʾ��
		MessageBox(NULL, "���ܼ��ǰ��OpenGL��Ȼ������", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // ���� FALSE
	}

	ShowWindow(hWnd, SW_SHOW); // ��ʾ����
	SetForegroundWindow(hWnd); // ����������ȼ�
	SetFocus(hWnd); // ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height); // ����͸�� GL ��Ļ

	if (!InitGL()) // ��ʼ���½���GL����
	{
		KillGLWindow(); // ������ʾ��
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // ���� FALSE
	}

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, // ���ڵľ��
	UINT uMsg, // ���ڵ���Ϣ
	WPARAM wParam, // ���ӵ���Ϣ����
	LPARAM lParam) // ���ӵ���Ϣ����
{
	switch (uMsg) // ���Windows��Ϣ
	{
	case WM_ACTIVATE: // ���Ӵ��ڼ�����Ϣ
	{
		if (!HIWORD(wParam)) // �����С��״̬
		{
			active = TRUE; // �����ڼ���״̬
		}
		else
		{
			active = FALSE; // �����ټ���
		}
		return 0; // ������Ϣѭ��
	}
	case WM_SYSCOMMAND: // ϵͳ�ж�����
	{
		switch (wParam) // ���ϵͳ����
		{
		case SC_SCREENSAVE: // ����Ҫ����?
		case SC_MONITORPOWER: // ��ʾ��Ҫ����ڵ�ģʽ?
			return 0; // ��ֹ����
		}
		break; // �˳�
	}
	case WM_CLOSE: // �յ�Close��Ϣ?
	{
		PostQuitMessage(0); // �����˳���Ϣ
		return 0; // ����
	}
	case WM_KEYDOWN: // �м�����ô?
	{
		keys[wParam] = TRUE; // ����ǣ���ΪTRUE
		return 0; // ����
	}
	case WM_KEYUP: // �м��ſ�ô?
	{
		keys[wParam] = FALSE; // ����ǣ���ΪFALSE
		return 0; // ����
	}
	case WM_SIZE: // ����OpenGL���ڴ�С
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); // LoWord=Width,HiWord = Height
			return 0; // ����
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, // ��ǰ����ʵ��
	HINSTANCE hPrevInstance, // ǰһ������ʵ��
	LPSTR lpCmdLine, // �����в���
	int nCmdShow) // ������ʾ״̬
{
	MSG msg; // Windowsx��Ϣ�ṹ
	BOOL done = FALSE; // �����˳�ѭ����Bool ����
					   // ��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL, "������ȫ��ģʽ������ô��", "����ȫ��ģʽ", MB_YESNO |
		MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE; // FALSEΪ����ģʽ
	}

	// ����OpenGL����
	if (!CreateGLWindow("NeHe's OpenGL������", 640, 480, 16, fullscreen))
	{
		return 0; // ʧ���˳�
	}
	while (!done) // ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // ����Ϣ�ڵȴ���?
		{
			if (msg.message == WM_QUIT) // �յ��˳���Ϣ?
			{
				done = TRUE; // �ǣ���done=TRUE
			}
			else // ���ǣ���������Ϣ
			{
				TranslateMessage(&msg); // ������Ϣ
				DispatchMessage(&msg); // ������Ϣ
			}
		}
		else // ���û����Ϣ
		{
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active) // ���򼤻��ô?
			{
				if (keys[VK_ESCAPE]) // ESC ������ô?
				{
					done = TRUE; // ESC �����˳��ź�
				}
				else // �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene(); // ���Ƴ���
					SwapBuffers(hDc); // �������� (˫����)
				}
			}
			if (keys[VK_F1]) // F1��������ô?
			{
				keys[VK_F1] = FALSE; // ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow(); // ���ٵ�ǰ�Ĵ���
				fullscreen = !fullscreen; // �л� ȫ�� / ���� ģʽ
				 // �ؽ� OpenGL ����
				if (!CreateGLWindow("NeHe's OpenGL ������", 640, 480, 16, fullscreen))
				{
					return 0; // �������δ�ܴ����������˳�
				}
			}
		}
	}
	// �رճ���
	KillGLWindow(); // ���ٴ���
	return (msg.wParam); // �˳�����
}