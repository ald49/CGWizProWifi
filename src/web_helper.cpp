#include <web_helper.h>

String GetUrlVarable(String url)
{
  int urlParmStart = url.lastIndexOf("/") + 1;

  return url.substring(urlParmStart, url.length());
}