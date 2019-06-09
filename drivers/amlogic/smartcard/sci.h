#ifndef _STB_SCI_H
#define _STB_SCI_H

struct sci_parameters {
	unsigned char T;
	unsigned int f;
	unsigned int ETU;
	unsigned int WWT;
	unsigned int CWT;
	unsigned int BWT;
	unsigned int EGT;
	unsigned int clock_stop_polarity;
	unsigned char check;
	unsigned char P;
	unsigned char I;
	unsigned char U;
};

enum sci_voltage {
	SCI_1_8V,
	SCI_3V,
	SCI_5V,
};

#define IOCTL_SET_RESET			_IOW('s',  1, unsigned int)
#define IOCTL_SET_PARAMETERS		_IOW('s',  4, struct sci_parameters)
#define IOCTL_GET_PARAMETERS		_IOW('s',  5, struct sci_parameters)
#define IOCTL_GET_IS_CARD_PRESENT	_IOW('s',  8, unsigned int)
#define IOCTL_SET_ATR_READY		_IOW('s', 11, unsigned int)
#define IOCTL_SET_VOLTAGE		_IOW('s', 13, enum sci_voltage)

/* F = FI_tab[FI] */
/* D = DI_tab[DI] */
/* ETU = F / D */
/* T = {0,1,14} */
/* EGT = (N == 255) ? 11 : N + 12 */
struct sci_params_v2 {
	/* bitmask of SCIP_XXX to determine used fields */
	unsigned int flags;
#define SCIP_FS         (1 << 0)
#define SCIP_ETU        (1 << 1)
#define SCIP_FI_DI      (1 << 2)
#define SCIP_BWI        (1 << 3)
#define SCIP_CWI        (1 << 4)
#define SCIP_N          (1 << 5)
#define SCIP_WI         (1 << 6)
#define SCIP_T          (1 << 7)
	/* frequency in Hz */
	unsigned int fs;
	/* cycles per ETU */
	unsigned int etu;
	/* (TAi >> 4) & 0x0f */
 	unsigned int FI;
	/* (TAi >> 0) & 0x0f */
	unsigned int DI;
 	/* (TBi >> 4) & 0x0f [T == 1 && i > 2] */
	unsigned int BWI;
 	/* (TBi >> 0) & 0x0f [T == 1 && i > 2] */
	unsigned int CWI;
	/* (TCi >> 0) & 0xff */
	unsigned int N;
	/* (TCi >> 0) & 0xff [T == 0 && i == 2] */
	unsigned int WI;
	/* (TDi >> 0) & 0x0f */
	unsigned int T;
	/* for future use and binary compatibility */
	unsigned int reserved[6];
};

#define IOCTL_GET_PARAMS_V2	_IOR('s', 30, struct sci_params_v2)
#define IOCTL_SET_PARAMS_V2	_IOW('s', 31, struct sci_params_v2)

#endif
