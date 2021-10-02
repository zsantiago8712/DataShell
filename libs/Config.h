#ifndef CONFIG_H
#define CONFIG_H

#include "Libs.h"
#include "Files.h"
#include "ini.h"

typedef struct _Config* Config;


//Constructor
Config initConfig(void);


//Destructors
Config freeConfig(Config configToFree);



//FUNCIONES PRINCIPALES
void configureApp(Config configApp);


//SETTERS
ERROR_CODE setColor(Config configApp);


#endif
