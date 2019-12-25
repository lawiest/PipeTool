#pragma once
#include "../utility/preconfig.h" 
#include "geodatabase.h"
#include <map.h>
#include "image.h"
#include "utility.h"
#include "../geomathse/GeomathSE.h"

KERNEL_NS

/// \brief 基于文件缓存的矢量瓦片切片
class GS_API GsFileVectorTileSpliter:public Utility::GsRefObject
{  
	struct LayerStruct:public UTILITY_NAME::GsVector<Utility::GsString>
	{
		int Index;
		Utility::GsString Name;
		LayerStruct()
		{
			Index = 0;
		}
		LayerStruct(int index,const char* name) : Name(name)
		{
			Index = index;
		}
	};
	/// \brief 金字塔对象
	GsPyramidPtr		m_ptrPyramid;
	/// \brief 切片级别范围
	int m_MinLevel,m_MaxLevel;
	/// \brief 总碎片数
	long long m_nTotalPieces;
	/// \brief 几何简化容差
	double m_SimplfyTol;
	/// \brief 瓦片数据集对象
	GsTileClassPtr				m_ptrTileClass;
	/// \brief 坐标转换对象
	GsCoordinateTransformationPtr m_ptrTans;
	/// \brief 切片过滤范围
	geostar::gobjptr			m_FilterExtent;
	/// \brief 切片过滤范围所在瓦片外接矩形
	geostar::gobjptr		    m_FilterGeoTilesExtent;
	/// \brief 因为会外扩所以写入缓存的瓦片会过多，使用层行列过滤掉部分瓦片
	Utility::GsStlMap<int, GeoStar::Utility::GsRect> m_mapLevelRect;
	/// \brief 是否裁切
	bool m_bKnifeClip;
	/// \brief 裁切的trans
	geostar::gobjptr	m_TranKnife;
	/// \brief 瓦片属性缓存
	Utility::GsGrowByteBuffer m_AttributeBuffer;
	/// \brief 瓦片图层索引缓存
	Utility::GsStlMap<Utility::GsString,LayerStruct> m_LayerIndex;
	/// \brief 切片对象缓存
	Utility::GsStlMap<int,geostar::gobjptr> m_ClipCache;
	/// \brief 临时切片文件io对象
	geostar::geo_reader* m_TempRead;
	geostar::geo_writer* m_TempWriter;
	/// \brief 切片临时文件存储路径
	Utility::GsString m_strCacheFile;

	/// \brief 创建临时切片文件io对象
	void CreateReader();
	/// \brief 获取图层的索引
	/// \param layerName 
	/// \param pFea 
	/// \param pAttIndex 
	/// \param nAttCount 
	/// \return 
	int LayerIndex(const char* layerName,GsFeature* pFea,int* pAttIndex,int nAttCount);
	/// \brief 根据level创建一个clip
	/// \param nLevel 
	/// \return 
	geostar::geo_trans* CreateClip(int nLevel);
	/// \brief 写一个碎片到临时文件
	/// \param o 
	void Write(geostar::geo_object* o);
	/// \brief 预先切割,返回切割后gobj对象数据，防止一次性切割内存占用过大
	/// \param ptrGeo 
	/// \param level 
	/// \return 
	geostar::gobjptr PreTrans(geostar::gobjptr ptrGeo,int level);
	/// \brief 计算预切割层级 返回当前层级表示不需要预切割
	/// \param ptrGeo 
	/// \param ptrPyramid 
	/// \param level 
	/// \return 
	int NeedPareClipLevel(geostar::gobjptr ptrGeo,GsPyramid *ptrPyramid,int level);
	bool m_FilterInvalidPixel;
	Utility::GsStlMap<unsigned long long, int> m_IndexMap;
public:
	/// \brief 
	/// \param pTileClass 
	/// \param pPyramid 
	/// \param nMin 
	/// \param nMax 
	/// \param dblSimplfyTol 
	GsFileVectorTileSpliter(GsTileClass* pTileClass,GsPyramid* pPyramid,int nMin,int nMax,double dblSimplfyTol = 0);
	virtual ~GsFileVectorTileSpliter();
	
	/// \brief 设置过滤范围,过滤范围外的数据不会进入瓦片
	/// \param box 
	void FilterExtent(const GsBox& box);
	/// \brief 设置过滤范围，过滤范围外的数据不会进入瓦片
	/// \param pGeo 
	void FilterExtent(GsGeometry* pGeo);

