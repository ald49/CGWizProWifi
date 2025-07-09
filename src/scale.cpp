#include <scale.h>


int NumberOfLoadcells = 3;

float LoadValue[3];
float loadMoment[3];
float TotalWeight = 0;
float lrdiff = 0;
long long int LoadCellId[3] = {342628709630718180, 3226339846031388900, 342628709630718170};

float cg = 0;
boolean loadcells_rdy[4];

float CalcCG();



boolean CheckLoadCell(HX711_ADC LoadCell_Local, int LoadCellNumber)
{
    boolean loadcell_rdy = false;
    if (LoadCell_Local.getTareTimeoutFlag())
    {
        if (LoadCellNumber != 0)
        {
            Serial.println("Timeout, check MCU>HX711 no." + String(LoadCellNumber) + " wiring and pin designations");
        }
        loadcell_rdy = false;
    }
    return loadcell_rdy;
}

void update(JsonDocument jaondata)
{
    for (int i = 0; i < sizeof(LoadCellId) / sizeof(LoadCellId[0]); i++)
    {
        long long int Unit = jaondata["Unit"];

        if (Unit == LoadCellId[i])
        {
            LoadValue[i] = jaondata["loadvalue"];
        }
    }
    CalcCG();
}

boolean setscaletar()
{
    Serial.println("Start Tare");
    // addMassage("Starting Tare");
    for (int i = 0; i < sizeof(LoadCellId) / sizeof(LoadCellId[0]); i++)
    {
        JsonDocument doc;
        doc["Unit"] = LoadCellId[i];
        doc["Command"] = "Tar";
        addCommand(doc);
        // LoadCells[i].tareNoDelay();
    }

    return true;
}

boolean setscaletar(int id)
{
    Serial.println("Start Tare LoadCell " + String(id));
    // addMassage("Starting Tare");

    JsonDocument doc;
    doc["Unit"] = LoadCellId[id];
    doc["Command"] = "Tar";
    addCommand(doc);

    return true;
}

JsonDocument getscaledata()
{
    JsonDocument doc;

    doc["cg"] = cg;
    doc["L0L2diff"] = lrdiff;
    doc["TotalWeight"] = TotalWeight;
    JsonArray models = doc["scalevalues"].to<JsonArray>();
    for (int i = 0; i <= NumberOfLoadcells - 1; i++)
    {
        JsonObject scalevalue = models.add<JsonObject>();
        scalevalue["id"] = i;
        scalevalue["weight"] = LoadValue[i];
        scalevalue["loadMoment"] = loadMoment[i];
    }
    return doc;
}

boolean setCalibrationscalet(int id, JsonDocument jsono)
{
    float knownmass = jsono["knownmass"];
    JsonDocument doc;
    doc["Unit"] = LoadCellId[id];
    doc["Command"] = "Calibration";
    doc["Value"] = knownmass;
    addCommand(doc);

    return true;
}

float CalcCG()
{
    TotalWeight = 0;
    for (int i = 0; i < NumberOfLoadcells; i++)
    {
        TotalWeight += LoadValue[i];
    }
    switch (NumberOfLoadcells)
    {
    case 2:
        cg = (((LoadValue[0] * distance[0])) + ((LoadValue[1] * distance[1]))) / TotalWeight;
        lrdiff = 0;
        break;
    case 3:
        cg = (((LoadValue[0] * distance[0]) + (LoadValue[2] * distance[0])) + ((LoadValue[1] * distance[1]))) / TotalWeight;
        lrdiff = ((LoadValue[0] * distance[2]) - (LoadValue[2] * distance[2])) / (LoadValue[0] + LoadValue[2]);
        break;
    }

    return cg;
}
