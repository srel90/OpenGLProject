/************************************************************
*	APRON TUTORIAL PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
************************************************************/
#include "stdafx.h"
#include"3dsloader.h"



/////////////////////////////////////////////////////////////////////////////////////////////////
//										 INIT 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Init_3ds(char* filename,LPSTR path)
{
	mLoad3ds.Import3DS(&m3DModel, filename);						
	
	//for(int i = 0; i < m3DModel.numOfMaterials; i++)				
	//{
	//	if(strlen(m3DModel.pMaterials[i].strFile) > 0)				
	//	{

	//		Texture_3ds(TextureArray3ds, m3DModel.pMaterials[i].strFile, i,path);			
	//	}
	//	
	//	m3DModel.pMaterials[i].texureId = i;						
	//}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										RENDER 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Render_3ds()
{
	
	for(int i = 0; i < m3DModel.numOfObjects; i++)
	{
		
		if(m3DModel.pObject.size() <= 0) break;						
		
		t3DObject *pObject = &m3DModel.pObject[i];					
			
		/*if(pObject->bHasTexture)									
		{									
			glEnable(GL_TEXTURE_2D);								
			
			glColor3ub(255, 255, 255);								
			
			glBindTexture(GL_TEXTURE_2D, TextureArray3ds[pObject->materialID]); 
		} 
		else 
		{
			glDisable(GL_TEXTURE_2D);								
			
			glColor3ub(255, 255, 255);								
		}*/
		
											
		glBegin(GL_TRIANGLES);
		for(int j = 0; j < pObject->numOfFaces; j++)
		{
			
			for(int whichVertex = 0; whichVertex < 3; whichVertex++)
			{
				int index = pObject->pFaces[j].vertIndex[whichVertex];
				
				glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
				if(pObject->bHasTexture) {
					
					if(pObject->pTexVerts) {
						glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
					}
				} else {
					
					if(m3DModel.pMaterials.size() < pObject->materialID) 
					{
						BYTE *pColor = m3DModel.pMaterials[pObject->materialID].color;
						
						glColor3ub(pColor[0], pColor[1], pColor[2]);
					}
				}
				
				glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
			}
		}
		
		glEnd();
	}
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										TEXTURE 3DS			jpeg or bmp
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Texture_3ds(UINT textureArray[], LPSTR strFileName, int ID,LPSTR path)
{
	if(!strFileName) return;
	char FilePath[255];
	strcpy_s(FilePath,path);
	strcat_s(FilePath,strFileName);

	int imgWidth, imgHeight, imgChannels;
	unsigned char* ptr = SOIL_load_image(FilePath, &imgWidth, &imgHeight, &imgChannels, SOIL_LOAD_RGB);
	if(ptr)
	{
		
		glGenTextures(1, &textureArray[ID]);
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, ptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
		SOIL_free_image_data(ptr);

	}else{
		MessageBox(NULL, FilePath /*"couldn't find texture!"*/, "Error!", MB_OK);
			exit(0);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										UNLOAD 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::Unload_3ds()
{
	for(int i = 0; i < m3DModel.numOfObjects; i++)	
	{
		delete [] m3DModel.pObject[i].pFaces;
		delete [] m3DModel.pObject[i].pNormals;
		delete [] m3DModel.pObject[i].pVerts;
		delete [] m3DModel.pObject[i].pTexVerts;
	}
}












