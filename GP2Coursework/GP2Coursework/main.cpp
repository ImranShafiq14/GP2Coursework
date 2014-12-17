//Header files
#include <iostream>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "FBXLoader.h"

//header for SDL2 functionality
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <SDL_ttf.h>

using namespace std;

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec4;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "Transform.h"
#include "Component.h"
#include "Light.h"
#include "Timer.h"
#include "SkyboxMaterial.h"

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string FONT_PATH = "/fonts";
const std::string MODEL_PATH = "/models/";

//Global variables go here 
//Pointer to our SDL Windows
SDL_Window * window;
//SDL GL Context
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
bool running = true;

vector<GameObject*> displayList;
GameObject *mainCamera;

vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
GameObject * mainLight;

GameObject * skyBox = NULL;

Timer * timer; //pointer to Timer object - RT

//boolean for triggering debug camera - RT
bool debug = false;

void CheckForErrors()
{
	GLenum error;
	do{
		error = glGetError();
	} while (error != GL_NO_ERROR);
}

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window 
	window = SDL_CreateWindow("GP2 Coursework - The Average Joes",		//window title
		SDL_WINDOWPOS_CENTERED,		//x position, centered
		SDL_WINDOWPOS_CENTERED,		//y position, centered
		width,				//width, in pixels
		height,				//height, in pixels
		SDL_WINDOW_OPENGL		//flags
		);
}