	/// \brief 坐标转换对象
	/// \param ptrTransObj 
	void CoordinateTransformation(GsCoordinateTransformation* ptrTransObj);
	/// \brief 坐标转换对象 
	/// \return 
	GsCoordinateTransformation* CoordinateTransformation();
	/// \brief 设置获取最小的切片级别
	/// \return 
	int& MinLevel();
	/// \brief 设置获取最大的切片级别
	/// \return 
	int& MaxLevel();
	/// \brief 添加一个Feature进行瓦片切割。
	/// \param pFea 
	/// \param pAttIndex 
	/// \param nAttCount 
	/// \param lyrName 
	/// \return 
	bool Add(GsFeature* pFea,int* pAttIndex,int nAttCount,const char* lyrName =  NULL);
	/// \brief 提交数据。
	virtual void Commit(); 

	/// \brief 设置是否对生产的瓦片使用GZ压缩
	/// \param bEnable 
	void GZipCompress(bool bEnable);
	/// \brief 获取是否对生产的瓦片使用GZ压缩
	/// \return 
	bool GZipCompress();

	/// \brief 设置切片临时文件存储路径
	/// \param strPath 
	void CachePath(const char* strPath);

	/// \brief 设置是否只生产过滤范围内的数据
	/// \param bClip 
	void Clip(bool bClip);
	/// \brief 获取是否只生产过滤范围内的数据
	/// \return 
	bool Clip();
	/// \brief 
	/// \param b 
	void FilterInvalidPixel(bool b);
	/// \brief 
	/// \return 
	bool FilterInvalidPixel();
	/// \brief 
	void ClearInvalidPixel();
public:
	/// \brief 当提交数据时显示进度。
	/// \details 参数1 
	/// \details 参数2 
	Utility::GsDelegate<void(long long,long long)> OnCommit;
};

/// \brief GsFileVectorTileSpliterPtr
GS_SMARTER_PTR(GsFileVectorTileSpliter);

/// \brief 栅格瓦片切片
class GS_API GsRasterTileSpliter
{
	long long m_nNow;
	long long m_nTotal;
	int m_nTileSize;
	int m_nPixelByteSize;
	int m_nCommit, m_nMaxCommit;
	Utility::GsSharedPtr<GsColorToRGBA> m_ptrTrans;
	double m_dblNodata;//设置nodata的值
	bool m_bUseNodata;//设置nodata是否生效
	bool m_IsClip;
private:
	/// \brief 
	/// \param level 
	/// \param buff 
	/// \param img 
	/// \param box 
	/// \return 
	bool Spliter(int level, Utility::GsGrowByteBuffer* buff, Utility::GsImage* img, const GsBox& box);
	/// \brief 
	/// \param level 
	/// \param row 
	/// \param col 
	/// \param width 
	/// \param height 
	/// \param buff 
	/// \return 
	bool Spliter(int level,int row,int col,int width,int height, Utility::GsGrowByteBuffer* buff);
private:

	GsGeometryPtr m_ptrFilterExtent;
	GsRasterClassPtr m_ptrRasterClass;
	GsTileClassPtr	 m_ptrTileClass;
	GsPyramidPtr	m_ptrPyramid; 
	/// \brief 内存缓存瓦片行数量
	int				m_MemCacheTileRows;
	/// \brief 内存缓存瓦片列数量
	int				m_MemCacheTileCols;
public:
	/// \brief 
	/// \param pRasterClass 
	/// \param pPyramid 
	/// \param pTileClass 
	GsRasterTileSpliter(GsRasterClass* pRasterClass, GsPyramid* pPyramid, 
		GsTileClass* pTileClass);
	/// \brief 最大提交数量，保存瓦片数量达到此数据量之后提交一次事务
	/// \return 
	int MaxCommit();
	/// \brief 最大提交数量，保存瓦片数量达到此数据量之后提交一次事务
	/// \param commit 
	void MaxCommit(int commit);


	/// \brief 内存缓存瓦片行数量
	/// \return 
	int MemoryCacheTileRows();
	/// \brief 内存缓存瓦片行数量
	/// \param r 
	void MemoryCacheTileRows(int r);

	/// \brief 内存缓存瓦片列数量
	/// \return 
	int MemoryCacheTileCols();
	/// \brief 内存缓存瓦片列数量
	/// \param c 
	void MemoryCacheTileCols(int c);

	/// \brief 是否按范围裁切
	/// \return 
	bool Clip();
	/// \brief 是否按范围裁切
	/// \param bClip 
	void Clip(bool bClip);

