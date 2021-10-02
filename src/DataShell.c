#include "../libs/DataShell.h"


static void exitApp(DataShell app, Menu menuApp);
static void returnMainMenu(DataShell app, Menu menuApp);
static ERROR_CODE showCSVFile(DataShell app, Menu menuApp);
static void reprintData(DataShell app);
static void printData(DataShell app);
static ERROR_CODE setFileName(DataShell app);
static ERROR_CODE addColumn(DataShell app);
static char* getNameNewColumn(void);
static void changeColor(DataShell app, int option);



struct _DataShell{
    
    int state;
    size_t columns;
    size_t rows;
    size_t columnsWithData;
    size_t rowsWithData;
    char*** data;
    char fileName[BUFSIZ];
};


//Constructor
DataShell initDataShell(void){


    DataShell app = NULL;
    
    app = malloc(sizeof(struct _DataShell));
    if(app == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    app->state = 0;
    app->columns = 8;
    app->rows = 8;
    app->columnsWithData = 8;
    app->rowsWithData = 8;   
    app->data = createMatrixString(app->data, app->rows, app->columns);
    return app;
}


//Destructors
DataShell freeDataShell(DataShell app){
    
    free(app);
    app = NULL;

    return app;
}


//FUNCIONES PRINCIPALES
void selectOption(DataShell app, Menu menuApp){

    char input = '\0';

	do {
    
        reprintData(app);
        printMenu(menuApp);
    }while((input = getchar()) != '0' && input != '1' && '2' != input);

    setOption(menuApp, input - '0');

}


void controller(DataShell app, Menu menuApp){
    
    if(app->state == 0 && getOption(menuApp) == 0)
        showCSVFile(app, menuApp);
    else if(app->state == 2 && getOption(menuApp) == 0)
        addColumn(app);
    else if(app->state == 0 && getOption(menuApp) == 1)
        app->state= 1;
    else if(app->state == 1 && getOption(menuApp) == 0)
        app->state = 3;
    else if(app->state == 3){
        changeColor(app, getOption(menuApp));
        returnMainMenu(app, menuApp);
    }
    else if(getOption(menuApp) == 1)
        returnMainMenu(app, menuApp);
    else if(getOption(menuApp) == 2)
        exitApp(app, menuApp);

    setOption(menuApp, 0);
}


void clearBuffer(void){

	char input;
	while((input = getchar()) != '\n');
}


 






// GETTERS
char*** getMatrixData(DataShell app){
    return app->data;
}


char** getMatrixDataRow(DataShell app, size_t indexRow){

    return app->data[indexRow];
}


int getState(DataShell app){
    return app->state;
}




// SETTER
ERROR_CODE setMatrixData(DataShell app, size_t indexRow, size_t indexColumn, char* newData){

    if(app != NULL)
        app->data[indexRow][indexColumn] = strdup(newData);
    
    return ERROR_OK;

}










//STATICS
static ERROR_CODE showCSVFile(DataShell app, Menu menuApp){

    FILE* csvFile = NULL;
    
    setFileName(app);

    csvFile = newFile(app->fileName, READ);
    if(csvFile == NULL){
       
        csvFile = closeFile(csvFile);
        app->state = 0;
        puts("PRESS ENTER TO RETURN TO MAIN MENU\n");
        getchar();
        return FILE_NOT_FOUND;
    }

    app->data = readCsvFile(csvFile, app->data, &app->rows, &app->rowsWithData, &app->columns, &app->columnsWithData);
    csvFile = closeFile(csvFile);


    app->state = 2;
    return ERROR_OK;
}



static ERROR_CODE setFileName(DataShell app){
    
    
    if(app != NULL){

        puts("ENTER THE NAME OF THE FILE YOU WANT TO SEE\n");
        fgets(app->fileName, sizeof(app->fileName), stdin);
        app->fileName[strcspn(app->fileName, "\n")] = 0;
    }
    return ERROR_OK;
}



static ERROR_CODE addColumn(DataShell app){
    
    FILE* csvFile = NULL;
    
    csvFile = newFile(app->fileName, WRITE);
    if(csvFile == NULL){
        csvFile = closeFile(csvFile);
        app->state = 1;

        return FILE_NOT_FOUND;
    }

    for(size_t i = 0; i < app->rowsWithData; i++){
        
        if(i == 0)
            setMatrixData(app, i, app->columnsWithData, getNameNewColumn());
        else
            setMatrixData(app, i, app->columnsWithData, "NULL");
    }

    app->columnsWithData += 1;

    writeCsvFile(csvFile, app->data, app->rowsWithData, app->columnsWithData);

	csvFile = closeFile(csvFile);
    return ERROR_OK;    
}

static char* getNameNewColumn(void){
    
    char nameNewColumn[BUFSIZ];
    fgets(nameNewColumn, BUFSIZ, stdin);

    nameNewColumn[strcspn(nameNewColumn, "\n")] = 0;

    return nameNewColumn;
}


static void returnMainMenu(DataShell app, Menu menuApp) {

	if (app->state == 2)
		app->data = freeMatrixString(app->data, app->rows);

	app->state = 0;
	app->rows = 8;
	app->rowsWithData = 8;
	app->columns = 8;
	app->columnsWithData = 8;
    setOption(menuApp, 0);

	app->data = createMatrixString(app->data, app->rows, app->columns);
}



static void exitApp(DataShell app, Menu menuApp){
    puts("EXIT APP THANKS FOR COMMING =)");

    app->data = freeMatrixString(app->data, app->rows);

   
    menuApp = freeMenu(menuApp);
    app = freeDataShell(app);
    exit(ERROR_OK);
}



static void reprintData(DataShell app){

    if(app->state == 0 || app->state == 1 || app->state == 3)
        printHeader();
    else if(app->state == 2)
        printData(app);
}



static void printData(DataShell app){

	system("clear");
    printf("\t\t\t\t########%s#############\n\n",app->fileName);
   
    ft_table_t *table = ft_create_table();
	ft_set_border_style(table, FT_DOUBLE2_STYLE);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    for(size_t rows = 0; rows < app->rowsWithData; rows++){
    
        ft_row_write_ln(table, app->columnsWithData, app->data[rows]);
        ft_set_cell_prop(table, FT_ANY_ROW, rows, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    }

    printf("%s\n", ft_to_string(table));

    ft_destroy_table(table);
    printf("\n\n\n");
}


static void changeColor(DataShell app, int option){
    
     const char* configListColors[] = { "\x1B[0m",  "\x1B[31m", "\x1B[32m"};

     printf("%s", configListColors[option]);
    
}


