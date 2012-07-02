#ifndef REGS_H
#define REGS_H
struct dword_regs
{
	unsigned int	edi,
					esi,
					ebp,
					cflag,
					ebx,
					edx,
					ecx,
					eax;
	unsigned short 	eflags;
};

struct word_regs
{
	unsigned short	di, _u_di,
					si, _u_si,
					bp, _u_bp,
					cflag, _u_cflag,
					bx, _u_bx,
					dx, _u_dx,
					cx, _u_cx,
					ax, _u_ax,
					flags;
};

struct byte_regs
{
	unsigned short	di, _u_di,
					si, _u_si,
					bp, _u_bp;
	unsigned int	cflag;

	unsigned char	bl,
					bh;
	unsigned short	_u_bx;

	unsigned char	dl,
					dh;
	unsigned short	_u_dx;

	unsigned char	cl,
					ch;
	unsigned short	_u_cx;

	unsigned char	al,
					ah;
	unsigned short	_u_ax;

};

union regs
{
	struct dword_regs d;
	struct word_regs  w;
	struct byte_regs  h;
};
#endif