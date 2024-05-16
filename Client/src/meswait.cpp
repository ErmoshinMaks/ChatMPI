#include "meswait.h" 

void MessageWaiter::emit_signal()
{
    emit checkMes();
}