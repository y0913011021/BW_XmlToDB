#ifndef GLOBAL_MATH_DEFINE_H
#define GLOBAL_MATH_DEFINE_H

#ifndef Min
#define Min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef Max
#define Max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef Abs
#define Abs(a) ((a) >= 0 ? (a) : -(a))
#endif

#ifndef MIN2
#define MIN2 Min
#endif
#ifndef MAX2
#define MAX2 Max
#endif

// 浮点数0值及其相等比较
#define INFINITESIMAL (1.0e-5)
#define EqualZero(a) (Abs(a) < INFINITESIMAL)
#define Equal(a,b) EqualZero((a)-(b))
#define Less(a,b) ((a)+INFINITESIMAL < (b))
#define Big(a,b) ((a) < (b)+INFINITESIMAL)
#define LessEqual(a,b) (Equal(a,b) || (a) < (b))
#define BigEqual(a,b)  (Equal(a,b) || (a) > (b))

#ifndef Equal3
#define Equal3(a, b, pre) (Abs((a)-(b))<(pre))
#endif

#define ToInt(a) ((int)((a)+INFINITESIMAL))

// 弧度转变为角度
#ifndef Rad2Deg
#define Rad2Deg	((float)57.29577951308232)
#endif
// 角度转变为弧度
#ifndef Deg2Rad
#define Deg2Rad	((float)0.01745329251994)
#endif

#ifndef M_PI
#define M_PI  ((float)3.1415926536)
#endif
#ifndef M_2PI
#define M_2PI ((float)6.2831853072)
#endif

#define Radian2Degree(a) ((a)*Rad2Deg)
#define Degree2Radian(a) ((a)*Deg2Rad)

#define AziBetween(a, abgn, aend) (abgn<=aend?(a>=abgn&&a<=aend):(a<=aend||a>=abgn))
#define AziBetween1(a, abgn, aend) (abgn<=aend?(a>=abgn&&a<aend):(a<aend||a>=abgn))
#define AziWidth(bgn, end) ((360+(end)-(bgn))%360)


#endif // MATH_DEFINE_H
