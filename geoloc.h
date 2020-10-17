#ifndef geoloc_h
#define geoloc_h
#include "string.h"
class geoloc
{
  public:
    geoloc(void);
    void begin(const char*, const char*);
    String publicIP(void);
    String geocordinates(void);
};

#endif

