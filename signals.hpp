// simple logic for signals
// - rlyeh, BOOST licensed

/*
    digital signals (~logic buttons) (~quadbools)

        | |__________| |
     ___|/|          |\|______
      1 |2|    3     |4|  5

    1 = off  (also false, disabled, low, idle, unset, inactive)
    2 = up   (also trigger, enable, raise)
    3 = on   (also true, enabled, high, hold, set, active)
    4 = down (also release, disable, drop)
    5 = off
*/

#pragma once

#include <bitset>
#include <deque>

struct signals {
    using bitset = std::bitset<16384>;
    using bitsets = std::deque<bitset>;

    static bitsets &any() {
        static bitsets bs(5);
        return bs;
    }

    static bool check(int t, bool then, bool now) {
        auto &any = signals::any();
        return any[1][t] == then && any[0][t] == now;
    }
    static bool check(int t, bool before, bool then, bool now) {
        auto &any = signals::any();
        return any[2][t] == before && any[1][t] == then && any[0][t] == now;
    }
    static bool check(int t, bool state_a, bool state_b, bool state_c, bool state_d, bool state_e) {
        auto &any = signals::any();
        return any[4][t] == state_a && any[3][t] == state_b && any[2][t] == state_c && any[1][t] == state_d && any[0][t] == state_e;
    }
};

namespace {
    // setters
    static inline void set( int t ) { // quick, without up/down interstates
        auto &then = signals::any()[1][t], &now = signals::any()[0][t];
        then = ( now = now ^ true );
    }
    static inline void transition( int t, bool value ) { // complete, with up/down interstates
        signals::any().front()[t] = value;
    }
    static inline void toggle( int t ) {
        auto &now = signals::any()[0][t];
        now = now ^ true;
    }

    // getters
    static inline bool is_off( int t ) {
        return signals::check(t,0,0);
    }
    static inline bool is_up( int t ) {
        return signals::check(t,0,1);
    }
    static inline bool is_on( int t ) {
        return signals::check(t,1,1);
    }
    static inline bool is_down( int t ) {
        return signals::check(t,1,0);
    }

    static inline bool is_pushed( int t ) {
        return signals::check(t,0,1,0);
    }
    static inline bool is_pushed2x( int t ) {
        return signals::check(t,0,1,0,1,0);
    }

    // frame advance
    static inline void frame() {
        auto &any = signals::any();
        any.push_front( any.front() );
        any.pop_back();
    }
}

/* getter aliases */

#define is_active(x)    is_on(x)
#define is_enabled(x)   is_on(x)
#define is_set(x)       is_on(x)

#define is_inactive(x)  is_off(x)
#define is_disabled(x)  is_off(x)
#define is_unset(x)     is_off(x)

#define is_triggered(x) is_up(x)
#define is_raised(x)    is_up(x)

#define is_released(x)  is_down(x)
#define is_dropped(x)   is_down(x)

