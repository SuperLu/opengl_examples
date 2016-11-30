//#include <iostream>
#include <windows.h>
#include "glew.h"
#include "glut.h"
#include "ximage.h"


#define NEHE_OPENGL_LESSON_1
#define M_PI       3.14159265358979323846   // pi
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
HGLRC hRc = NULL;//窗口着色描述符句柄
HDC hDc = NULL;//OpenGL渲染描述符表句柄
HWND hWnd = NULL;//保存窗口句柄
HINSTANCE hInstance = NULL;//保存程序实例

bool keys[256];//保存键盘按键的数组
bool active = true;//窗口的活动标志
bool fullscreen = true;//全屏标志缺省，缺省设定成全屏模式
GLfloat rtri; // 用于三角形的角度
GLfloat rquad; // 用于四边形的角度
CxImage img;
GLfloat xrot; // X 旋转量
GLfloat yrot; // Y 旋转量
GLfloat zrot; // Z 旋转量
GLuint texture[1]; // 存储一个纹理

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//WndProc的定义						 
GLvoid KillGLWindow(GLvoid);//正常销毁窗口
BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag);//
GLvoid ReSizeGLScene(GLsizei w, GLsizei h)
{
	if (h == 0)
	{
		h = 1;
	}
	glViewport(0, 0, w, h);//重置当前的视口
	glMatrixMode(GL_PROJECTION);//选择投影矩阵
	glLoadIdentity();//重置投影矩阵
	//设置视口的大小
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);//选择模型观察矩阵
	glLoadIdentity();
}
int LoadGLTextures() // 载入位图(调用上面的代码)并转换成纹理
{
	int Status = FALSE;
	if (img.Load("tupian1.jpg", CXIMAGE_FORMAT_JPG))
	{
		Status = TRUE;
		glGenTextures(1, &texture[0]); // 创建纹理
		// 使用来自位图数据生成 的典型纹理
#if 1
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, img.GetBits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线形滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 线形滤波
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

//此处对OpenGL进行所有设置
int InitGL(GLvoid)
{
	if (!LoadGLTextures()) // 调用纹理载入子例程
	{
		return FALSE; // 如果未能载入，返回FALSE
	}
	glEnable(GL_TEXTURE_2D); // 启用纹理映射
	glShadeModel(GL_SMOOTH);//启用阴影平滑
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//黑色背景
	glClearDepth(1.0f);//设置深度缓存
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glDepthFunc(GL_LEQUAL);//启用深度测试类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//告诉系统对透视进行修正

	return TRUE;
}
//此处开始进行绘制
int DrawGLScene(GLvoid)
{
#if 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
	glLoadIdentity(); // 重置当前的模型观察矩阵
	glTranslatef(0.0f, 0.0f, -5.0f); // 移入屏幕 5 个单位
	glRotatef(xrot, 0.0f, 0.0f, 1.0f); // 绕X轴旋转
	//glRotatef(yrot, 0.0f, 1.0f, 0.0f); // 绕Y轴旋转
	//glRotatef(zrot, 0.0f, 0.0f, 1.0f); // 绕Z轴旋转

	glBindTexture(GL_TEXTURE_2D, texture[0]); // 选择纹理
#if 1
	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
															 // 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
															  // 顶面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
															 // 底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
															  // 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
															 // 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
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
	xrot += 0.1f; // X 轴旋转
	//yrot += 0.2f; // Y 轴旋转
	//zrot += 0.4f; // Z 轴旋转

#else
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除屏幕和深度缓存
	glLoadIdentity();//重置当前的模型观察矩阵
	
	glTranslatef(-1.5f, 0.0f, -6.0f); // 左移 1.5 单位，并移入屏幕 6.0
	glRotatef(rtri, 0.0f, 1.0f, 0.0f); // 绕Y轴旋转三角形
	glBegin(GL_TRIANGLES);//绘制三角形
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//上顶点
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//左下
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//右下

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//上顶点
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//左下
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//右下

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);//上顶点
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//左下
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//右下

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);//上顶点
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);//左下
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);//右下

	glEnd();

	glLoadIdentity(); // 重置模型观察矩阵
	glTranslatef(1.5f, 0.0f, -6.0f); // 右移1.5单位,并移入屏幕 6.0
	glRotatef(rquad, 1.0f, 1.0f, 1.0f); // 绕X轴旋转四边形
	
	glBegin(GL_QUADS);//绘制四边形
	//前面
	glColor3f(1.0f, 0.0f, 0.0f);//red
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	//后面
	glColor3f(1.0f, 1.0f, 0.0f);//yellow
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	//左面
	glColor3f(0.0f, 1.0f, 0.0f);//green
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	//右面
	glColor3f(0.0f, 1.0f, 1.0f);//green
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	
	//上面
	glColor3f(0.0f, 0.0f, 1.0f);//blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	//下面
	glColor3f(1.0f, 0.0f, 1.0f);//green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glEnd();

	rtri += 0.2f; // 增加三角形的旋转变量
	rquad -= 0.15f; // 减少四边形的旋转变量

	if (keys[VK_F1]) // F1键按下了么?
	{
		keys[VK_F1] = FALSE; // 若是，使对应的Key数组中的值为 FALSE
		KillGLWindow(); // 销毁当前的窗口
		fullscreen = !fullscreen; // 切换 全屏 / 窗口 模式
								  // 重建 OpenGL 窗口(修改)
		if (!CreateGLWindow("NeHe's 第一个多边形程序", 640, 480, 16, fullscreen))
		{
			return 0; // 如果窗口未能创建，程序退出
		}
	}
