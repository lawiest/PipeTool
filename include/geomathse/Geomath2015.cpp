#ifndef  ANDROID

#include "GeomathSE.h"
#include "Geomath2015.h"

#ifdef _WINDOWS
#include <Windows.h>
void* gseCall(const char* fname)
{
	char buf[512]; void* ptr; HMODULE dll;
	const char *dname = "\\gsGeomathSE.dll";
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, dname, &dll);
    ::GetModuleFileNameA(dll, buf, sizeof(buf));
    memcpy(strrchr(buf, '\\'), dname, 17);
    ptr = ::GetProcAddress(::LoadLibraryA(buf), fname);
    return ((void* (*)())ptr)();
}
#else    
extern "C" geostar::geo_factory* CreateGPfactory();
extern "C" geostar::geo_algorithm* CreateGAlgorithm();
void* gseCall(const char* fname)
{   
    if (strcmp(fname, "CreateGPfactory") == 0)
        return CreateGPfactory();
    if (strcmp(fname, "CreateGAlgorithm") == 0)
        return CreateGAlgorithm();
    return 0;
}
#endif

namespace geostar
{
    geo_factory& g_f()
    {
        static geo_factory* g = 0;
        if (g == 0) g = (geo_factory*)gseCall("CreateGPfactory");
        return *g;
    }
    geo_algorithm& g_a()
    {
        static geo_algorithm* g = 0;
        if (g == 0) g = (geo_algorithm*)gseCall("CreateGAlgorithm");;
        return *g;
    }
    static inline geo_object* _addref(geo_object* p) { if (p)p->addref(); return p; }
    static inline void _release(geo_object* p) { if (p)p->release(); }

