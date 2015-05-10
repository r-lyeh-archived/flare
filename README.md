flare <a href="https://travis-ci.org/r-lyeh/flare"><img src="https://api.travis-ci.org/r-lyeh/flare.svg?branch=master" align="right" /></a>
=====

- Flare is a lightweight C++ API to deal with digital signals/logical buttons.
- Flare is related to input, FSM, gameplay logic and other gamedev stuff.
- Flare is tiny. Header-only.
- Flare is cross-platform.
- Flare is stand-alone.
- Flare is zlib/libpng licensed.

### some theory
```
    digital signals (~logic buttons) (~quadbools)

        | |__________| |
     ___|/|          |\|______
      1 |2|    3     |4|  5

    1 = off  (also false, disabled, low, idle, unset, inactive)
    2 = up   (also trigger, enable, raise)
    3 = on   (also true, enabled, high, hold, set, active)
    4 = down (also release, disable, drop)
    5 = off
```

### immediate API, no up/down interstates
```c++
// getter
bool get( int var );
// setter
void set( int var, bool value );
```

### transitional API, featuring up/down interstates
```c++
// getters
bool is_off( int var );   // aliases: is_inactive(v), is_disabled(v), is_unset(v) 
bool is_up( int var );    // aliases: is_triggered(v), is_raised(v)
bool is_on( int var );    // aliases: is_active(v), is_enabled(v), is_set(v) 
bool is_down( int var );  // aliases: is_released(v), is_dropped(v)
bool is_push( int var );
bool is_push2x( int var );
// setters
void set( int var );
void clear( int var );
void toggle( int var );
```

### shared API
```c++
// update all signals and get ready for next frame
void frame();
```

### sample
```c++
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
```
