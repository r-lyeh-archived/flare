#include "flare.hpp"

enum {
    BUTTON,
};

int main() {
                      // is_up(BUTTON) is_on(BUTTON) is_down(BUTTON) is_off(BUTTON) 
                      //      0             0               0              1        
    set( BUTTON );    //      1             0               0              0        
    frame();          //      0             1               0              0        
    frame();          //      0             1               0              0        
    toggle( BUTTON ); //      0             0               1              0        
    frame();          //      0             0               0              1        
    frame();          //      0             0               0              1        
    clear( BUTTON );  //      0             0               0              1        
    frame();          //      0             0               0              1        
    frame();          //      0             0               0              1        
}