    template<class base> struct t_object :base
    {
        int m_ref;
        t_object() :m_ref(1) {}
        virtual ~t_object() {}
        virtual string_t type_info()const { return 0; }
        virtual void* type_cast(string_t) { return 0; }
        virtual int i4_get(int i) { return 0; }
        virtual bool i4_set(int i, int v) { return false; }

        virtual int addref() {
            return (++m_ref);
        }
        virtual int release() {
            if ((--m_ref) > 0)
                return m_ref;
            delete this;
            return 0;
        }
    };

#pragma region gseTrans
    gseTrans::~gseTrans() {
        _release(m_ptr);
    }
    gseTrans::gseTrans(const gseTrans& p) {
        _addref(m_ptr = p.m_ptr);
    }
    gseTrans::gseTrans(geo_trans* p) {
        _addref(m_ptr = p);
    }
    gseTrans& gseTrans::operator=(const gseTrans& p) {
        Clear();
        _addref(m_ptr = p.m_ptr);
        return *this;
    }
    void gseTrans::Clear() {
        _release(m_ptr); m_ptr = 0;
    }
    gsePath gseTrans::Trans(gsePath p)
    {
        if (m_ptr && p.m_ptr)
            p.m_ptr = m_ptr->trans(p.m_ptr);
        return p;
    }
    void gseTrans::Create(gsePath(*fun)(gsePath))
    {
        struct Trans :t_object<geo_trans>
        {
            gsePath(*m_fun)(gsePath);
            Trans(gsePath(*fun)(gsePath)) :m_fun(fun) {}
            geo_object* trans(geo_object* p) {
                return m_fun(p).Detach();
            }
            bool setpara(string_t, void*) { return false; }
        };
        Clear();
        m_ptr = new Trans(fun);
    }
    void gseTrans::Create(void* user, gsePath(*fun)(void*,gsePath p))
    {
        struct Trans :t_object<geo_trans>
        {
            void*   m_user;
            gsePath(*m_fun)(void*,gsePath);
            Trans(void* user, gsePath(*fun)(void*,gsePath)) :m_user(user), m_fun(fun) {}
            geo_object* trans(geo_object* p) {
                return m_fun(m_user,p).Detach(); 
            }
            bool setpara(string_t, void*) { return false; }
        };
        Clear();
        m_ptr = new Trans(user, fun);
    }
    void gseTrans::_Bind(void* user, void* fun, gsePath(*trans)(void*, void*,gsePath))
    {
        struct Trans :t_object<geo_trans>
        {
            void*   m_user;
            void*   m_fun;
            gsePath(*m_trans)(void*, void*,gsePath);
            Trans(void* user, void* fun, gsePath(*read)(void*, void*,gsePath)) :m_user(user), m_fun(fun), m_trans(read) {}
            geo_object* trans(geo_object* p) {
                return m_trans(m_user, m_fun, p).Detach();
            }
            bool setpara(string_t, void*) { return false; }
        };
        Clear();
        m_ptr = new Trans(user, fun, trans);
    }
    gseReader gseTrans::Trans(geo_reader* p)
    {   
        if (p == 0 || m_ptr == 0)
            return p;
        gseReader R;
        R.m_ptr = g_f().new_reader_trans(p, 1, &m_ptr);
        return R;
    }
    gseWriter gseTrans::Trans(geo_writer* p)
    {
        if (p == 0 || m_ptr == 0)
            return p;
        struct Writer :t_object<geo_writer>
        {
            geo_writer*     m_w;
            geo_trans*      m_t;
            Writer(geo_writer* w, geo_trans* t) :m_w(w), m_t(t) {
                w->addref(); t->addref();
            }
            ~Writer() {
                m_w->release();
                m_t->release();
            }
            void write(geo_object* p) {
                p = m_t->trans(p);
                m_w->write(p);
                _release(p);
            }
        };
        gseWriter W;
        W.m_ptr = new Writer(p, m_ptr);
        return W;
    }
#pragma endregion

#pragma region gseReader
    gseReader::~gseReader() {
        _release(m_ptr);
    }
    gseReader::gseReader(gsePathA& A){
        m_ptr = 0;
        BindPathA(A);
    }
    gseReader::gseReader(const gseReader& p) {
        _addref(m_ptr = p.m_ptr);
    }
    gseReader::gseReader(geo_reader* p) {
        _addref(m_ptr = p);
    }
    gseReader& gseReader::operator=(const gseReader& p) {
        Clear(); 
        _addref(m_ptr = p.m_ptr);
        return *this;
    }
    void gseReader::Clear() {
        _release(m_ptr); m_ptr = 0;
    }
    void gseReader::Create(void* user, gsePath(*fun)(void*))
    {
        struct Reader :t_object<geo_reader>
        {
            void*   m_user;
            gsePath(*m_fun)(void*);
            Reader(void* user, gsePath(*fun)(void*)) :m_user(user), m_fun(fun) {}
            geo_object* read() { return m_fun(m_user).Detach(); }
        };
        Clear();
        m_ptr = new Reader(user, fun);
    }
    void gseReader::_Bind(void* user, void* fun, gsePath(*read)(void*, void*))
    {
        struct Reader :t_object<geo_reader>
        {
            void*   m_user;
            void*   m_fun;
            gsePath(*m_read)(void*,void*);
            Reader(void* user,void* fun, gsePath(*read)(void*,void*)) :m_user(user), m_fun(fun),m_read(read) {}
            geo_object* read() { return m_read(m_user,m_fun).Detach(); }
        };
        Clear();
        m_ptr = new Reader(user, fun,read);
    }

