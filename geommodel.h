#ifndef GEOMMODEL_H
#define GEOMMODEL_H

#include<QOpenGLFunctions>
#include<QOpenGLWidget>
enum { X, Y, Z, W };
#define GLM_NONE     (0)		    /* render with only vertices */
#define GLM_FLAT     (1 << 0)		/* render with facet normals */
#define GLM_SMOOTH   (1 << 1)		/* render with vertex normals */
#define GLM_TEXTURE  (1 << 2)		/* render with texture coords */
#define GLM_COLOR    (1 << 3)		/* render with colors */
#define GLM_MATERIAL (1 << 4)		/* render with materials */
typedef struct _GLMnode {
  GLuint           index;
  GLboolean        averaged;
  struct _GLMnode* next;
} GLMnode;

class GeomModelGroup
{
public:
    char*				name;		    /* name of this group */
    GLuint				numtriangles;	/* number of triangles in this group */
    GLuint*				triangles;		/* array of triangle indices */
    GLuint				material;       /* index to material for group */
    GeomModelGroup*		next;			/* pointer to next group in model */

};
typedef struct {
  GLuint vindices[3];			/* array of triangle vertex indices */
  GLuint nindices[3];			/* array of triangle normal indices */
  GLuint tindices[3];			/* array of triangle texcoord indices*/
  GLuint findex;			    /* index of triangle facet normal */
} GLMtriangle;

typedef struct _GLMmaterial
{
  char* name;				    /* name of material */
  GLfloat diffuse[4];			/* diffuse component */
  GLfloat ambient[4];			/* ambient component */
  GLfloat specular[4];			/* specular component */
  GLfloat emmissive[4];			/* emmissive component */
  GLfloat shininess;			/* specular exponent */
} GLMmaterial;


class GeomModel
{
public:
    GeomModel();
    GLvoid glmWeld(GLfloat epsilon);
    GLuint glmList(GLuint mode);
    GLvoid glmDraw(GLuint mode);
    GLvoid glmWriteOBJ(char* filename, GLuint mode);
    GeomModel* glmReadOBJ(char* filename);
    GLvoid glmDelete();
    GLvoid glmSpheremapTexture();
    GLvoid glmLinearTexture();
    GLvoid glmVertexNormals(GLfloat angle);
    GLvoid glmFacetNormals();
    GLvoid glmReverseWinding();
    GLvoid glmScale(GLfloat scale);
    GLvoid glmDimensions(GLfloat* dimensions);
    GLfloat glmUnitize();
    virtual ~GeomModel();
private:
    GLvoid _glmSecondPass(FILE* file);
    GLvoid _glmFirstPass(FILE* file);
    GLvoid _glmWriteMTL(char* modelpath, char* mtllibname);
    GLvoid _glmReadMTL(char* name);
    char* _glmDirName(char* path);
    GLuint _glmFindMaterial(char* name);
    GeomModelGroup* _glmAddGroup(char* name);
    GeomModelGroup* _glmFindGroup(char* name);
    GLfloat* _glmWeldVectors(GLfloat* vectors, GLuint* numvectors, GLfloat epsilon);
    static GLboolean _glmEqual(GLfloat* u, GLfloat* v, GLfloat epsilon);
    static GLvoid _glmNormalize(GLfloat* n);
    static GLvoid _glmCross(GLfloat* u, GLfloat* v, GLfloat* n);
    static GLfloat _glmDot(GLfloat* u, GLfloat* v);
    static GLfloat _glmAbs(GLfloat f);
    static GLfloat  _glmMax(GLfloat a, GLfloat b);
    char*    pathname;			/* path to this model */
    char*    mtllibname;			/* name of the material library */

    GLuint   numvertices;			/* number of vertices in model */
    GLfloat* vertices;			/* array of vertices  */

    GLuint   numnormals;			/* number of normals in model */
    GLfloat* normals;			    /* array of normals */

    GLuint   numtexcoords;		/* number of texcoords in model */
    GLfloat* texcoords;			/* array of texture coordinates */

    GLuint   numfacetnorms;		/* number of facetnorms in model */
    GLfloat* facetnorms;			/* array of facetnorms */

    GLuint       numtriangles;	/* number of triangles in model */
    GLMtriangle* triangles;		/* array of triangles */

    GLuint       nummaterials;	/* number of materials in model */
    GLMmaterial* materials;		/* array of materials */

    GLuint       numgroups;		/* number of groups in model */
    GeomModelGroup*    groups;			/* linked list of groups */

    GLfloat position[3];			/* position of the model */

};

#endif // GEOMMODEL_H
