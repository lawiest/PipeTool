#pragma once
#include <vector>
namespace geostar {
    struct geo_object;
    struct geo_reader;
    struct geo_writer;
    struct geo_trans;
    struct geo_factory;
    struct geo_algorithm;

    struct gsePath;
    struct gseReader;
    struct gseWriter;
    struct gseTrans;

    typedef long long id_type;
    typedef std::vector<gsePath> gsePathA;
    typedef std::vector<int> intA;
    typedef std::vector<char> charA;
    typedef std::vector<id_type> idA;
    typedef std::vector<double> doubleA;

    geo_factory& g_f();
    geo_algorithm& g_a();

    struct gsePath 
    {   
        geo_object* m_ptr;
    
        ~gsePath();

        //构造
        gsePath() :m_ptr(0) {} 
        gsePath(const gsePath& p);
        gsePath& operator=(const gsePath& p);
        gsePath(geo_object* g);
        gsePath(geo_object* g,bool ref);

        gsePath& operator=(geo_object* g);
        operator geo_object*() { return m_ptr; }
        bool Attach(geo_object*);
        geo_object* Detach();
        void Clear();

        //功能
        void NewSingle(int cdim, int num, double* xy, char* vt = 0);
        void NewSingleByRef(int num, double* xy);
        void NewMulti(int num, gsePath* subA);
        void NewOracle(int i_n, const int *i_p, int c_n, int c_dim, const double *c_p);
        gsePath CreateSpi();
        void NewPath3(int npt, void* xyz, void* uv,int vcs, bool ref);
        void NewPatht(gsePath p3A,int ntin, void* tin, int vcs, bool ref);
        
        template<class type> void NewPath3(int npt, type* xyz, type* uv, bool ref) {
            NewPath3(npt, xyz, uv, sizeof(type), ref);
        }
        template<class type> void NewPatht(gsePath p3A, int ntin, void* tin, bool ref) {
            NewPatht(p3A, ntin, tin, sizeof(type), ref);
        }

        bool IsNull() { return m_ptr == 0; }
        bool HasCurve();
        bool IsPaths();
        bool IsPathm();
        bool IsPath3();
        bool IsPatht();
        bool IsSpi();

        int PropSize();
        void PropSize(int cs);
        void* PropPtr();
        void PropClone(const gsePath& a);

        void id(id_type id) {
            PropSize(sizeof(id));
            *(id_type*)PropPtr() = id;
        }
        id_type id() { return *(id_type*)PropPtr(); }

        int i4_get(int id);
        void i4_set(int id, int value);

        int CDim();
        int GDim();
        void GDim(int d);

        int NumPoint();
        int NumSub();
        int Vcs();

        double* PtrPoint();
        double* PtrZ();

        void* PtrXYZ();
        void* PtrUV();
        void* PtrTin();
        gsePath PtrP3A();
        gsePath* PtrSub();
        
        void GetCurve(doubleA& xyA, charA& vtA);

        void GetSubs(gsePathA& A);
        void GetSingles(gsePathA& A);

        void InsertAt(int n, const double* T, const double* xy);

        double Length();
        double Area();

        void Envelope(double* env);
        void Label(double* xy);     //内部点
        void Label2(double* xy);    //内部点 计算速度比Label慢但落点更居中
        void Centroid(double* xy);
        void Maxline(double* xy_xy);

        double Distance(gsePath G,double* xy_xy);

        gsePath PropGeo(int mode);

        gsePath Clone();

        gsePath Hull(); //凸壳

        gsePath RectOuter(); //最小面积外接矩形
        gsePath RectInner(); //最大面积内接矩形
        gsePath SquareInner(); //最大面积内接正方形

        gsePath CircleOuter(); //最小面积外接圆
        gsePath CircleInner(); //最大面积内接圆

        void Split(gsePath a, gsePathA& A);

        int LeftRight(double* xy);
        void PointAt(double t, double* xy);
        double XY2T(double* xy);
        gsePath PathAt(double s, double t);

        gsePath Parallel(double r, int narc,int mode);
        gsePath Buffer(double r, int narc);

        gsePath GeoCombine(gsePath G,int mode);
        gsePath GeoUnion(gsePath G);
        gsePath GeoIntersect(gsePath G);
        gsePath GeoDiff(gsePath G);
        gsePath GeoSymDiff(gsePath G);

        int Modify(int mode, void* para);
        void Dauglas(double tol);
        void ToInt(double precision);  //将坐标改为precision的整数倍
        void Reverse();
        void ForceGoodDir();
        bool ForceGeoClose(double tol);
        
        gsePath Simplify(bool bxor = false);
        
        int SprQuery(gsePath G);
        bool SprIs(gsePath G, int mode);
        bool SprIsDisjion(gsePath G);
        bool SprIsIntersect(gsePath G);
        bool SprIsCross(gsePath G);
        bool SprIsEqual(gsePath G);
        bool SprIsTouch(gsePath G);
        bool SprIsOverlap(gsePath G);
        bool SprIsContain(gsePath G);
        bool SprIsWithin(gsePath G);

        gsePath CutByEnv(const double* env);
    };

    struct gseReader
    {
        geo_reader* m_ptr;

        ~gseReader();
        