	/// \brief 设置过滤范围,过滤范围外的数据不会进入瓦片
	/// \param box 
	void FilterExtent(const GsBox& box);
	/// \brief 设置过滤范围，过滤范围外的数据不会进入瓦片
	/// \param pGeo 
	void FilterExtent(GsGeometry* pGeo);

	/// \brief 获取过滤范围 
	/// \return 
	GsGeometry* FilterExtent();
	 
	/// \brief 执行切割过程，其中需要保证nStartLevel <= nEndLevel
	/// \param nStartLevel 切割的起始级别
	/// \param nEndLevel 切割的结束级别
	/// \return 返回是否切割成功
	bool Execute(int nStartLevel, int nEndLevel);

	/// \brief 设置nodata的值，一般情况下可以认为小于nodata的像素值认为是无效的。
	/// \param nodata nodata的值
	void NoDataValue(double nodata);
	/// \brief 获取nodata的值
	/// \return nodata的值
	double NoDataValue();

	/// \brief 设置是否使用设置的nodata
	/// \param bUseNodata 是否使用nodata
	void UseNoData(bool bUseNodata);
	/// \brief 获取是否使用设置的nodata
	/// \return 是否使用nodata
	bool UseNoData();
public:
	/// \brief 当切割瓦片的时候发送的进度，返回false则标识中断
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	/// \details 参数4 
	/// \details 参数5 
	/// \details 返回值 
	Utility::GsDelegate<bool(int,int ,int,long long, long long)> OnProgress;
};

class GS_API GsMapTileSpliter
{
public:
	/// \brief 
	/// \param pMapDefinePath 
	/// \param pPyramid 
	/// \param pTileClass 
	GsMapTileSpliter(const char* pMapDefinePath, GsPyramid* pPyramid,GsTileClass* pTileClass);

	/// \brief 
	/// \param box 
	void FilterExtent(const GsBox& box);
	/// \brief 设置过滤范围，过滤范围外的数据不会进入瓦片
	/// \param pGeo 
	void FilterExtent(GsGeometry* pGeo);
	/// \brief 获取过滤范围 
	/// \return 
	GsGeometry* FilterExtent();
	/// \brief 设置透明色 背景色
	/// \param color 
	void TransparencyColor(const Utility::GsColor& color);
	/// \brief 透明色
	/// \return 
	Utility::GsColor TransparencyColor();

	/// \brief 是否裁切边框
	/// \return 
	bool ClipBoundary();
	/// \brief 设置是否裁切边框
	/// \param bClip 
	void ClipBoundary(bool bClip);

	/// \brief 设置大位图宽
	/// \param widthStep 
	void WidthStep(int widthStep);
	/// \brief 大位图宽
	/// \return 
	int WidthStep();

	/// \brief 设置大位图高
	/// \param heightStep 
	void HeightStep(int heightStep);
	/// \brief 大位图高
	/// \return 
	int HeightStep();

	/// \brief 瓦片编码类型
	/// \return 
	GsTileEncodingType EncodingType();
	/// \brief 设置瓦片编码类型
	/// \param tileEncodingType 
	void EncodingType(GsTileEncodingType tileEncodingType);

	/// \brief 绘制DPI
	/// \return 
	double DPI();
	/// \brief 设置绘制DPI
	/// \param dpi 
	void DPI(double dpi);

