const int sendDelay = 1000 * 60;
const int readDelay = 1000 * 1;

const int morningCuttOff = 10;
const int nightCuttOff = 20;

const float lowLightCutOff = 0.2;
const float highLightCutOff = 0.9;
const float moistureCutOff = 12;
const bool verbose = true;

const float smoothingFactor = 0.7;

Ewma co2(smoothingFactor);
Ewma tvoc(smoothingFactor);
Ewma moisture(smoothingFactor);
Ewma lux(smoothingFactor);
Ewma temp(smoothingFactor);
Ewma humid(smoothingFactor);

bool pumpsState = false;
bool statusState = false;
bool lightsState = false;
bool LDRState = false;
bool fanState = false;