#include "reqHandler.h"

ReqHandler::ReqHandler()
{
    m_pool.start();
}

ReqHandler::~ReqHandler()
{
    m_pool.stop();
}