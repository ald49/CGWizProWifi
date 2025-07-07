#include <msg.h>

int msgnr = 1;
JsonDocument docmsg;
JsonArray msgs = docmsg["msgs"].to<JsonArray>();

void addMassage(String msgstr)
{
    JsonObject msgvalue = msgs.add<JsonObject>();
    msgvalue["id"] = msgnr;
    msgvalue["msg"] = msgstr;
    msgvalue["Time"] = millis();
    msgnr = msgnr + 1;
}

void cleanOldMsg()
{
    for (JsonArray::iterator it = msgs.begin(); it != msgs.end(); ++it)
    {
        int deltime = ((*it)["Time"]);
        deltime = deltime + 10000;
        if (deltime < millis())
        {
            // msgs.remove(it);
        }
    }
}

void deleteMsg(int id)
{

    for (JsonArray::iterator it = msgs.begin(); it != msgs.end(); ++it)
    {
        if ((*it)["id"] == id)
        {
            msgs.remove(it);
        }
    }
}