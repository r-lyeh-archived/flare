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