        //构造
        gseReader() :m_ptr(0) {} 
        gseReader(geo_reader* p);
        gseReader(gsePathA& A);
        gseReader(const gseReader& p);        
        operator geo_reader*() { return m_ptr; }
        gseReader& operator=(const gseReader& p);

        //创建
        void Clear();
        void Create(void* user, gsePath(*fun)(void*));
        void Create(void* user, geo_object*(*fun)(void*, unsigned int i));
        void BindPathA(gsePathA& A);

        void _Bind(void* user, void* fun,gsePath (*read)(void*,void*));

        template<class type> struct mem_read
        {
            static gsePath _read(void* user, void* fun)
            {
                gsePath(type::*mem)();
                *(void**)&mem = fun;
                return ((*(type*)user).*mem)();
            }
        };

        template<class type>
        void Bind(type& T, gsePath(type::*fun)())
        {
            void* ptr = *(void**)&fun;
            _Bind(&T, ptr, &mem_read<type>::_read);
        }

        template<class type> struct mem_read2
        {
            type*   m_t;
            gsePath(type::*m_fun)(int);
            mem_read2(type* t, gsePath(type::*fun)(int)):m_t(t), m_fun(fun) {}
            geo_object* read(int i) {
                return (((*m_t).*m_fun)(i)).Detach();
            }
            static geo_object* _read2(void* user, unsigned int i) {
                mem_read2<type>* me = (mem_read2<type>*)user;
                if (i > 0) return me->read(i - 1);
                delete me; return 0;
            }
        };

        template<class type>
        void Bind2(type& T, gsePath(type::*fun)(int))
        {
            typedef mem_read2<type> read2;
            Create(new read2(&T, fun), read2::_read2);
        }

        //功能
        gsePath Read();
        void ReadPaths(gsePath p);
        void Open(const char* format, const char* fn);
        void OpenShp(const char* fn) { Open("shape", fn); }
        void OpenText(const char* fn) { Open("gtxt", fn); }
        void OpenGse(const char* fn) { Open("g2d", fn); }
    };

    struct gseWriter 
    {
        geo_writer* m_ptr;
        ~gseWriter();

        //构造
        gseWriter() :m_ptr(0) {} 
        gseWriter(gsePathA& A,bool clone);
        gseWriter(const gseWriter& p);
        gseWriter(geo_writer* p);
        operator geo_writer*() { return m_ptr; }
        gseWriter& operator=(const gseWriter& p);

        //创建
        void Clear();
        void BindPathA(gsePathA& A, bool clone = false);
        void Create(void* user, void(*fun)(void*, geo_object*));
        void Create(void* user, void(*fun)(void*, gsePath));

        void _Bind(void* user, void* fun, void(*write)(void*, void*,gsePath));

        template<class type> struct mem_write
        {
            static void _write(void* user, void* fun,gsePath g)
            {
                void(type::*mem)(gsePath);
                *(void**)&mem = fun;
                ((*(type*)user).*mem)(g);
            }
        };

        template<class type>
        void Bind(type& T, void(type::*fun)(gsePath))
        {
            void* ptr = *(void**)&fun;
            _Bind(&T, ptr, &mem_write<type>::_write);
        }

        //功能
        void Write(gsePath p);
        void WriteAll(geo_reader* R);
        void Open(const char* format, const char* fn);
        void OpenShp(const char* fn) { Open("shape", fn); }
        void OpenText(const char* fn) { Open("gtxt", fn); }
        void OpenGse(const char* fn) { Open("g2d", fn); }
    };

    struct gseTrans
    {
        geo_trans* m_ptr;
        ~gseTrans();

        //构造
        gseTrans() :m_ptr(0) {}
        gseTrans(const gseTrans& p);
        gseTrans(geo_trans* p);
        operator geo_trans*() { return m_ptr; }
        gseTrans& operator=(const gseTrans& p);
        void Clear();

        gsePath Trans(gsePath p);
        gseReader Trans(geo_reader* p);
        gseWriter Trans(geo_writer* p);

        //构造
        void Create(gsePath(*fun)(gsePath));
        void Create(void* user, gsePath(*fun)(void*, gsePath));

        void _Bind(void* user, void* fun, gsePath(*trans)(void*,void*, gsePath));

        template<class type> struct mem_trans
        {
            static gsePath _trans(void* user, void* fun,gsePath p)
            {
                gsePath(type::*mem)(gsePath);
                *(void**)&mem = fun;
                return ((*(type*)user).*mem)(p);
            }
        };

        template<class type>
        void Bind(type& T, gsePath(type::*fun)(gsePath))
        {
            void* ptr = *(void**)&fun;
            _Bind(&T, ptr, &mem_trans<type>::_trans);
        }
    };

    double Tolerance(); void Tolerance(double tol);

    bool SprIs(int spr, int mode);
    void SprQueryN2N(gseReader& A, gseReader& B, intA& result, int mode=0);

    void TopReserveSimplify(gsePathA& A, double tol, double* env);

    void LineClean(double tol, gseReader& R, gseWriter& W);
    void PolgonBuild(gseReader& R, gseWriter& W);
    void PolylineBuild(int nline, double* xy, gsePathA& lineA);
    void LineCombine(gseReader& R, double tol, double len, gsePathA& lineA);
}