//Used to cleanup once we exit
void CleanUp()
{
	if (skyBox)
	{
		skyBox->destroy();
		delete skyBox;
		skyBox = NULL;
	}

	auto iter = displayList.begin();
	while (iter != displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete(*iter);
			(*iter) = NULL;
			iter = displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	displayList.clear();

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something went wrong in creating the context, if it is still NULL
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to use
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;

	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

//Method for creating skybox - RT
void createSkyBox()
{
	Vertex triangleData[] = {
			{ vec3(-10.0f, 10.0f, 10.0f) },// Top Left
			{ vec3(-10.0f, -10.0f, 10.0f) },// Bottom Left
			{ vec3(10.0f, -10.0f, 10.0f) }, //Bottom Right
			{ vec3(10.0f, 10.0f, 10.0f) },// Top Right


			//back
			{ vec3(-10.0f, 10.0f, -10.0f) },// Top Left
			{ vec3(-10.0f, -10.0f, -10.0f) },// Bottom Left
			{ vec3(10.0, -10.0f, -10.0f) }, //Bottom Right
			{ vec3(10.0f, 10.0f, -10.0f) }// Top Right
	};


	GLuint indices[] = { 
		0, 2, 1,
		0, 3, 2,

		1, 2, 6,
		6, 5, 1,

		4, 5, 6,
		6, 7, 4,

		2, 3, 6,
		6, 3, 7,

		0, 7, 3,
		0, 4, 7,

		0, 1, 5,
		0, 5, 4
	};

	Mesh * pMesh = new Mesh();
	pMesh->init();

	pMesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	pMesh->copyIndexData(36, sizeof(int), (void**)indices);

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 0.0f);
	SkyBoxMaterial *material = new SkyBoxMaterial();
	material->init();

	string vsPath = ASSET_PATH + SHADER_PATH + "/skyVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/skyFS.glsl";
	material->loadShader(vsPath, fsPath);

	string posZTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysFront2048.png";
	string negZTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysBack2048.png";
	string posXTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysLeft2048.png";
	string negXTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysRight2048.png";
	string posYTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysUp2048.png";
	string negYTexturename = ASSET_PATH + TEXTURE_PATH + "/CloudyLightRaysDown2048.png";

	material->loadCubeTexture(posZTexturename, negZTexturename, posXTexturename, negXTexturename, posYTexturename, negYTexturename);

	skyBox = new GameObject();
	skyBox->setMaterial(material);
	skyBox->setTransform(t);
	skyBox->setMesh(pMesh);

	CheckForErrors();

}


void renderGameObject(GameObject *pObject)
{
	if (!pObject)
	{
		return;
	}

	pObject->render();
	Mesh * currentMesh = pObject->getMesh();
	Transform * currentTransform = pObject->getTransform();
	Material * currentMaterial = (Material*)pObject->getMaterial();
	
	if (currentMesh && currentMaterial && currentTransform)
	{
		currentMesh->Bind();
		currentMaterial->Bind();

		GLint MVPLocation = currentMaterial->getUniformLocation("MVP");
		GLint ambientMatLocation = currentMaterial->getUniformLocation("ambientMaterialColour");
		GLint ambientLightLocation = currentMaterial->getUniformLocation("ambientLightColour");
		GLint ModelLocation = currentMaterial->getUniformLocation("Model");
		GLint diffuseMatLocation = currentMaterial->getUniformLocation("diffuseMaterialColour");
		GLint diffuseLightLocation = currentMaterial->getUniformLocation("diffuseLightColour");
		GLint lightDirLocation = currentMaterial->getUniformLocation("lightDirection");
		GLint cameraPosLocation = currentMaterial->getUniformLocation("cameraPosition");
		GLint specularMatLocation = currentMaterial->getUniformLocation("specularMaterialColour");
		GLint specularPowerLocation = currentMaterial->getUniformLocation("specularPower");
		GLint specularLightLocation = currentMaterial->getUniformLocation("specularLightColour");
		GLint diffuseTextureLocation = currentMaterial->getUniformLocation("diffuseMap");
		GLint specularTextureLocation = currentMaterial->getUniformLocation("specMap");
		GLint bumpTextureLocation = currentMaterial->getUniformLocation("bumpMap");

		Camera *cam = mainCamera->getCamera();
		Light * light = mainLight->getLight();
		
		mat4 MVP = cam->getProjectMatrix()*cam->getViewMatrix()*currentTransform->getModel();
		vec4 ambientMaterialColour = currentMaterial->getAmbientColour();
		mat4 Model = currentTransform->getModel();
		vec4 diffuseMaterialColour = currentMaterial->getDiffuseColour();
		vec4 diffuseLightColour = light->getDiffuseColour();
		vec3 lightDirection = light->getLightDirection();
		vec4 specularLightColour = light->getSpecularColour();
		vec4 specularMaterialColour = currentMaterial->getSpecularColour();
		float specularPower = currentMaterial->getSpecularPower();
		vec3 cameraPosition = mainCamera->getTransform()->getPosition();
	
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform4fv(ambientMatLocation, 1, glm::value_ptr(ambientMaterialColour));
		glUniform4fv(ambientLightLocation, 1, glm::value_ptr(ambientLightColour));
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));
		glUniform4fv(diffuseMatLocation, 1, glm::value_ptr(diffuseMaterialColour));
		glUniform4fv(diffuseLightLocation, 1, glm::value_ptr(diffuseLightColour));
		glUniform3fv(lightDirLocation, 1, glm::value_ptr(lightDirection));
		
		glUniform4fv(specularMatLocation, 1, glm::value_ptr(specularMaterialColour));
		glUniform4fv(specularLightLocation, 1, glm::value_ptr(specularLightColour));
		glUniform3fv(cameraPosLocation, 1, glm::value_ptr(cameraPosition));
		glUniform1f(specularPowerLocation, specularPower);

		glUniform1i(diffuseTextureLocation, 0);
		glUniform1i(specularTextureLocation, 1);
		glUniform1i(bumpTextureLocation, 2);
		
		glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
	}
	
	for (int i = 0; i < pObject->getChildCount(); i++)
	{
		renderGameObject(pObject->getChild(i));
	}
}

//renders skybox - slimmed down version of renderGameObject - RT
void renderSkyBox()
{
	skyBox->render();

	Mesh * currentMesh = skyBox->getMesh();
	SkyBoxMaterial * currentMaterial = (SkyBoxMaterial*)skyBox->getMaterial();
	if (currentMesh && currentMaterial)
	{
		Camera * cam = mainCamera->getCamera();

		currentMaterial->bind();
		currentMesh->Bind();

		GLint cameraLocation = currentMaterial->getUniformLocation("cameraPos");
		GLint viewLocation = currentMaterial->getUniformLocation("view");
		GLint projectionLocation = currentMaterial->getUniformLocation("projection");
		GLint cubeTextureLocation = currentMaterial->getUniformLocation("cubeTexture");

		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam->getProjectMatrix()));

		mat4 rotationY = glm::rotate(mat4(1.0f), mainCamera->getTransform()->getRotation().y, vec3(0.0f, 1.0f, 0.0f));
		mat4 rotationX = glm::rotate(mat4(1.0f), mainCamera->getTransform()->getRotation().x, vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(rotationY*rotationX));
		glUniform4fv(cameraLocation, 1, glm::value_ptr(mainCamera->getTransform()->getPosition()));
		glUniform1i(cubeTextureLocation, 0);

		glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);

		currentMaterial->unbind();
	}

	CheckForErrors();

}