	/// \brief 最大使用缓存大小，仅使用文件类型时有效
	/// \return 
	int MemoryCacheMaxSize();
	/// \brief 设置最大使用缓存大小，仅使用文件类型时有效
	/// \param memoryCacheMaxSize 
	void MemoryCacheMaxSize(int memoryCacheMaxSize);
	/// \brief 文件缓存路径
	/// \return 
	Utility::GsString CacheFilePath();
	/// \brief 设置文件缓存路径
	/// \param fileName 
	void CacheFilePath(const char* fileName);
	/// \brief 执行切割过程
	/// \param nStartLevel 
	/// \param nEndLevel 
	/// \param trackCancel 
	/// \return 
	bool Execute(int nStartLevel, int nEndLevel, GsTrackCancel* trackCancel = nullptr);
	/// \brief 执行范围更新过程
	/// \param nStartLevel 
	/// \param nEndLevel 
	/// \param pGeo 
	/// \param trackCancel 
	/// \return 
	bool Update(int nStartLevel, int nEndLevel, GsGeometry* pGeo, GsTrackCancel* trackCancel = nullptr);
	/// \brief 进度信息回调函数
	/// \details 参数1 
	/// \details 参数2 
	/// \details 参数3 
	/// \details 参数4 
	/// \details 参数5 
	Utility::GsDelegate<bool(int, int, int, long long, long long)> OnProgress;
protected:
	/// \brief 文件大位图
	GsMemoryImageCanvasPtr m_Canvas;
	/// \brief 临时小位图，
	GsMemoryImageCanvasPtr m_smallCanvas;
	/// \brief 临时空瓦片，用于判断切出来的瓦片是否为空
	GsMemoryImageCanvasPtr m_EmptyCanvas;
	/// \brief 临时空瓦片，用于判断切出来的瓦片是否为空
	GsMemoryImageCanvasPtr m_EmptyBigCanvas;
	GsDisplayPtr m_ptrDisplay;
	GsTrackCancelPtr m_ptrTrack;
	GsDisplayTransformationPtr m_pDT;
	int m_nStartLevel;
	int m_nEndLevel;
	GsMapPtr m_pMap;
	GsPyramidPtr m_pPyramid;
	GsTileClassPtr m_pTileClass;
	GsBox m_tmpBox;
	GsGeometryPtr m_pGeo;
	Utility::GsColor m_Col;
	Utility::GsString m_sCachePath;
	int m_nMemoryCacheMaxSize;
	double m_dDPI;

	int m_nWidthStep;//
	int m_nHeightStep;//

	/// \brief 瓦片输出类型
	GsTileEncodingType m_TileEncodingType;
	/// \brief 颜色自适应
	bool m_bUseColorDepth;
	/// \brief 水印
	bool m_MarkWater;
	/// \brief 裁切瓦片
	bool m_Clip;
	GsGraphicsPathPtr m_CanvasClip;
	/// \brief 
	/// \param box 
	/// \param rect 
	/// \return 
	bool DrawBigCanvas(GsBox box, GeoStar::Utility::GsRect rect);
	/// \brief 
	/// \param nLevel 
	/// \param nMinRow 
	/// \param nMinCol 
	/// \param nMaxRow 
	/// \param nMaxCol 
	/// \return 
	long ClipHugeCanvas(int nLevel, int nMinRow, int nMinCol, int nMaxRow, int nMaxCol);
	
	/// \brief 
	/// \param nLevel 
	/// \param nMinRow 
	/// \param mMinCol 
	/// \param nMaxRow 
	/// \param nMaxCol 
	/// \return 
	bool InitLevelExent(int nLevel, int &nMinRow, int& mMinCol, int &nMaxRow, int &nMaxCol);
	/// \brief 
	/// \param box 
	/// \return 
	bool InitClip( const GsBox& box);

	/// \brief 
	/// \param l 
	/// \param r1 
	/// \param c1 
	/// \param r2 
	/// \param c2 
	/// \param box 
	void LRC2Box(int l, int r1, int c1, int r2, int c2,GsBox &box);
	int m_CurrentTileIndex;
	int m_TotalTileCount;
	/// \brief 
	/// \param rect 
	/// \return 
	bool InitCacheCanvas(const Utility::GsRect& rect);
	/// \brief 
	/// \param startLevel 
	/// \param endLevel 
	/// \param pGeo 
	void EstimateTotalTileCount(int startLevel,int endLevel,GsGeometry* pGeo);
	/// \brief 
	/// \param box 
	/// \return 
	bool IsNeedToDraw(const GsBox& box);
};

class GS_API GsTileSingleSpliter
{
	char m_tmp_path[512];//临时文件路径
	geostar::geo_writer* m_clip_fw;//写m_clip_fn的writer
	std::vector<GsFeatureClassPtr> m_fclsA;//参与切割的所有FeatureClass

	Utility::GsSet<std::string>	m_str_pool;//字符串的数据池
	FILE* m_prop_file;//属性的临时文件
	int* m_prop_data;//属性数据(内置1M空间)
	GsTileClass* m_pTileClass;//目标瓦片的数据源
	GsPyramid* m_pPyramid;	//金字塔
	int m_tile_count;		//已经OnClip的瓦片个数
	bool m_bGZip;
	int m_startUnion_level;	//开始缩并的层级
	double m_CompressionRatio;//压缩比例

	/// \brief 按范围裁切的范围
	GsGeometryPtr m_FilterExtent;

	/// \brief 瓦片切片的最小层级
	int m_MinLevel;
	/// \brief 瓦片切片的最大层级
	int m_MaxLevel;
	/// \brief 当一个瓦片中对象个数小于m_objn_min的时候，该瓦片不会细分
	int m_objn_min;
	
