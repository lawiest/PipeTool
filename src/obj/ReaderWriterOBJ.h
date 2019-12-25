
#ifndef READER_WRITER_OBJ
#define READER_WRITER_OBJ

#if defined(_MSC_VER)
    #pragma warning( disable : 4786 )
#endif

#include <stdlib.h>
#include <limits>
#include <string>

#include <osg/Notify>
#include <osg/Node>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Vec3f>

#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TexGen>
#include <osg/TexMat>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>

#include <osgUtil/MeshOptimizers>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Tessellator>

#include "obj.h"
#include "OBJWriterNodeVisitor.h"

#include <map>
#include <set>

#include <utility.h>

class ReaderWriterOBJ : public osgDB::ReaderWriter
{
public:
    ReaderWriterOBJ()
    {
        supportsExtension("obj","Alias Wavefront OBJ format");
        supportsOption("noRotation","Do not do the default rotate about X axis");
        supportsOption("noTesselateLargePolygons","Do not do the default tesselation of large polygons");
        supportsOption("noTriStripPolygons","Do not do the default tri stripping of polygons");
        supportsOption("generateFacetNormals","generate facet normals for vertices without normals");
        supportsOption("noReverseFaces","avoid to reverse faces when normals and triangles orientation are reversed");

        supportsOption("DIFFUSE=<unit>", "Set texture unit for diffuse texture");
        supportsOption("AMBIENT=<unit>", "Set texture unit for ambient texture");
        supportsOption("SPECULAR=<unit>", "Set texture unit for specular texture");
        supportsOption("SPECULAR_EXPONENT=<unit>", "Set texture unit for specular exponent texture");
        supportsOption("OPACITY=<unit>", "Set texture unit for opacity/dissolve texture");
        supportsOption("BUMP=<unit>", "Set texture unit for bumpmap texture");
        supportsOption("DISPLACEMENT=<unit>", "Set texture unit for displacement texture");
        supportsOption("REFLECTION=<unit>", "Set texture unit for reflection texture");

        supportsOption("precision=<digits>","Set the floating point precision when writing out files");
    }

    virtual const char* className() const { return "Wavefront OBJ Reader"; }

    virtual ReadResult readNode(const std::string& fileName, const osgDB::ReaderWriter::Options* options) const;

    virtual ReadResult readNode(std::istream& fin, const Options* options) const;

    virtual WriteResult writeObject(const osg::Object& obj,const std::string& fileName,const Options* options=NULL) //const
    {
        const osg::Node* node = dynamic_cast<const osg::Node*>(&obj);
        if (node)
            return writeNode(*node, fileName, options);
        else
            return WriteResult(WriteResult::FILE_NOT_HANDLED);
    }

    virtual WriteResult writeNode(const osg::Node& node,const std::string& fileName,const Options* options=NULL)// const
    {
		std::string strName = node.getName();
		unsigned long long hash = UTILITY_NAME::GsHash::Hash64(strName.c_str());

        if (!acceptsExtension(osgDB::getFileExtension(fileName)))
            return WriteResult(WriteResult::FILE_NOT_HANDLED);

        ObjOptionsStruct localOptions = parseOptions(options);

        osgDB::ofstream f(fileName.c_str());
        f.precision(localOptions.precision);

        //std::string materialFile = osgDB::getNameLessExtension(fileName) + ".mtl";
		std::string materialFile = osgDB::getFilePath(fileName) + "/" + std::to_string(hash) + ".mtl";
		std::vector<unsigned long long >::const_iterator it = std::find(vecHash.begin(), vecHash.end(), hash);

		bool isMatSame = false;
		if (it != vecHash.end())
			isMatSame = true;

		OBJWriterNodeVisitor nv(f, osgDB::getSimpleFileName(materialFile), isMatSame);

		// we must cast away constness
		(const_cast<osg::Node*>(&node))->accept(nv);
		vecHash.push_back(hash); 
			
		osgDB::ofstream mf(materialFile.c_str());
		nv.writeMaterials(mf);

        return WriteResult(WriteResult::FILE_SAVED);
    }

    virtual WriteResult writeObject(const osg::Object& obj,std::ostream& fout,const Options* options=NULL) const
    {
        const osg::Node* node = dynamic_cast<const osg::Node*>(&obj);
        if (node)
            return writeNode(*node, fout, options);
        else
            return WriteResult(WriteResult::FILE_NOT_HANDLED);
    }

    virtual WriteResult writeNode(const osg::Node& node,std::ostream& fout,const Options* options=NULL) const
    {
        ObjOptionsStruct localOptions = parseOptions(options);
        fout.precision(localOptions.precision);

        // writing to a stream does not support materials

        OBJWriterNodeVisitor nv(fout);

        // we must cast away constness
        (const_cast<osg::Node*>(&node))->accept(nv);

        return WriteResult(WriteResult::FILE_SAVED);
    }

protected:

     class ObjOptionsStruct {
     public:
        bool rotate;
        bool noTesselateLargePolygons;
        bool noTriStripPolygons;
        bool generateFacetNormals;
        bool fixBlackMaterials;
        bool noReverseFaces;
        // This is the order in which the materials will be assigned to texture maps, unless
        // otherwise overridden
        typedef std::vector< std::pair<int,obj::Material::Map::TextureMapType> > TextureAllocationMap;
        TextureAllocationMap textureUnitAllocation;
        /// Coordinates precision.
        int precision;

        ObjOptionsStruct()
        {
            rotate = true;
            noTesselateLargePolygons = false;
            noTriStripPolygons = false;
            generateFacetNormals = false;
            fixBlackMaterials = true;
            noReverseFaces = false;
            precision = std::numeric_limits<double>::digits10 + 2;
        }
    };

    typedef std::map< std::string, osg::ref_ptr<osg::StateSet> > MaterialToStateSetMap;
	std::vector<unsigned long long> vecHash;

    void buildMaterialToStateSetMap(obj::Model& model, MaterialToStateSetMap& materialToSetSetMapObj, ObjOptionsStruct& localOptions, const Options* options) const;

    osg::Geometry* convertElementListToGeometry(obj::Model& model, obj::Model::ElementList& elementList, ObjOptionsStruct& localOptions) const;

    osg::Node* convertModelToSceneGraph(obj::Model& model, ObjOptionsStruct& localOptions, const Options* options) const;

    inline osg::Vec3 transformVertex(const osg::Vec3& vec, const bool rotate) const ;
    inline osg::Vec3 transformNormal(const osg::Vec3& vec, const bool rotate) const ;

    ObjOptionsStruct parseOptions(const Options* options) const;

};

#endif