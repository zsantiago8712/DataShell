#include "../libs/Menus.h"



struct _Menu{
    
    char* menuOptions[BUFSIZ]; 
    int option;
};




//Constructor
Menu initMenu(void){

    Menu menuApp = NULL; 
    
    menuApp= malloc(sizeof(struct _Menu));
    if(menuApp == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    menuApp->option = 0;

    return menuApp;
}



//Destructors
Menu freeMenu(Menu menuApp){
    free(menuApp);

    menuApp = NULL;
    return menuApp;
}




//GETTERS
char** getMenuList(Menu menuApp){
    return menuApp->menuOptions;
}



int getOption(Menu menuApp){
    return menuApp->option;
}




//SETTER
void setMenuList(Menu menuApp, int state){


    const char* list[4][5] = { 
                            {"SHOW CSV FILE", "CONFIGS","EXIT", NULL},
                            {"CHANGE COLOR", "RETURN TO MAIN MENU", "EXIT", NULL},
                            {"ADD COLUMN", "RETURN TO MAIN MENU", "EXIT", NULL},
                            {"WHITE", "RED", "GREEN", NULL}
                        };


    for(int i = 0; list[state][i] != (void*)0; i++)
        menuApp->menuOptions[i] = strdup(list[state][i]);
}



ERROR_CODE setOption(Menu menuApp, int newOption){

    if(menuApp == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    menuApp->option = newOption;
    return ERROR_OK;
}





void printMenu(Menu menuApp){

    for(int i = 0; menuApp->menuOptions[i] != (void*)0; i++)
        printf("[%d]%s\n", i, menuApp->menuOptions[i]);
}






void printHeader(void){


    system("clear");
	puts(" ░█████╗░██████╗░██╗░░░██╗███╗░░██╗░█████╗░██╗░░██╗  ");
	puts("░██╔══██╗██╔══██╗██║░░░██║████╗░██║██╔══██╗██║░░██║  ");
	puts(" ██║░░╚═╝██████╔╝██║░░░██║██╔██╗██║██║░░╚═╝███████║  ");
	puts(" ██║░░██╗██╔══██╗██║░░░██║██║╚████║██║░░██╗██╔══██║  ");
	puts(" ╚█████╔╝██║░░██║╚██████╔╝██║░╚███║╚█████╔╝██║░░██║  ");
	puts( "░╚════╝░╚═╝░░╚═╝░╚═════╝░╚═╝░░╚══╝░╚═══╝░ ╚═╝░░ ╚╝  ");
	puts("");
	puts("			██████╗░░█████╗░████████╗░█████╗░░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░");
	puts("			██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░");
	puts("			██║░░██║███████║░░░██║░░░███████║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░");
	puts("			██║░░██║██╔══██║░░░██║░░░██╔══██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░");
	puts("			██████╔╝██║░░██║░░░██║░░░██║░░██║██████╔╝██║░░██║███████╗███████╗███████╗");
	puts("			╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝");
	printf("                                                                                               A.0.1\n");

}