	GsTilePtr m_pGeoTile;

	
    struct GsClipBuff;
	struct GsClip;
	struct PropMap;
    
    friend struct GsClipBuff;
	friend struct GsClip;
	friend struct PropMap;

	/// \brief 
	/// \param str 
	/// \return 
	const char* str_ptr(const std::string& str);

	/// \brief 
	/// \param gcB 
	void AddTile(GsClipBuff& gcB);

	/// \brief 
	/// \param type 
	/// \param fea 
	/// \param i 
	/// \param prop 
	/// \return 
	bool dump_prop(Utility::Data::GsFieldType& type, GsFeature& fea, int i, int* prop);

	/// \brief 将Fea的属性写入m_file_prop
	/// \param Fea 
	/// \return 
	int write_prop(GsFeature* Fea);

	/// \brief 读取当前gse对象的属性(返回属性的首地址)
	/// \param gse 
	/// \return 
	int* read_prop(geostar::geo_object* gse);

	/// \brief 
	/// \return 
	geostar::geo_writer* get_writer();
	/// \brief 
	/// \param Fea 
	void _add_to_gse_file(GsFeature* Fea);

	/// \brief [pp,pp+n)是一个图层的所有数据，将其写入pLayer
	/// \param layer 
	/// \param n 
	/// \param pp 
	void TileLayer(GsMBLayer* layer, int n, geostar::geo_object** pp);

	/// \brief 将一个瓦片中的所有几何对象打包写入到m_dataBuf
	/// \param gseA 
	void ToDataBuf(std::vector<geostar::geo_object*>& gseA);

	/// \brief 将fcls的属性设置到layer
	/// \param fcls 
	/// \param layer 
	void CopyAtt(GsFeatureClass* fcls, GsMBLayer*  layer);

	/// \brief 
	/// \param level 
	/// \param fn 
	void make_fn(int level, char* fn);

public:

	/// \brief 
	/// \param bGZip 
	GsTileSingleSpliter(bool bGZip = true);
	~GsTileSingleSpliter();

	/// \brief 设置瓦片的最小及最大层级
	/// \param nMinLevel 
	/// \param nMaxLevel 
	void Level(int nMinLevel, int nMaxLevel);
	/// \brief 设置单个瓦片中最小对象个数
	/// \param nObjCount 
	void TileObjectCount(int nObjCount);
	/// \brief 设置瓦片金字塔类型
	/// \param pPyramid 
	void Pyramid(GsPyramid* pPyramid);
	/// \brief 设置瓦片对象
	/// \param pTileClass 
	void TileClass(GsTileClass* pTileClass);
	/// \brief 设置压缩
	/// \param bGZip 
	void Zip(bool bGZip);
	/// \brief 设置临时路径
	void TempPath(const char* strPath);	
	/// \brief 设置开始缩并的层级
	/// \param nLevel 
	void StartUnionLevel(int nLevel);
	/// \brief 设置过滤范围，过滤范围外的数据不会进入瓦片
	/// \param pGeo 
	void FilterExtent(GsGeometry* pGeo);
	/// \brief 设置压缩比例
	void CompressionRatio(double dCompressionRatio);
	/// \brief 
	/// \param pFcls 
	void AddToGseFile(GsFeatureClass* pFcls, GsSpatialQueryFilter * pQuery = NULL);
	/// \brief 
	/// \param fcs 
	void AddToGseFile(char* fcs);
	/// \brief 
	/// \param db 
	/// \param clsname 
	void AddToGseFile(GsGeoDatabase* db, const char* clsname);

	/// \brief 对临时文件进行top一致性处理
	/// \param nLevel 
	void Consistent(int nLevel);

	/// \brief tol_expand 外扩容查，单位为瓦片的大小
	/// \param level 
	/// \param tol_expand 
	void ClipCut(int level, double tol_expand);



	/// \brief 存储瓦片的回调, 在存储瓦片到数据库前的时候发生
	/// \param int nLevel,瓦片层级
	/// \param int nRow,瓦片行号
	/// \param 	int nCol,瓦片列好
	/// \param 	const char* pTileData, 瓦片数据
	/// \param 	int pTileDataLength , 瓦片数据长度
	/// \param 	GsTileEncodingType TileType 瓦片类型
	Utility::GsDelegate<void(int nLevel,int nRow,int nCol,const unsigned char* pTileData,int pTileDataLength , GsTileEncodingType TileType)> OnStoreTile;
};
KERNEL_ENDNS