    void gseReader::Create(void* user, geo_object*(*fun)(void*, unsigned int i)) {
        Clear();
        m_ptr = g_f().new_reader(user, fun);
    }
    static geo_object* _readA_callback(void* user, unsigned int i) {
        if (i == 0) return 0;
        gsePathA& A = *(gsePathA*)user;
        return i > A.size() ? 0 : _addref(A[i-1]);
    }
    void gseReader::BindPathA(gsePathA& A)
    {
        Clear();
        m_ptr = g_f().new_reader(&A, _readA_callback);
    }
    gsePath gseReader::Read()
    {
        gsePath p;
        if (m_ptr)
            p.m_ptr = m_ptr->read();
        return p;
    }
    void gseReader::Open(const char* format, const char* fn)
    {
        Clear();
        m_ptr = g_f().open_reader(format, fn);
    }
    void gseReader::ReadPaths(gsePath p)
    {
        Clear();
        m_ptr = g_f().open_reader("path_s", (string_t)p.m_ptr);
    }
#pragma endregion

#pragma region gseWrite
    gseWriter::~gseWriter() {
        _release(m_ptr);
    }
    gseWriter::gseWriter(gsePathA& A,bool clone) {
        m_ptr = 0;
        BindPathA(A, clone);
    }
    gseWriter::gseWriter(const gseWriter& p) {
        _addref(m_ptr = p.m_ptr);
    }
    gseWriter::gseWriter(geo_writer* p) {
        _addref(m_ptr = p);
    }
    gseWriter& gseWriter::operator=(const gseWriter& p) {
        Clear();
        _addref(m_ptr = p.m_ptr);
        return *this;
    }
    void gseWriter::Clear() {
        _release(m_ptr); m_ptr = 0;
    }
    void gseWriter::Create(void* user, void(*fun)(void*, gsePath))
    {
        struct Writer :t_object<geo_writer>
        {
            void*   m_user;
            void(*m_fun)(void*,gsePath);
            Writer(void* user, void(*fun)(void*,gsePath)) :m_user(user), m_fun(fun) {}
            void write(geo_object* p) { 
                gsePath g(p);
                m_fun(m_user, g);
            }
        };
        Clear();
        m_ptr = new Writer(user, fun);
    }
    void gseWriter::Create(void* user, void(*fun)(void*, geo_object*)){
        Clear();
        m_ptr = g_f().new_writer(user, fun);
    }
    static void _writeA_callback0(void* user, geo_object* p) {
        if (p == 0) return;
        ((gsePathA*)user)->push_back(p);
    }
    static void _writeA_callback1(void* user, geo_object* p) {
        if (p == 0) return;
        ((gsePathA*)user)->push_back(gsePath(p).Clone());
    }
    void gseWriter::BindPathA(gsePathA& A, bool clone)
    {
        Clear();
        m_ptr = g_f().new_writer(&A, clone ? _writeA_callback1 : _writeA_callback0);
    }
    void gseWriter::_Bind(void* user, void* fun, void(*write)(void*, void*,gsePath))
    {
        struct Writer :t_object<geo_writer>
        {
            void*   m_user;
            void*   m_fun;
            void (*m_write)(void*, void*,gsePath);
            Writer(void* user, void* fun, void(*write)(void*, void*, gsePath)) 
                :m_user(user), m_fun(fun), m_write(write) {}
            void write(geo_object* g) { 
                if (g == 0) return;
                gsePath p(g);
                m_write(m_user, m_fun, g);
            }
        };
        Clear();
        m_ptr = new Writer(user, fun, write);
    }
    void gseWriter::Write(gsePath p)
    {
        if (m_ptr)
            m_ptr->write(p.m_ptr);
    }

    void gseWriter::WriteAll(geo_reader* R)
    {
        if (R == 0 || m_ptr == 0)
            return;
        gsePath p;
        while (p.Attach(R->read()))
        {
            m_ptr->write(p.m_ptr);
        }
    }

    void gseWriter::Open(const char* format, const char* fn)
    {
        Clear();
        m_ptr = g_f().open_writer(format, fn);
    }

#pragma endregion
    
#pragma region gsePath
    gsePath::~gsePath() {
        _release(m_ptr);
    }
    gsePath::gsePath(const gsePath& p) {
        _addref(m_ptr = p.m_ptr);
    }
    gsePath::gsePath(geo_object* p) {
        _addref(m_ptr = p);
    }
    gsePath::gsePath(geo_object* p,bool ref) {
        m_ptr = p;
        if (ref) _addref(p);
    }
    gsePath& gsePath::operator=(const gsePath& p) {
        Clear();
        _addref(m_ptr = p.m_ptr);
        return *this;
    }
    gsePath& gsePath::operator=(geo_object* g) {
        Clear();
        _addref(m_ptr = g);
        return *this;
    }
    bool gsePath::Attach(geo_object* p) {
        Clear();
        m_ptr = p;
        return m_ptr != 0;
    }
    geo_object* gsePath::Detach() {
        geo_object* p = m_ptr;
        m_ptr = 0;
        return p;
    }
    int gsePath::i4_get(int id) {
        return m_ptr ? m_ptr->i4_get(id) : 0;
    }
    void gsePath::i4_set(int id, int value) {
        if (m_ptr) m_ptr->i4_set(id, value);
    }
    void gsePath::Clear() {
        _release(m_ptr); m_ptr = 0;
    }
    void gsePath::NewSingle(int cdim, int num, double* xy, char* vt)
    {
        Clear();
        m_ptr = g_f().create_single(0, num, cdim, xy, 0, vt);
    }

