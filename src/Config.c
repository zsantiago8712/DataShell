#include "../libs/Config.h"


static ERROR_CODE setInitConfiguratinosApp(Config configApp);
static void restartApp(Config configApp);
static ERROR_CODE checkConfig(Config configApp);
static char* createConfigCommandSize(Config configApp);


struct _Config{
    
    int width;
    int height;
    union{
        int numColor;
        char* hexColor;
    }color;
	

};


//Constructors
Config initConfig(void){
    
    Config config = NULL;
    config = malloc(sizeof(struct _Config));

    if(config == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    config->width = -1;
    config->height = -1;
	config->color.numColor = -1;

    return config;
}


//Destructors
Config freeConfig(Config configToFree){
    
    free(configToFree);
    configToFree = NULL;

    return configToFree;
}


//FUNCIONES PRINCIPALES

void configureApp(Config configApp){

    if(setInitConfiguratinosApp(configApp) != ERROR_OK)
        restartApp(configApp);

    system(CLEAN);
    system(createConfigCommandSize(configApp));
    printf("%s", configApp->color.hexColor);
    
}



//STATICS
static ERROR_CODE setInitConfiguratinosApp(Config configApp){
    ini_t* config = NULL;
    
    config = ini_load("config.ini");
    if(config == NULL)
        return CONFIG_FILE_NOT_FOUND;

    
    ini_sget(config, "app", "width", "%d", &configApp->width);
    ini_sget(config, "app", "height", "%d", &configApp->height);
    ini_sget(config, "app", "color", "%d", &configApp->color.numColor);



    if(checkConfig(configApp) == CONFIG_ERROR){       
        ini_free(config);
        return CONFIG_ERROR;
    }

    ini_free(config);
    setColor(configApp);

    return ERROR_OK;
}


static void restartApp(Config configApp){
    
    FILE* configFile = NULL;
    configFile = newFile("config.ini", WRITE);

    configApp = freeConfig(configApp);
    configFile = createConfigFile(configFile);
    closeFile(configFile);
    
    puts("THE APP NEEDS TO RESTART\n PLEASE PRESS ENTER");
    getchar();

    system("./myapp.out");
    exit(CONFIG_FILE_NOT_FOUND);
}


static ERROR_CODE checkConfig(Config configApp){

    if(configApp->color.numColor < 0 || configApp->height < 0 || configApp->width < 0)
        return CONFIG_ERROR;

    return ERROR_OK;
}


static char* createConfigCommandSize(Config configApp){
    
    char command[BUFSIZ] = "resize -s ";
    char number[20];
    
    sprintf(number, "%d ", configApp->width);
    strcat(command, number);
    
	sprintf(number, "%d ", configApp->height);
    strcat(command, number);

    return strdup(command);
}



//SETTERS
ERROR_CODE setColor(Config configApp){
    
    
    const char* configListColors[] = { "\x1B[0m",  "\x1B[31m", "\x1B[32m"};
    
    if(configApp != NULL)
        configApp->color.hexColor = strdup(configListColors[configApp->color.numColor]);
    
    return ERROR_OK;  
}

