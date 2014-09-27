signals
=======

- Signals is a lightweight C++ API to deal with digital signals.
- Signals is related to input, FSM, and related gamedev stuff.
- Signals is tiny. Header-only.
- Signals is cross-platform.
- Signals is stand-alone.
- Signals is BOOST licensed.

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

### setters API
- `set(int var, bool value)` set variable state without up/down interstates
- `transition(int var, bool value)` set variable state with up/down interstates
- `toggle(int var)` toggles variable state

### getters API
- `bool is_on(int var)` -- other aliases: `is_active(v)`,`is_enabled(v)`,`is_set(v)` 
- `bool is_off(int var)` -- other aliases: `is_inactive(v)`,`is_disabled(v)`,`is_unset(v)` 
- `bool is_up(int var)` -- other aliases: `is_triggered(v)`,`is_raised(v)`
- `bool is_down(int var)` -- other aliases: `is_released(v)`,`is_dropped(v)`
- `bool is_pushed(int var)` 
- `bool is_pushed2x(int var)` 

### shared API
- `void frame()` advance to next frame

### sample
```c++
#include <cassert>
#include "signals.hpp"
enum {
    BUTTON,
};
int main() {
    frame();
	assert( is_off(BUTTON) );

	transition( BUTTON, true );
    assert( is_up(BUTTON) );
    frame();

	assert( is_on(BUTTON) );
    frame();

	transition( BUTTON, false );
    assert( is_down(BUTTON) );
    frame();

    assert( is_off(BUTTON) );
    frame();
}
```
