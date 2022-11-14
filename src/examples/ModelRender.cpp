#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


//#include <stb_image.h>

#include <assimp/iostream.hpp>
//using namespace std;


struct Texture {
	unsigned int id;
	string type;
	string path;
};

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texCoord;
};

//vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
//{
//	vector<Texture> textures;
//	for (int i = 0; i < mat->GetTextureCount(type); i++)
//	{
//		aiString str;
//		mat->GetTexture(type, i, &str);
//		Texture texture;
//		texture.id = TextureFromFile(str.C_Str(), Data->meshManager.directory);
//		texture.type = typeName;
//		texture.path = str;
//		//textures.push_back(texture);
//	}
//	return textures;
//}

Mesh processMesh(aiMesh* mesh, const aiScene* scene)
{

	uint32 vertexSize = sizeof(vec3) * sizeof(vec3) + sizeof(vec2);

	Mesh meshVal = {};
	Mesh mesh2;

	meshVal.vertCount = mesh->mNumVertices;
	meshVal.size = vertexSize * meshVal.vertCount;
	meshVal.data = malloc(meshVal.size);

	meshVal.verts = (vec3*)(meshVal.data);
	meshVal.normals = (vec3*)((uint8*)meshVal.data + sizeof(vec3) * meshVal.vertCount);
	meshVal.texcoords = (vec2*)((uint8*)meshVal.data + (sizeof(vec3) + sizeof(vec3)) * meshVal.vertCount);

	int32 numOfIndex = 0;

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			numOfIndex++;
		}
	}

	meshVal.indexCount = numOfIndex;
	meshVal.indices = (uint32*)malloc(sizeof(uint32) * meshVal.indexCount);

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		meshVal.verts[i].x = mesh->mVertices[i].x;
		meshVal.verts[i].y = mesh->mVertices[i].y;
		meshVal.verts[i].z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			meshVal.normals[i].x = mesh->mNormals[i].x;
			meshVal.normals[i].y = mesh->mNormals[i].y;
			meshVal.normals[i].z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			meshVal.texcoords[i].x = mesh->mTextureCoords[0][i].x;
			meshVal.texcoords[i].y = mesh->mTextureCoords[0][i].y;
		}

	}

	int32 loopCounter = 0;
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for ( int j = 0; j < face.mNumIndices; j++)
		{
			meshVal.indices[loopCounter] = face.mIndices[j];
			loopCounter++;
		}		
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		//vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return meshVal;
}

void processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Data->meshManager.meshes[Data->meshManager.meshCount] = processMesh(mesh, scene);
		//PushBack(&Data->meshes, processMesh(mesh, scene));
		Data->meshManager.meshCount++;
		//meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}


void LoadModel()
{

	char* path[] =
	{
	   "data/map.osm",
	   "data/building1.obj",
	   "data/levelEditor/level1.txt",
	   "data/levelEditor/level2.txt",
	   "data/levelEditor/level3.txt",
	   "data/levelEditor/level4.txt",
	   "data/levelEditor/level5.txt",
	   "data/levelEditor/level6.txt",
	   "data/levelEditor/level7.txt"
	};


	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path[1], aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	//Data->meshManager.directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}




void DrawMeshes()
{

}



void DrawModel()
{


	vec4 color3 = V4(0.3f, 0.5f, 0.0f, 1.0f);

	for (int i = 0; i < Data->meshManager.meshCount; i++)
	{
		DrawMesh(&Data->meshManager.meshes[i], V3(0), IdentityQuaternion(), V3(1, 1, 1), color3);
	}
}

enum TextureType
{

};


//struct Vertex
//{
//	vec3 position;
//	vec3 normal;
//	vec2 texCoord;
//};
//
//struct Texture {
//	unsigned int id;
//	TextureType type;
//};
//

//void setupMesh()
//{
//
//    unsigned int VAO, VBO, EBO;
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
//        &indices[0], GL_STATIC_DRAW);
//
//    // vertex positions
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//    // vertex normals
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
//    // vertex texture coords
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
//
//    glBindVertexArray(0);
//}