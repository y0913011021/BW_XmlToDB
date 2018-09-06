#ifndef _GLOBAL_COLOR_DEFINE_H_
#define _GLOBAL_COLOR_DEFINE_H_

#define make_rgba(r,g,b,a) (((a)<<24)|((b)<<16)|((g)<<8)|((r)))
#define make_rgb(r,g,b) (((0xff)<<24)|((b)<<16)|((g)<<8)|((r)))
#define make_qrgba(r,g,b,a) (((a)<<24)|((r)<<16)|((g)<<8)|((b)))
#define make_qrgb(r,g,b) (((0xff)<<24)|((r)<<16)|((g)<<8)|((b)))

#define argb2abgr(clr) (((clr) & 0xff000000)|(((clr) << 16) & 0xff0000)|((clr) & 0xff00)|(((clr) >> 16) & 0xff))

#endif // COLOR_DEFINE_H
