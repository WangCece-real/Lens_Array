#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "ConvexLens.h"

#include "Ball.h"
#include "Len.h"

#include <vector>
using namespace std;

#include "LensArray.h"
#include "ManageLensArray.h"
//三角形绘制是逆时针画的，逆时针是正面，顺时针看到的是背面

#pragma region 模型数据
////透镜中心形状
//float lp[] = {
//	// positions        
//	-0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f, -0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//
//	-0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f, -0.5f, -0.5f,
//
//	-0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f,  0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//};

#pragma endregion

#pragma region Camera Declare
// Instantiate Camera class
Camera camera(glm::vec3(0, 0, 30.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
LightDirectional lightD = LightDirectional(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));

#pragma endregion

#pragma region 输入处理
glm::mat4 viewMat;
float lastX;
float lastY;
bool firstMouse = true;
glm::vec3 averagePos;
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{	//从键盘获取，如果是esc就关闭
		//glfwGetKey函数，它需要一个窗口以及一个按键作为输入。
		//这个函数将会返回这个按键是否正在被按下,没按下返回glfw_release = 1;

		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){	
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else {
		camera.speedY = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		viewMat = camera.ClickChangeViewMatrix(1);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		viewMat = camera.ClickChangeViewMatrix(2);
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		viewMat = camera.ClickChangeViewMatrix(3);
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		viewMat = camera.ClickChangeViewMatrix(4);
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		viewMat = camera.SeeResult(5, averagePos);
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		viewMat = camera.SeeResult(6, averagePos);
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		viewMat = camera.SeeResult(7, averagePos);
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		viewMat = camera.SeeResult(0, averagePos);
	}

}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
#pragma endregion

//#pragma region 改变阵列
//
//void sphere2Ellip(LensArray & _rebuild_len, float _xlabelRatio, float _ylabelRatio)
//{
//	/*
//		_rebuild_len ：透镜阵列
//		_xlabelRatio ：x方向 椭圆长轴/圆半径
//		_ylabelRatio ：y方向 椭圆短轴/圆半径
//		作用：调整透镜位置，调整对应透镜的点位置
//	*/
//	for (vector<vector<Len>>::iterator it = _rebuild_len.m_lensArrayData.begin(); it != _rebuild_len.m_lensArrayData.end(); it++)
//	{
//		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
//		{
//			//遍历每一个透镜
//			for (vector<glm::vec3>::iterator itp = itl->m_Image.begin(); itp != itl->m_Image.end(); itp++)
//			{
//				//遍历透镜中的每一个成像结果
//
//
//			}
//		}
//	}
//}
//#pragma endregion


int main(){

#pragma region Open  a Window
	//这是使用句柄
	glfwInit();			//使用glfw库，成功返回GL_TRUE,失败返回GL_FALSE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//给创建的窗口设置属性，使用3.3版本的OPENGL	，格式（选项，选项值）
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//返回指针(pointer)放在window里面，创建窗口对象
	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(1600, 1000, "My Lens experiment", NULL, NULL);
	if (window == NULL)
	{
		printf("Open window error!");
		glfwTerminate();
		return -1;
	}
	//使用这个窗口作为主上下文
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Init GLEW
	glewExperimental = true;	//GLEW是用来管理OPENGL函数指针的？
	if (glewInit() != GLEW_OK)	//glewInit成功会返回一个值GLEW_OK,0??
	{
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 1600, 1000);		//设置视口，和窗口的大小不同，视口相当于是看见的部分，0，0表示窗口左下角的位置，800 * 600大小
	/*
		//面剔除
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	//剔除背面
	//glCullFace(GL_FRONT)	//剔除正面
	glFrontFace(GL_CW);	//将顺时针变为正面

	*/
	glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region Init Shader Program
	//Shader 创建放在Init GLEW之后
	//Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	Shader* lenShader = new Shader("LenVert.vert", "LenFrag.frag");
	Shader* ballShader = new Shader("BallVert.vert", "BallFrag.frag");
	Shader* poslenShader = new Shader("poslenVert.vert", "poslenFrag.frag");
#pragma endregion

#pragma region Init Material

#pragma endregion

#pragma region Init and Load Texture

#pragma endregion

#pragma region Prepare MVP matrices
	//calculate our transforamtion matrix here
	//变换的顺序很重要：缩放-》旋转-》位移
	// V = ( Mt * Mr * Ms ) * V
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;

	projMat = glm::perspective(glm::radians(45.0f), 1600.0f / 1000.0f, 0.1f, 100.0f);
#pragma endregion


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	//球类实例化
	Ball b1(glm::vec3(0, 0, -10.0f), 5.0f);
	//
	//Len l1(glm::vec3(0, 0, 0),0.5f);
	//l1.setArea(1.0f);
	//l1.lenImaging(b1.m_Data,b1.m_Center);
	////cout << "l1的透镜位置 " <<l1.m_Position.x<< l1.m_Position.y << l1.m_Position.z << endl;
	//Len l2(l1.m_RebuildPosition, l1.m_foLength);
	////cout << "l2的透镜位置 " << l2.m_Position.x << l2.m_Position.y << l2.m_Position.z << endl;

	//l2.lenImaging(l1.m_Image);

#pragma region 透镜阵
	int xNum = 44;
	int yNum = 44;
	float focusLength = 0.4f;
	float span = 0.25f;
	glm::vec3 lensArrayPosition = glm::vec3(-5, -5, 0);
	LensArray * imageArr = new LensArray(lensArrayPosition, xNum, yNum, span, focusLength, "MODE_I");
	LensArray * rebuildArr = new LensArray(imageArr->m_RebuildArrayPosition, xNum, yNum, span, focusLength, "MODE_R");
	//LensArray * rebuidArr = new LensArray(imageArr->m_RebuildArrayPosition, xNum, yNum, span, focusLength+0.005f, "MODE_R");
	for (int i = 0; i < imageArr->m_X; i++)
	{
		for (int j = 0; j < imageArr->m_Y; j++)
		{
			imageArr->m_lensArrayData[i][j].lenImaging(b1.m_Data, b1.m_Center);
			//if (imageArr->m_lensArrayData[i][j].m_Image.empty())
			//{	
			//	continue;
			//}
			rebuildArr->m_lensArrayData[i][j].lenImaging(imageArr->m_lensArrayData[i][j].m_Image);
			//cout <<"("<< imageArr->m_lensArrayData[i][j].m_Position.x <<","
			//	<< imageArr->m_lensArrayData[i][j].m_Position.y <<","
			//	<< imageArr->m_lensArrayData[i][j].m_Position.z << ") "<<endl;
		}
	}
	ManageLensArray mla;
	mla.sphere2Ellip(rebuildArr, 1.0f, 1.5f);
	mla.upDate(imageArr, rebuildArr);
	//rebuildArr->m_lensArrayData.clear();
	//for (int i = 0; i < imageArr->m_X; i++)
	//{
	//	for (int j = 0; j < imageArr->m_Y; j++)
	//	{
	//		rebuildArr->m_lensArrayData[i][j].m_Image.clear();
	//		rebuildArr->m_lensArrayData[i][j].lenImaging(imageArr->m_lensArrayData[i][j].m_Image);
	//		//cout <<"("<< imageArr->m_lensArrayData[i][j].m_Position.x <<","
	//		//	<< imageArr->m_lensArrayData[i][j].m_Position.y <<","
	//		//	<< imageArr->m_lensArrayData[i][j].m_Position.z << ") "<<endl;
	//	}
	//}


#pragma endregion


	//render loop 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//Process Input
		processInput(window);

		//clear screen	清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//设置用来清屏的颜色
		//清屏，可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		// 设置viewMat
		viewMat = camera.GetViewMatrix();

		//画透镜位置
		poslenShader->use();
		glUniformMatrix4fv(glGetUniformLocation(poslenShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(poslenShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		imageArr->drawlp(poslenShader);
		rebuildArr->drawlp(poslenShader);

		//画球
		ballShader->use();
		b1.setColor(0.5f, 1.0f, 0.0f);
		glUniformMatrix4fv(glGetUniformLocation(ballShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(ballShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		b1.draw(ballShader);

		//画成像和重建结果
		lenShader->use();
		glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		imageArr->draw(lenShader);
		glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		rebuildArr->draw(lenShader);
		//glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		//glUniformMatrix4fv(glGetUniformLocation(lenShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		//l1.draw(lenShader);
		//l2.draw(lenShader);

//	#pragma region 渲染物体
//		//Set Model matrix
//		modelMat = glm::translate(glm::mat4(1.0f), cubePosition);//各个箱子的位置矩阵
//
//		//Set View and Projection Matrices here if you want
//
//		//Set Material -> Shader Program
//
//		//使用程序
//		myShader->use();		
//
//		//Set Material -> Texture
//
//		//Set Material -> Uniforms
//		glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 0.0f, 1.0f, 0.0f);
//		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
//		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
//		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
//	
//	
//		// Set Model
//		glBindVertexArray(VAO);		//每次使用绑上一个VAO，
//
//		//Drawcall
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 480);
//#pragma endregion
//
//

		// Clean up, prepare for next render loop
		glfwSwapBuffers(window);//交换双缓冲
		glfwPollEvents();//获取用户的操作
		camera.UpdareCameraPos();
	}

	//Exit Program
	glfwTerminate();
	return 0;

}