    void gsePath::NewSingleByRef(int num, double* xy)
    {
        Clear();
        m_ptr = g_f().create_single(0, num, 2, xy, 1, 0);
    }
    void gsePath::NewMulti(int num, gsePath* subA)
    {
        Clear();
        m_ptr = g_f().create_multi(0, num, (geo_object**)subA, 0);
    }    
    void gsePath::NewOracle(int i_n, const int *i_p, int c_n, int c_dim, const double *c_p)
    {
        Clear();
        m_ptr = g_f().ora_create(i_n, i_p, c_n, c_dim, c_p, 0);
    }
    void gsePath::NewPath3(int npt, void* xyz, void* uv, int vcs, bool ref) {
        Clear();
        m_ptr = g_f().new_path_3(npt, xyz, uv, vcs, ref);
    }
    void gsePath::NewPatht(gsePath p3A, int ntin, void* tin, int vcs, bool ref){
        Clear();
        m_ptr = g_f().new_path_t(p3A.m_ptr, ntin,tin, vcs, ref);
    }
    gsePath gsePath::CreateSpi()
    {
        gsePath p;
        p.m_ptr = g_a().spi_create(m_ptr, 0);
        return p;
    }
    bool gsePath::IsPaths() {
        return m_ptr && m_ptr->m_ptr(m_ptr_path_s_xy) != 0;
    }
    bool gsePath::IsPathm() {
        return m_ptr && m_ptr->m_ptr(m_ptr_path_m_subs) != 0;
    }
    bool gsePath::IsPath3() {
        return m_ptr && m_ptr->m_ptr(m_ptr_path_3_xyz) != 0;
    }
    bool gsePath::IsPatht() {
        return m_ptr && m_ptr->m_ptr(m_ptr_path_t_tin) != 0;
    }
    bool gsePath::IsSpi() {
        return m_ptr && m_ptr->m_ptr(m_ptr_spi_path) != 0;
    }
    int gsePath::PropSize(){
        return m_ptr->i4_get(geometry_i4_prop_len) * 4;
    }
    void gsePath::PropSize(int cs) {
        m_ptr->i4_set(geometry_i4_prop_len, (cs + 3) / 4);
    }
    void* gsePath::PropPtr() {
        return m_ptr->m_ptr(m_ptr_path_i4);
    }
    void gsePath::PropClone(const gsePath& a){
        if (m_ptr == 0 || a.m_ptr == 0) return;
        gsePath b = a;
        int n = b.PropSize();
        PropSize(n);
        memcpy(PropPtr(), b.PropPtr(), n);
    }
    int gsePath::CDim() {
        //error
        return m_ptr->i4_get(geometry_i4_gdim);
    }
    int gsePath::GDim() {
        return m_ptr->i4_get(geometry_i4_gdim);
    }
    void gsePath::GDim(int d) {
        m_ptr->i4_set(geometry_i4_gdim,d);
    }
    int gsePath::Vcs() {
        return m_ptr->i4_get(i4_path_vcs);
    }
    int gsePath::NumPoint() {
        return m_ptr->i4_get(i4_path_ptn);
    }
    int gsePath::NumSub() {
        return m_ptr->i4_get(i4_path_subn);
    }
    bool gsePath::HasCurve() {
        return m_ptr->i4_get(i4_path_has_arc)?true:false;
    }
    double* gsePath::PtrPoint() {
        return (double*)m_ptr->m_ptr(m_ptr_path_s_xy);
    }
    double* gsePath::PtrZ() {
        return (double*)m_ptr->m_ptr(m_ptr_path_s_z);
    }
    gsePath* gsePath::PtrSub() {
        return (gsePath*)m_ptr->m_ptr(m_ptr_path_m_subs);
    }
    void* gsePath::PtrXYZ() {
        return m_ptr->m_ptr(m_ptr_path_3_xyz);
    }
    void* gsePath::PtrUV() {
        return m_ptr->m_ptr(m_ptr_path_3_uv);
    }
    void* gsePath::PtrTin() {
        return m_ptr->m_ptr(m_ptr_path_t_tin);
    }
    gsePath gsePath::PtrP3A() {
        return gsePath((geo_object*)m_ptr->m_ptr(m_ptr_path_t_p3A));
    }
    void gsePath::GetSubs(gsePathA& A) {
        if (m_ptr == 0)return;
        int n; gsePath* P;
        if( (n = NumSub()) == 0) {
            A.push_back(*this);
            return;
        }
        P = PtrSub();
        A.insert(A.end(), P, P + n);
    }
    void gsePath::GetCurve(doubleA& xyA, charA& vtA)
    {
        if (m_ptr == 0) return;
        int cdim, gdim, num; double* xyz; char* vt;
        g_f().out_single(m_ptr, &cdim, &gdim, &num, &xyz, &vt);
        xyA.resize(num*cdim);
        memcpy(&xyA[0], xyz, cdim*num * 8);
        vtA.clear();
        if (vt == 0) return;
        vtA.resize(num);
        memcpy(&vtA[0], vt, num);
    }
    void gsePath::GetSingles(gsePathA& A) {
        if (m_ptr == 0)return;
        int i,n; gsePath* P;
        if ((n = NumSub()) == 0) {
            A.push_back(*this);
            return;
        }
        P = PtrSub();
        for (i = 0; i < n; ++i)
            P[i].GetSingles(A);
    }
    void gsePath::InsertAt(int n, const double* T, const double* xy){
        if (m_ptr == 0) return;
        g_a().insert_at(m_ptr, n, T, xy);
    }
    double gsePath::Length() {
        return g_a().prop_value(m_ptr, prop_value_length);
    }
    double gsePath::Area() {
        return g_a().prop_value(m_ptr, prop_value_area);
    }
    void gsePath::Envelope(double* env) {
        g_a().prop_geo_2(m_ptr, prop_geo_env, env);
    }
    void gsePath::Label(double* xy) {
        g_a().prop_geo_2(m_ptr, prop_geo_label,xy);
    }
    void gsePath::Label2(double* xy){
        g_a().layout(m_ptr, 0, 0, 1, xy);
    }
    void gsePath::Centroid(double* xy) {
        g_a().prop_geo_2(m_ptr, prop_geo_centroid, xy);
    }
    void gsePath::Maxline(double* xy_xy) {
        g_a().prop_geo_2(m_ptr, prop_geo_maxline, xy_xy);
    }
    double gsePath::Distance(gsePath G, double* xy_xy){
        double A[4],x,y;
        geo_object* l = g_a().nearest(m_ptr, G.m_ptr);
        memcpy(A, l->m_ptr(m_ptr_path_s_xy), sizeof(A));
        l->release();
        if (xy_xy) memcpy(xy_xy, A, sizeof(A));
        x = A[0] - A[2]; y = A[1] - A[3];
        return sqrt(x*x + y*y);
    }
    gsePath gsePath::PropGeo(int mode) {
        gsePath p;
        if (m_ptr) p.m_ptr = g_a().prop_geo(m_ptr, mode);
        return p;
    }
    gsePath gsePath::Clone() {
        return PropGeo(prop_geo_clone);
    }
    gsePath gsePath::Hull() {
        return PropGeo(prop_geo_hull);
    }
    gsePath gsePath::RectOuter() {
        return PropGeo(prop_geo_env_nstd);
    }
    gsePath gsePath::RectInner() {
        return PropGeo(prop_geo_inner_rect);
    }
    gsePath gsePath::SquareInner() {
        return PropGeo(prop_geo_inner_square);
    }
    gsePath gsePath::CircleOuter() {
        return PropGeo(prop_geo_env_circle);
    }
    gsePath gsePath::CircleInner() {
        return PropGeo(prop_geo_inner_circle);
    }
    int gsePath::LeftRight(double* xy) {
        return g_a().left_right(m_ptr, xy[0], xy[1]);
    }
    double gsePath::XY2T(double* xy) {
        return g_a().xy2t(m_ptr, xy);
    }
    void gsePath::PointAt(double t, double* xy) {
        g_a().t2xy(m_ptr, t, xy);
    }
    gsePath gsePath::PathAt(double s, double t) {
        gsePath p;
        p.m_ptr = g_a().t2path(m_ptr, s, t);
        return p;
    }
    void gsePath::Split(gsePath a, gsePathA& A){
        gseWriter W; W.BindPathA(A);
        g_a().gsplit(m_ptr, a.m_ptr, W.m_ptr);
    }
    gsePath gsePath::GeoCombine(gsePath G,int mode) {
        gsePath g;
        g.m_ptr = g_a().gcombine(m_ptr, G.m_ptr, mode);
        return g;
    }
    gsePath gsePath::GeoUnion(gsePath G) {
        return GeoCombine(G, gcombine_union);
    }
    gsePath gsePath::GeoIntersect(gsePath G) {
        return GeoCombine(G, gcombine_intersect);
    }
    gsePath gsePath::GeoDiff(gsePath G) {
        return GeoCombine(G, gcombine_diffrence);
    }
    gsePath gsePath::GeoSymDiff(gsePath G) {
        return GeoCombine(G, gcombine_sym_diffrence);
    }
    gsePath gsePath::Buffer(double r, int narc) {
        static thread_local geo_trans* T = 0;
        if(T==0) T = g_f().create_trans("buffer");
        T->setpara("radius", &r);
        T->setpara("narc", &narc);
        gsePath g;
        g.m_ptr = T->trans(m_ptr);
        return g;
    }
    gsePath gsePath::CutByEnv(const double* env) {
        static thread_local geo_trans* T = 0;
        if (T == 0) {
            T = g_f().create_trans("cut_by_env");
        }
        gsePath g;
        T->setpara("env", (void*)env);
        g.m_ptr = T->trans(m_ptr);
        return g;
    }
    gsePath gsePath::Parallel(double r, int narc, int mode) {
        static thread_local geo_trans* T = 0;
        if (T == 0) {
            T = g_f().create_trans("parallel");
        }
        T->setpara("radius", &r);
        T->setpara("narc", &narc);
        T->setpara("mode", &mode);
        gsePath g;
        g.m_ptr = T->trans(m_ptr);
        return g;
    }
    int gsePath::Modify(int mode, void* para){
        return g_a().gmodify(m_ptr, mode, para);
    }
    void gsePath::Dauglas(double tol) {
        Modify(gmodify_dauglas, &tol);
    }
    void gsePath::Reverse() {
        Modify(gmodify_reverse, 0);
    }
    void gsePath::ForceGoodDir() {
        Modify(gmodify_force_good_dir, 0);
    }
    bool gsePath::ForceGeoClose(double tol) {
        return Modify(gmodify_force_geo_close, &tol)==0;
    }

