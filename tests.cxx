#include <cassert>
#include <iostream>
#include "signals.hpp"

enum {
    MY_FLAG,
};

int main() {
    frame();
    assert(  is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    transition( MY_FLAG, true );
    assert( !is_off(MY_FLAG) );
    assert(  is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    transition( MY_FLAG, true );
    assert( !is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert(  is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    transition( MY_FLAG, false );
    assert( !is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert(  is_down(MY_FLAG) );

    frame();
    transition( MY_FLAG, false );
    assert(  is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    transition( MY_FLAG, false );
    assert(  is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    toggle( MY_FLAG );
    assert( !is_off(MY_FLAG) );
    assert(  is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    assert( !is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert(  is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    frame();
    set( MY_FLAG );
    assert(  is_off(MY_FLAG) );
    assert( !is_up(MY_FLAG) );
    assert( !is_on(MY_FLAG) );
    assert( !is_down(MY_FLAG) );

    std::cout << "All ok." << std::endl;
}
