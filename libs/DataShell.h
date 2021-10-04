#ifndef DATASHELL_H
#define DATASHELL_H

#include "Libs.h"
#include "Menus.h"
#include "Memory.h"
#include "Files.h"
#include "fort.h"
#include "Config.h"

typedef struct _DataShell* DataShell;

//Constructor
DataShell initDataShell(void);


//Destructors
DataShell freeDataShell(DataShell app);


//FUNCIONES PRINCIPALES
void selectOption(DataShell app, Menu menuApp);
//void controller(DataShell app, Menu menuApp);
void clearBuffer(void);

//DEBUG NEWIMPLEMETACION
void selectOption2(DataShell app, Menu menuApp);
void dynamicController(DataShell app, Menu menuApp, Config configApp);


//GETTERS

char*** getMatrixData(DataShell app);
char** getMatrixDataRow(DataShell app, size_t indexRow);
int getState(DataShell app);
//SETTERS



#endif
