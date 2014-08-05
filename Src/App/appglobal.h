#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include "iservicefactory.h"
#include "fileservicefactory.h"


class AppGlobal
{
public:
	static AppGlobal& instance()
	{
		static AppGlobal    ins;
		return ins;
	}

	const IServiceFactory & serviceFactory(){
		return FileServiceFactory::instance();
	}

private:
	AppGlobal() {};
	AppGlobal(const AppGlobal&);    
	void operator=(const AppGlobal &);
	
};

#endif // APPGLOBAL_H
