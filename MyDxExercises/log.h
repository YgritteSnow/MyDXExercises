#ifndef __LOG_H__
#define __LOG_H__


#define LogOutput LogOutputA
void LogOutputA(char* st, ...);

#define HR_RETURN(hr) \
	res = hr; \
	if( FAILED(res) ) \
	{ \
		LogOutput("HRESULT = %u; ", (UINT)res); \
		LogOutput("%s, %s, %s", __FILE__, __LINE__, #hr); \
		abort(); \
		return; \
	}

#endif 