#endif
	return true;
}
//正常销毁窗口
GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)//是否处于全屏模式
	{
		ChangeDisplaySettings(NULL, 0);//是的话，切换回桌面
		ShowCursor(true);//显示鼠标指针
	}
	if (hRc) //是否拥有OpenGL渲染描述表
	{
		if (!wglMakeCurrent(NULL,NULL))//是否可以释放DC和RC描述表
		{
			MessageBox(NULL, "释放DC或RC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRc))//是否可以删除RC
		{
			MessageBox(NULL, "释放RC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION);
		}
		hRc = NULL;//将RC设为NULL
	}

	if (hDc && !ReleaseDC(hWnd,hDc))//是否可以释放DC
	{
		MessageBox(NULL, "释放DC失败。", "关闭错误", MB_OK | MB_ICONINFORMATION);
		hDc = NULL;//将hDc设为NULL
	}

	if (hWnd && !DestroyWindow(hWnd))//是否可以销毁窗口
	{
		MessageBox(NULL, "释放窗口句柄失败。", "关闭错误", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;//将hWnd设为NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))
	{
		MessageBox(NULL, "不能注销窗口类。", "关闭错误", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;//将hInstance设为NULL
	}
}

BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat; //保存查找匹配的结果
	WNDCLASS wc;//窗口类结构
	DWORD dwExStyle;//扩展窗口风格
	DWORD dwStyle;//窗口风格

	RECT WindowRect;//取得矩形的左上角和右下角的坐标值
	WindowRect.left = (long)0;//将Left设为0
	WindowRect.right = (long)width;//将Right设为要求的宽度
	WindowRect.top = (long)0;//将top设为0
	WindowRect.bottom = (long)height;//将bottom设为要求的高度

	fullscreen = fullscreenflag;//设置全局变量

	hInstance = GetModuleHandle(NULL);//取得我们的窗口的实例
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//移动时重画，并为窗口取得DC
	wc.lpfnWndProc = (WNDPROC)WndProc;//wndproc处理消息
	wc.cbClsExtra = 0;//无额外窗口数据
	wc.cbWndExtra = 0;//无额外窗口数据
	wc.hInstance = hInstance;//设置实例
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);//装入缺省图标
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//装入鼠标指针
	wc.hbrBackground = NULL;//GL不需要背景
	wc.lpszMenuName = NULL;//不需要菜单
	wc.lpszClassName = "OpenGL";//设定类名字

	if (!RegisterClass(&wc))//注册窗口
	{
		MessageBox(NULL, "注册窗口失败", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}


	if (fullscreen)//尝试全屏模式
	{
		DEVMODE dmScreenSettings;//设备模式
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));//清空内存
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);//DEVMODE结构体的大小
		dmScreenSettings.dmPelsWidth = width;//所选屏幕高度
		dmScreenSettings.dmPelsHeight = height;//所选屏幕宽度
		dmScreenSettings.dmBitsPerPel = bits;//每像素所选的彩色深度
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//尝试设置显示模式并返回结果。注：CDS_FULLSCREEN移去了状态条
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"全屏模式在当前显卡上设置失败！\n使用窗口模式？","NeHeG",MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;//选择窗口模式
			}
			else
			{
				//弹出对话框，告诉用户程序结束
				MessageBox(NULL, "程序将被关闭", "错误", MB_YESNO | MB_ICONSTOP);
				return FALSE;
			}

		}
	}

	if (fullscreen) //是否处于全屏模式
	{
		dwExStyle = WS_EX_APPWINDOW;//扩展窗体风格
		dwStyle = WS_POPUP;//窗体风格
		ShowCursor(FALSE);//隐藏鼠标指针
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;//扩展窗体风格
		dwStyle = WS_OVERLAPPEDWINDOW;//窗体风格
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);//调整窗口达到真正要求大小

	if (!(hWnd = CreateWindowEx(dwExStyle,//扩展窗体风格
								"OpenGL",//类名字
								title,//窗口标题
								WS_CLIPSIBLINGS |//必须的窗体风格属性
								WS_CLIPCHILDREN	|//必须的窗体风格属性
								dwStyle,//选择的窗体属性
								0,0,//窗口位置
								WindowRect.right-WindowRect.left,//计算调整好的窗口宽度
								WindowRect.bottom-WindowRect.top,//计算调整好的窗口宽度
								NULL,//无父窗口
								NULL,//无菜单
								hInstance,//实例
								NULL)))//不向WM_CREATE传递任何东西
	{
		KillGLWindow();//重置显示区
		MessageBox(NULL, "不能创建一个窗口设备描述表", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static PIXELFORMATDESCRIPTOR pfd = //pfd告诉窗口我们所希望的东西，即窗口使用的像素格式
	{
		sizeof(PIXELFORMATDESCRIPTOR),//上述格式描述符的大小
		1,//版本号
		PFD_DRAW_TO_WINDOW |//格式支持窗口
		PFD_SUPPORT_OPENGL |//格式支持OpenGL
		PFD_DOUBLEBUFFER,//支持双缓冲
		PFD_TYPE_RGBA,//申请RGBA格式
		bits,//选定色彩深度
		0,0,0,0,0,0,//忽略的色彩位
		0,//无Alpha缓冲
		0,//忽略shiftbit
		0,//无累加缓冲
		0,0,0,0,//忽略聚集位
		16,//16位z缓冲（深度缓存）
		0,//无蒙版缓存
		0,//无辅助缓存
		PFD_MAIN_PLANE,//主绘图层
		0,//Reserved
		0,0,0//忽略层遮罩
	};

	if (!(hDc = GetDC(hWnd)))//取得设备描述符表
	{
		KillGLWindow();//重置显示区
		MessageBox(NULL, "不能创建一种相匹配的像素格式", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDc,&pfd)))//windows找到相应的像素格式
	{
		KillGLWindow();//重置显示区
		MessageBox(NULL, "不能设置像素格式", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDc, PixelFormat, &pfd)) // 能够设置象素格式么?
	{
		KillGLWindow(); // 重置显示区
		MessageBox(NULL, "不能设置像素格式", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // 返回 FALSE
	}

	if (!(hRc = wglCreateContext(hDc))) // 能否取得着色描述表?
	{
		KillGLWindow(); // 重置显示区
		MessageBox(NULL, "不能创建OpenGL渲染描述表", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // 返回 FALSE
	}

	if (!wglMakeCurrent(hDc, hRc)) // 尝试激活着色描述表
	{
		KillGLWindow(); // 重置显示区
		MessageBox(NULL, "不能激活当前的OpenGL渲然描述表", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // 返回 FALSE
	}

	ShowWindow(hWnd, SW_SHOW); // 显示窗口
	SetForegroundWindow(hWnd); // 略略提高优先级
	SetFocus(hWnd); // 设置键盘的焦点至此窗口
	ReSizeGLScene(width, height); // 设置透视 GL 屏幕

	if (!InitGL()) // 初始化新建的GL窗口
	{
		KillGLWindow(); // 重置显示区
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // 返回 FALSE
	}

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, // 窗口的句柄
	UINT uMsg, // 窗口的消息
	WPARAM wParam, // 附加的消息内容
	LPARAM lParam) // 附加的消息内容
{
	switch (uMsg) // 检查Windows消息
	{
	case WM_ACTIVATE: // 监视窗口激活消息
	{
		if (!HIWORD(wParam)) // 检查最小化状态
		{
			active = TRUE; // 程序处于激活状态
		}
		else
		{
			active = FALSE; // 程序不再激活
		}
		return 0; // 返回消息循环
	}
	case WM_SYSCOMMAND: // 系统中断命令
	{
		switch (wParam) // 检查系统调用
		{
		case SC_SCREENSAVE: // 屏保要运行?
		case SC_MONITORPOWER: // 显示器要进入节电模式?
			return 0; // 阻止发生
		}
		break; // 退出
	}
	case WM_CLOSE: // 收到Close消息?
	{
		PostQuitMessage(0); // 发出退出消息
		return 0; // 返回
	}
	case WM_KEYDOWN: // 有键按下么?
	{
		keys[wParam] = TRUE; // 如果是，设为TRUE
		return 0; // 返回
	}
	case WM_KEYUP: // 有键放开么?
	{
		keys[wParam] = FALSE; // 如果是，设为FALSE
		return 0; // 返回
	}
	case WM_SIZE: // 调整OpenGL窗口大小
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); // LoWord=Width,HiWord = Height
			return 0; // 返回
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, // 当前窗口实例
	HINSTANCE hPrevInstance, // 前一个窗口实例
	LPSTR lpCmdLine, // 命令行参数
	int nCmdShow) // 窗口显示状态
{
	MSG msg; // Windowsx消息结构
	BOOL done = FALSE; // 用来退出循环的Bool 变量
					   // 提示用户选择运行模式
	if (MessageBox(NULL, "你想在全屏模式下运行么？", "设置全屏模式", MB_YESNO |
		MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE; // FALSE为窗口模式
	}

	// 创建OpenGL窗口
	if (!CreateGLWindow("NeHe's OpenGL程序框架", 640, 480, 16, fullscreen))
	{
		return 0; // 失败退出
	}
	while (!done) // 保持循环直到 done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 有消息在等待吗?
		{
			if (msg.message == WM_QUIT) // 收到退出消息?
			{
				done = TRUE; // 是，则done=TRUE
			}
			else // 不是，处理窗口消息
			{
				TranslateMessage(&msg); // 翻译消息
				DispatchMessage(&msg); // 发送消息
			}
		}
		else // 如果没有消息
		{
			// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息
			if (active) // 程序激活的么?
			{
				if (keys[VK_ESCAPE]) // ESC 按下了么?
				{
					done = TRUE; // ESC 发出退出信号
				}
				else // 不是退出的时候，刷新屏幕
				{
					DrawGLScene(); // 绘制场景
					SwapBuffers(hDc); // 交换缓存 (双缓存)
				}
			}
			if (keys[VK_F1]) // F1键按下了么?
			{
				keys[VK_F1] = FALSE; // 若是，使对应的Key数组中的值为 FALSE
				KillGLWindow(); // 销毁当前的窗口
				fullscreen = !fullscreen; // 切换 全屏 / 窗口 模式
				 // 重建 OpenGL 窗口
				if (!CreateGLWindow("NeHe's OpenGL 程序框架", 640, 480, 16, fullscreen))
				{
					return 0; // 如果窗口未能创建，程序退出
				}
			}
		}
	}
	// 关闭程序
	KillGLWindow(); // 销毁窗口
	return (msg.wParam); // 退出程序
}