    static void _toint(gsePath s, double d) {
        int n = s.NumPoint();
        if (n < 1) return;
        double t,*xy = s.PtrPoint();
        t = 1.0 / d;
        for (n *= 2; --n >= 0; ++xy)
            *xy = floor(*xy*t)*d;
    }
    void gsePath::ToInt(double precision) {
        gsePathA A; GetSingles(A);
        for (int i = (int)A.size(); --i >= 0;)
            _toint(A[i], precision);
    }
    gsePath gsePath::Simplify(bool bxor) {
        gsePath p;
        p.m_ptr = g_a().prop_geo(m_ptr, bxor ? prop_geo_simplify2 : prop_geo_simplify);
        return p;
    }
    int gsePath::SprQuery(gsePath G) {
        return g_a().spr_query(m_ptr, G.m_ptr);
    }
    bool gsePath::SprIs(gsePath G, int mode) {
        return g_a().spr_query_is(m_ptr, G.m_ptr, mode);
    }
    bool gsePath::SprIsDisjion(gsePath G) {
        return !SprIs(G, geostar::spr_is_intersect);
    }
    bool gsePath::SprIsIntersect(gsePath G) {
        return SprIs(G, geostar::spr_is_intersect);
    }
    bool gsePath::SprIsCross(gsePath G) {
        return SprIs(G, geostar::spr_is_cross);
    }
    bool gsePath::SprIsEqual(gsePath G) {
        return SprIs(G, geostar::spr_is_equal);
    }
    bool gsePath::SprIsTouch(gsePath G) {
        return SprIs(G, geostar::spr_is_touch);
    }
    bool gsePath::SprIsOverlap(gsePath G) {
        return SprIs(G, geostar::spr_is_overlap);
    }
    bool gsePath::SprIsContain(gsePath G) {
        return SprIs(G, geostar::spr_is_contain);
    }
    bool gsePath::SprIsWithin(gsePath G) {
        return SprIs(G, geostar::spr_is_within);
    }
#pragma endregion

#pragma region 
    bool SprIs(int spr, int mode)
    {
        return g_a().spr_is(spr, mode);
    }
    void SprQueryN2N(gseReader& A, gseReader& B, intA& result, int mode)
    {
        gseWriter W;
        W.m_ptr = g_f().new_writer(&result, [](void* user, geo_object* p) {
            intA* A = (intA*)user;
			if (p == 0) return;
            int n = p->i4_get(geometry_i4_prop_len);
            int* i = (int*)p->m_ptr(m_ptr_path_i4);
            A->insert(A->end(), i, i + n);
        });
        g_a().spr_query_n2n(A.m_ptr, B.m_ptr, W.m_ptr, mode);
    }
#pragma endregion
}

#endif
