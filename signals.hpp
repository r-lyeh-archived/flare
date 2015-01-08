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

// immediate API, no up/down interstates
namespace {
    // getter
    static inline bool get( int t ) {              
        return signals::any()[0][t];
    }
    // setter
    static inline void set( int t, bool value ) {
        signals::any()[1][t] = value;
        signals::any()[0][t] = value;
    }
}

// transitional API, featuring up/down interstates
namespace {
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

    static inline bool is_push( int t ) {
        return signals::check(t,0,1,0);
    }
    static inline bool is_push2x( int t ) {
        return signals::check(t,0,1,0,1,0);
    }

    // aliases for getters
    static bool (&is_unset)( int t ) =     is_off;
    static bool (&is_inactive)( int t ) =  is_off;
    static bool (&is_disabled)( int t ) =  is_off;

    static bool (&is_raised)( int t ) =    is_up;
    static bool (&is_triggered)( int t ) = is_up;

    static bool (&is_set)( int t ) =       is_on;
    static bool (&is_active)( int t ) =    is_on;
    static bool (&is_enabled)( int t ) =   is_on;

    static bool (&is_dropped)( int t ) =   is_down;
    static bool (&is_released)( int t ) =  is_down;

    // setters
    static inline void clear( int t ) {
        signals::any()[0][t] = 0;
    }
    static inline void set( int t ) {
        signals::any()[0][t] = 1;
    }
    static inline void toggle( int t ) {
        auto &now = signals::any()[0][t];
        now = now ^ true;
    }
}

// shared API
namespace {
    // frame advance
    static inline void frame() {
        auto &any = signals::any();
        any.push_front( any.front() );
        any.pop_back();
    }
}
