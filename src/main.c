
#include "../libs/DataShell.h"

int main(void){
 

    DataShell app = NULL;
    Menu menuApp = NULL;
    Config configApp = NULL;

    configApp = initConfig();    
    app = initDataShell();
    menuApp = initMenu();

    configureApp(configApp);

    while(1){
        
        setMenuList(menuApp, getState(app));
        selectOption(app, menuApp);

		clearBuffer();
        controller(app, menuApp);
    }

      
}
