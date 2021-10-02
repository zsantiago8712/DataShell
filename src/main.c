
#include "../libs/DataShell.h"

int main(void){
 

    DataShell app = NULL;
    Menu menuApp = NULL;

    app = initDataShell();
    menuApp = initMenu();


    while(1){
        
        setMenuList(menuApp, getState(app));
        selectOption(app, menuApp);

		clearBuffer();
        controller(app, menuApp);
    }

      
}
