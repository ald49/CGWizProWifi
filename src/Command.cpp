#include <Command.h>

int Commandnr = 1;
JsonDocument docCommand;
JsonArray commands = docCommand["commands"].to<JsonArray>();

void addCommand(JsonDocument doc)
{
    JsonObject commandsvalue = commands.add<JsonObject>();
    commandsvalue["id"] = Commandnr;
    commandsvalue["Unit"] = doc["Unit"];
    commandsvalue["Command"] = doc["Command"];
    commandsvalue["Value"] = doc["Value"];
    commandsvalue["Time"] = millis();
    Commandnr += 1;
}

JsonDocument getCommand(JsonDocument doc)
{
    JsonDocument Returndoc;
    for (JsonArray::iterator it = commands.begin(); it != commands.end(); ++it)
    {
        if ((*it)["Unit"] == doc["Unit"])
        {
            Returndoc = (*it);
            break;
        }
    }
    return Returndoc;
}

void deleteCommand(int id)
{
    for (JsonArray::iterator it = commands.begin(); it != commands.end(); ++it)
    {
        if ((*it)["id"] == id)
        {
            commands.remove(it);
        }
    }
}