//Function to draw
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSkyBox();

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		renderGameObject((*iter));
	}
	SDL_GL_SwapWindow(window);
}

//Function to update game state
void update()
{
	skyBox->update();

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->update();
	}

	timer->update();
}

void initialise()
{
	createSkyBox();

	mainCamera = new GameObject();
	mainCamera->setName("Camera");
	
	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 10.0f);
	mainCamera->setTransform(t);
	
	Camera * c = new Camera();
	c->setFOV(45.0f);
	c->setAspectRatio((float)WINDOW_WIDTH / WINDOW_HEIGHT);
	c->setNearClip(0.1f);
	c->setFarClip(100.0f);
	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);

	mainLight = new GameObject();
	mainLight->setName(std::string("MainLight"));
	
	Transform * trans = new Transform();
	trans->setPosition(0.0f, 0.0f, 0.0f);
	mainLight->setTransform(trans);
	
	Light * light = new Light();
	mainLight->setLight(light);
	displayList.push_back(mainLight);
	
	
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();
	}

	//Changed Model loading variable for ArmoredRecon - IS
	std::string armoredReconModel = ASSET_PATH + MODEL_PATH + "armoredrecon.fbx";
	GameObject * go = loadFBXFromFile(armoredReconModel);
	for (int i = 0; i < go->getChildCount(); i++)
	{
		Material * material = new Material();
		material->init();
		std::string vsPath = ASSET_PATH + SHADER_PATH + "/bumpMappingVS.glsl";
		std::string fsPath = ASSET_PATH + SHADER_PATH + "/bumpMappingFS.glsl";
		material->loadShader(vsPath, fsPath);

		std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + "/armoredrecon_diff.png";
		material->loadDiffuseMap(diffTexturePath);

		std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + "/armoredrecon_spec.png";
		material->loadSpecularMap(specTexturePath);

		std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + "/armoredrecon_N.png";
		material->loadBumpMap(bumpTexturePath);

		go->getChild(i)->setMaterial(material);
	}
	
	go->getTransform()->setPosition(3.0f, -2.0f, -6.0f);
	displayList.push_back(go);

	////Loading of additional model (tank1) with textures - IS
	//std::string tank1Model = ASSET_PATH + MODEL_PATH + "Tank1.fbx";
	//go = loadFBXFromFile(tank1Model);
	//for (int i = 0; i < go->getChildCount(); i++)
	//{
	//	Material * material = new Material();
	//	material->init();
	//	std::string vsPath = ASSET_PATH + SHADER_PATH + "/bumpMappingVS.glsl";
	//	std::string fsPath = ASSET_PATH + SHADER_PATH + "/bumpMappingFS.glsl";
	//	material->loadShader(vsPath, fsPath);

	//	std::string diffTexturePath = ASSET_PATH + TEXTURE_PATH + "/Tank1DF.png";
	//	material->loadDiffuseMap(diffTexturePath);

	//	std::string specTexturePath = ASSET_PATH + TEXTURE_PATH + "/Tank1_S.png";
	//	material->loadSpecularMap(specTexturePath);

	//	std::string bumpTexturePath = ASSET_PATH + TEXTURE_PATH + "/Tank1_N.png";
	//	material->loadBumpMap(bumpTexturePath);

	//	go->getChild(i)->setMaterial(material);
	//}

	//go->getTransform()->setPosition(-3.0f, -2.0f, -6.0f);
	//go->getTransform()->setRotation(0.0f, 90.0f, 0.0f);
	//displayList.push_back(go);

	timer = new Timer(); //creates Timer object - RT

	timer->start(); //calls start function - RT
}

