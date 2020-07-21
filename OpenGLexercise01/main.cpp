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
//�����λ�������ʱ�뻭�ģ���ʱ�������棬˳ʱ�뿴�����Ǳ���

#pragma region ģ������
////͸��������״
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

#pragma region ���봦��
glm::mat4 viewMat;
float lastX;
float lastY;
bool firstMouse = true;
glm::vec3 averagePos;
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{	//�Ӽ��̻�ȡ�������esc�͹ر�
		//glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ���롣
		//����������᷵����������Ƿ����ڱ�����,û���·���glfw_release = 1;

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

//#pragma region �ı�����
//
//void sphere2Ellip(LensArray & _rebuild_len, float _xlabelRatio, float _ylabelRatio)
//{
//	/*
//		_rebuild_len ��͸������
//		_xlabelRatio ��x���� ��Բ����/Բ�뾶
//		_ylabelRatio ��y���� ��Բ����/Բ�뾶
//		���ã�����͸��λ�ã�������Ӧ͸���ĵ�λ��
//	*/
//	for (vector<vector<Len>>::iterator it = _rebuild_len.m_lensArrayData.begin(); it != _rebuild_len.m_lensArrayData.end(); it++)
//	{
//		for (vector<Len>::iterator itl = it->begin(); itl != it->end(); itl++)
//		{
//			//����ÿһ��͸��
//			for (vector<glm::vec3>::iterator itp = itl->m_Image.begin(); itp != itl->m_Image.end(); itp++)
//			{
//				//����͸���е�ÿһ��������
//
//
//			}
//		}
//	}
//}
//#pragma endregion


int main(){

#pragma region Open  a Window
	//����ʹ�þ��
	glfwInit();			//ʹ��glfw�⣬�ɹ�����GL_TRUE,ʧ�ܷ���GL_FALSE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//�������Ĵ����������ԣ�ʹ��3.3�汾��OPENGL	����ʽ��ѡ�ѡ��ֵ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//����ָ��(pointer)����window���棬�������ڶ���
	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(1600, 1000, "My Lens experiment", NULL, NULL);
	if (window == NULL)
	{
		printf("Open window error!");
		glfwTerminate();
		return -1;
	}
	//ʹ�����������Ϊ��������
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Init GLEW
	glewExperimental = true;	//GLEW����������OPENGL����ָ��ģ�
	if (glewInit() != GLEW_OK)	//glewInit�ɹ��᷵��һ��ֵGLEW_OK,0??
	{
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 1600, 1000);		//�����ӿڣ��ʹ��ڵĴ�С��ͬ���ӿ��൱���ǿ����Ĳ��֣�0��0��ʾ�������½ǵ�λ�ã�800 * 600��С
	/*
		//���޳�
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	//�޳�����
	//glCullFace(GL_FRONT)	//�޳�����
	glFrontFace(GL_CW);	//��˳ʱ���Ϊ����

	*/
	glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region Init Shader Program
	//Shader ��������Init GLEW֮��
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
	//�任��˳�����Ҫ������-����ת-��λ��
	// V = ( Mt * Mr * Ms ) * V
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;

	projMat = glm::perspective(glm::radians(45.0f), 1600.0f / 1000.0f, 0.1f, 100.0f);
#pragma endregion


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	//����ʵ����
	Ball b1(glm::vec3(0, 0, -10.0f), 5.0f);
	//
	//Len l1(glm::vec3(0, 0, 0),0.5f);
	//l1.setArea(1.0f);
	//l1.lenImaging(b1.m_Data,b1.m_Center);
	////cout << "l1��͸��λ�� " <<l1.m_Position.x<< l1.m_Position.y << l1.m_Position.z << endl;
	//Len l2(l1.m_RebuildPosition, l1.m_foLength);
	////cout << "l2��͸��λ�� " << l2.m_Position.x << l2.m_Position.y << l2.m_Position.z << endl;

	//l2.lenImaging(l1.m_Image);

#pragma region ͸����
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


	//render loop ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//Process Input
		processInput(window);

		//clear screen	����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//����������������ɫ
		//���������ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		// ����viewMat
		viewMat = camera.GetViewMatrix();

		//��͸��λ��
		poslenShader->use();
		glUniformMatrix4fv(glGetUniformLocation(poslenShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(poslenShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		imageArr->drawlp(poslenShader);
		rebuildArr->drawlp(poslenShader);

		//����
		ballShader->use();
		b1.setColor(0.5f, 1.0f, 0.0f);
		glUniformMatrix4fv(glGetUniformLocation(ballShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(ballShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		b1.draw(ballShader);

		//��������ؽ����
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

//	#pragma region ��Ⱦ����
//		//Set Model matrix
//		modelMat = glm::translate(glm::mat4(1.0f), cubePosition);//�������ӵ�λ�þ���
//
//		//Set View and Projection Matrices here if you want
//
//		//Set Material -> Shader Program
//
//		//ʹ�ó���
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
//		glBindVertexArray(VAO);		//ÿ��ʹ�ð���һ��VAO��
//
//		//Drawcall
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 480);
//#pragma endregion
//
//

		// Clean up, prepare for next render loop
		glfwSwapBuffers(window);//����˫����
		glfwPollEvents();//��ȡ�û��Ĳ���
		camera.UpdareCameraPos();
	}

	//Exit Program
	glfwTerminate();
	return 0;

}