//Main Method - Entry Point
int main(int argc, char * arg[])
{
	// init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "ERROR TFF_Init: " << TTF_GetError();
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	initialise();

	//sets mouse cursor to centre of window - RT
	SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls the game loop to false
				running = false;
			}
			//checks for mouse motion - RT
			else if (event.type == SDL_MOUSEMOTION)
			{

				float deadzone = 3.5f;

				float magnitude = sqrt((float)event.motion.x * (float)event.motion.x + (float)event.motion.y * (float)event.motion.y);

				cout << magnitude << endl;

				if (magnitude > deadzone || (magnitude < -deadzone))
				{

					float cameraMoveLookX = ((float)event.motion.x - (WINDOW_WIDTH / 2)) * timer->getDeltaTime();
					float cameraMoveLookY = ((float)event.motion.y - (WINDOW_HEIGHT / 2)) * timer->getDeltaTime();

					vec3 camLookAt = mainCamera->getCamera()->getLookAt();

					mainCamera->getCamera()->setLookAt(camLookAt.x + cameraMoveLookX, camLookAt.y - cameraMoveLookY, camLookAt.z);

				}
				else
				{
					magnitude = 0.0f;
				}

				timer->stop(); //stops timer - RT
				timer->reset(); //resets timer - RT
				timer->start(); //restarts timer - RT
			}	
			//check for key held down by user - RT
			else if (event.type == SDL_KEYDOWN)
			{
				//checks to see which key was held down - RT
				switch (event.key.keysym.sym)
				{
				//if a key pressed - RT
				case SDLK_a:
				{
					
					vec3 camPosition = mainCamera->getTransform()->getPosition();
					camPosition.x -= 0.1f;
					cout << camPosition.x << endl; //for debugging purposes only - RT
					Transform *t = new Transform();
					t->setPosition(camPosition.x, camPosition.y, camPosition.z);
					mainCamera->setTransform(t);
					skyBox->setTransform(t);
						
					break;
				}
				//if d key pressed - RT
				case SDLK_d:
				{
					
					vec3 camPosition = mainCamera->getTransform()->getPosition();
					camPosition.x += 0.1f;
					cout << camPosition.x << endl; //for debugging purposes only - RT
					Transform *t = new Transform();
					t->setPosition(camPosition.x, camPosition.y, camPosition.z);
					mainCamera->setTransform(t);
					skyBox->setTransform(t);
						
					break;
				}
				//if w key pressed - RT
				case SDLK_w:
				{
					//only available to debug camera: player shouldn't be able to
					//"fly" - should be constrained to ground - RT
					if (debug == true)
					{
						vec3 camPosition = mainCamera->getTransform()->getPosition();
						camPosition.y += 0.1f;
						cout << camPosition.y << endl; //for debugging purposes only - RT
						Transform *t = new Transform();
						t->setPosition(camPosition.x, camPosition.y, camPosition.z);
						mainCamera->setTransform(t);
						skyBox->setTransform(t);
						
					}
					else
					{
						vec3 camPosition = mainCamera->getTransform()->getPosition();
						camPosition.z += 0.1f;
						cout << camPosition.z << endl; //for debugging purposes only - RT
						Transform *t = new Transform();
						t->setPosition(camPosition.x, camPosition.y, camPosition.z);
						mainCamera->setTransform(t);
						skyBox->setTransform(t);
					}
					break;
				}
				//if s key pressed - RT
				case SDLK_s:
				{
					//only available to debug camera: player shouldn't be able to 
					//"fly" and/or "go through" ground - RT
					if (debug == true)
					{
						vec3 camPosition = mainCamera->getTransform()->getPosition();
						camPosition[1] -= 0.1f;
						cout << camPosition.x << endl; //for debugging purposes only - RT
						Transform *t = new Transform();
						t->setPosition(camPosition.x, camPosition.y, camPosition.z);
						mainCamera->setTransform(t);
						skyBox->setTransform(t);
						
					}
					else
					{
						vec3 camPosition = mainCamera->getTransform()->getPosition();
						camPosition.z -= 0.1f;
						cout << camPosition.z << endl; //for debugging purposes only - RT
						Transform *t = new Transform();
						t->setPosition(camPosition.x, camPosition.y, camPosition.z);
						mainCamera->setTransform(t);
						skyBox->setTransform(t);

					}
					break;
				}
				//if r key is pressed
				case SDLK_r:
				{
					cout << "Debug mode altered" << endl; //for debugging purposes only - RT
					debug = !debug;
					break;
				}
				//if p key is pressed
				case SDLK_p:
				{
					cout << "Camera reset triggered" << endl; //for debugging purposes only - RT
					timer->reset();
					timer->start();
					mainCamera->getCamera()->reset(); //resets lookAt value in camera - RT
					
					Transform *t = new Transform();
					t = mainCamera->getTransform();
					skyBox->setTransform(t);

				}
				default:
					break;
				}
			}
		}

		update();
		render();
	}

	CleanUp();
	return 0;
}