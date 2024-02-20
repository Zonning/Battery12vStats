
#include <Arduino.h>
#include <Battery12vStats.h>

//Internal ADC

BatteryStatsInternal::BatteryStatsInternal(int adcPin, int reads) {
  _reads = reads;
  _adcPin = adcPin;
}


BatteryStatsInternal::BatteryStatsInternal(int adcPin) {
  _reads = DEFAULT_READS;
  _adcPin = adcPin;
}

BatteryStatsInternal::BatteryStatsInternal() {
  _reads = DEFAULT_READS;
  _adcPin = DEFAULT_PIN;
}

BatteryStatsInternal::~BatteryStatsInternal() {
  free(_conversionTable);
  delete this->_conversionTable;
}

double BatteryStatsInternal::getBatteryVolts() {
  int readValue = _avgAnalogRead(_adcPin, _reads);
  return _analogReadToVolts(readValue);
}

int BatteryStatsInternal::getBatteryChargeLevel() {
  int readValue = _avgAnalogRead(_adcPin, _reads);
  double volts = _analogReadToVolts(readValue);

if (BATTTYPE == 1){ //Lead Acid
  if (volts >= 12.80) {
    return 100;
  }
  if (volts <= 10.50) {
    return 0;
  }
}
if (BATTTYPE == 2){ //AGM
  if (volts >= 12.90) {
    return 100;
  }
  if (volts <= 10.70) {
    return 0;
  }
}
if (BATTTYPE == 3){ //GEL
  if (volts >= 13.00) {
    return 100;
  }
  if (volts <= 10.80) {
    return 0;
  }
}
if (BATTTYPE == 4){ //LIFEPO4
  if (volts >= 13.60) {
    return 100;
  }
  if (volts <= 10.00) {
    return 0;
  }
}
if (BATTTYPE == 5){ //CUSTOM
  if (volts >= 12.80) {
    return 100;
  }
  if (volts <= 10.50) {
    return 0;
  }
}

  return _getChargeLevelFromConversionTable(volts);
}


void BatteryStatsInternal::_initConversionTable()
{
  if(BATTTYPE == 1){
  _conversionTable = (double*)malloc(sizeof(double)*101); //Lead Acid
  _conversionTable[0] = 10.500;
  _conversionTable[1] = 10.580;  _conversionTable[2] = 10.660; _conversionTable[3] = 10.740; _conversionTable[4] = 10.820; _conversionTable[5] = 10.900;
  _conversionTable[6] = 10.980; _conversionTable[7] = 11.060; _conversionTable[8] = 11.140; _conversionTable[9] = 11.220; _conversionTable[10] = 11.300;
  _conversionTable[11] = 11.330; _conversionTable[12] = 11.360; _conversionTable[13] = 11.390; _conversionTable[14] = 11.420; _conversionTable[15] = 11.450;
  _conversionTable[16] = 11.480; _conversionTable[17] = 11.510; _conversionTable[18] = 11.540; _conversionTable[19] = 11.570; _conversionTable[20] = 11.600;
  _conversionTable[21] = 11.620; _conversionTable[22] = 11.640; _conversionTable[23] = 11.660; _conversionTable[24] = 11.680; _conversionTable[25] = 11.700;
  _conversionTable[26] = 11.720; _conversionTable[27] = 11.740; _conversionTable[28] = 11.760; _conversionTable[29] = 11.780; _conversionTable[30] = 11.800;
  _conversionTable[31] = 11.810; _conversionTable[32] = 11.820; _conversionTable[33] = 11.830; _conversionTable[34] = 11.840; _conversionTable[35] = 11.850;
  _conversionTable[36] = 11.860; _conversionTable[37] = 11.870; _conversionTable[38] = 11.880; _conversionTable[39] = 11.890; _conversionTable[40] = 11.900;
  _conversionTable[41] = 11.920; _conversionTable[42] = 11.940; _conversionTable[43] = 11.960; _conversionTable[44] = 11.980; _conversionTable[45] = 12.000;
  _conversionTable[46] = 12.020; _conversionTable[47] = 12.040; _conversionTable[48] = 12.060; _conversionTable[49] = 12.080; _conversionTable[50] = 12.100;
  _conversionTable[51] = 12.110; _conversionTable[52] = 12.120; _conversionTable[53] = 12.130; _conversionTable[54] = 12.140; _conversionTable[55] = 12.150;
  _conversionTable[56] = 12.160; _conversionTable[57] = 12.170; _conversionTable[58] = 12.180; _conversionTable[59] = 12.190; _conversionTable[60] = 12.200;
  _conversionTable[61] = 12.210; _conversionTable[62] = 12.220; _conversionTable[63] = 12.230; _conversionTable[64] = 12.240; _conversionTable[65] = 12.250;
  _conversionTable[66] = 12.260; _conversionTable[67] = 12.270; _conversionTable[68] = 12.280; _conversionTable[69] = 12.290; _conversionTable[70] = 12.300;
  _conversionTable[71] = 12.310; _conversionTable[72] = 12.320; _conversionTable[73] = 12.330; _conversionTable[74] = 12.340; _conversionTable[75] = 12.350;
  _conversionTable[76] = 12.360; _conversionTable[77] = 12.370; _conversionTable[78] = 12.380; _conversionTable[79] = 12.390; _conversionTable[80] = 12.400;
  _conversionTable[81] = 12.410; _conversionTable[82] = 12.420; _conversionTable[83] = 12.430; _conversionTable[84] = 12.440; _conversionTable[85] = 12.450;
  _conversionTable[86] = 12.460; _conversionTable[87] = 12.470; _conversionTable[88] = 12.480; _conversionTable[89] = 12.490; _conversionTable[90] = 12.500;
  _conversionTable[91] = 12.520; _conversionTable[92] = 12.540; _conversionTable[93] = 12.560; _conversionTable[94] = 12.580; _conversionTable[95] = 12.600;
  _conversionTable[96] = 12.620; _conversionTable[97] = 12.640; _conversionTable[98] = 12.660; _conversionTable[99] = 12.680; _conversionTable[100] = 12.700;
  }


  if(BATTTYPE == 2){
  _conversionTable = (double*)malloc(sizeof(double)*101); //AGM
  _conversionTable[0] = 10.700;
  _conversionTable[1] = 10.780;  _conversionTable[2] = 10.860; _conversionTable[3] = 10.940; _conversionTable[4] = 11.020; _conversionTable[5] = 11.100;
  _conversionTable[6] = 11.180; _conversionTable[7] = 11.260; _conversionTable[8] = 11.340; _conversionTable[9] = 11.420; _conversionTable[10] = 11.500;
  _conversionTable[11] = 11.520; _conversionTable[12] = 11.540; _conversionTable[13] = 11.560; _conversionTable[14] = 11.580; _conversionTable[15] = 11.600;
  _conversionTable[16] = 11.620; _conversionTable[17] = 11.640; _conversionTable[18] = 11.660; _conversionTable[19] = 11.680; _conversionTable[20] = 11.700;
  _conversionTable[21] = 11.720; _conversionTable[22] = 11.740; _conversionTable[23] = 11.760; _conversionTable[24] = 11.780; _conversionTable[25] = 11.800;
  _conversionTable[26] = 11.820; _conversionTable[27] = 11.840; _conversionTable[28] = 11.860; _conversionTable[29] = 11.880; _conversionTable[30] = 11.900;
  _conversionTable[31] = 11.910; _conversionTable[32] = 11.920; _conversionTable[33] = 11.930; _conversionTable[34] = 11.940; _conversionTable[35] = 11.950;
  _conversionTable[36] = 11.960; _conversionTable[37] = 11.970; _conversionTable[38] = 11.980; _conversionTable[39] = 11.990; _conversionTable[40] = 12.000;
  _conversionTable[41] = 12.020; _conversionTable[42] = 12.040; _conversionTable[43] = 12.060; _conversionTable[44] = 12.080; _conversionTable[45] = 12.100;
  _conversionTable[46] = 12.120; _conversionTable[47] = 12.140; _conversionTable[48] = 12.160; _conversionTable[49] = 12.180; _conversionTable[50] = 12.200;
  _conversionTable[51] = 12.210; _conversionTable[52] = 12.220; _conversionTable[53] = 12.230; _conversionTable[54] = 12.240; _conversionTable[55] = 12.250;
  _conversionTable[56] = 12.260; _conversionTable[57] = 12.270; _conversionTable[58] = 12.280; _conversionTable[59] = 12.290; _conversionTable[60] = 12.300;
  _conversionTable[61] = 12.310; _conversionTable[62] = 12.320; _conversionTable[63] = 12.330; _conversionTable[64] = 12.340; _conversionTable[65] = 12.350;
  _conversionTable[66] = 12.360; _conversionTable[67] = 12.370; _conversionTable[68] = 12.380; _conversionTable[69] = 12.390; _conversionTable[70] = 12.400;
  _conversionTable[71] = 12.420; _conversionTable[72] = 12.440; _conversionTable[73] = 12.460; _conversionTable[74] = 12.480; _conversionTable[75] = 12.500;
  _conversionTable[76] = 12.520; _conversionTable[77] = 12.540; _conversionTable[78] = 12.560; _conversionTable[79] = 12.580; _conversionTable[80] = 12.600;
  _conversionTable[81] = 12.610; _conversionTable[82] = 12.620; _conversionTable[83] = 12.630; _conversionTable[84] = 12.640; _conversionTable[85] = 12.650;
  _conversionTable[86] = 12.660; _conversionTable[87] = 12.670; _conversionTable[88] = 12.680; _conversionTable[89] = 12.690; _conversionTable[90] = 12.700;
  _conversionTable[91] = 12.720; _conversionTable[92] = 12.740; _conversionTable[93] = 12.760; _conversionTable[94] = 12.780; _conversionTable[95] = 12.800;
  _conversionTable[96] = 12.820; _conversionTable[97] = 12.840; _conversionTable[98] = 12.860; _conversionTable[99] = 12.880; _conversionTable[100] = 12.900;
  }


  if(BATTTYPE == 3){
  _conversionTable = (double*)malloc(sizeof(double)*101); //GEL
  _conversionTable[0] = 10.800;
  _conversionTable[1] = 10.880;  _conversionTable[2] = 10.960; _conversionTable[3] = 11.040; _conversionTable[4] = 11.120; _conversionTable[5] = 11.200;
  _conversionTable[6] = 11.280; _conversionTable[7] = 11.360; _conversionTable[8] = 11.440; _conversionTable[9] = 11.520; _conversionTable[10] = 11.600;
  _conversionTable[11] = 11.620; _conversionTable[12] = 11.640; _conversionTable[13] = 11.660; _conversionTable[14] = 11.680; _conversionTable[15] = 11.700;
  _conversionTable[16] = 11.720; _conversionTable[17] = 11.740; _conversionTable[18] = 11.760; _conversionTable[19] = 11.780; _conversionTable[20] = 11.800;
  _conversionTable[21] = 11.830; _conversionTable[22] = 11.860; _conversionTable[23] = 11.890; _conversionTable[24] = 11.920; _conversionTable[25] = 11.950;
  _conversionTable[26] = 11.980; _conversionTable[27] = 12.010; _conversionTable[28] = 12.040; _conversionTable[29] = 12.070; _conversionTable[30] = 12.100;
  _conversionTable[31] = 12.110; _conversionTable[32] = 12.120; _conversionTable[33] = 12.130; _conversionTable[34] = 12.140; _conversionTable[35] = 12.150;
  _conversionTable[36] = 12.160; _conversionTable[37] = 12.170; _conversionTable[38] = 12.180; _conversionTable[39] = 12.190; _conversionTable[40] = 12.200;
  _conversionTable[41] = 12.210; _conversionTable[42] = 12.220; _conversionTable[43] = 12.230; _conversionTable[44] = 12.240; _conversionTable[45] = 12.250;
  _conversionTable[46] = 12.260; _conversionTable[47] = 12.270; _conversionTable[48] = 12.280; _conversionTable[49] = 12.290; _conversionTable[50] = 12.300;
  _conversionTable[51] = 12.310; _conversionTable[52] = 12.320; _conversionTable[53] = 12.330; _conversionTable[54] = 12.340; _conversionTable[55] = 12.350;
  _conversionTable[56] = 12.360; _conversionTable[57] = 12.370; _conversionTable[58] = 12.380; _conversionTable[59] = 12.390; _conversionTable[60] = 12.400;
  _conversionTable[61] = 12.410; _conversionTable[62] = 12.420; _conversionTable[63] = 12.430; _conversionTable[64] = 12.440; _conversionTable[65] = 12.450;
  _conversionTable[66] = 12.460; _conversionTable[67] = 12.470; _conversionTable[68] = 12.480; _conversionTable[69] = 12.490; _conversionTable[70] = 12.500;
  _conversionTable[71] = 12.520; _conversionTable[72] = 12.540; _conversionTable[73] = 12.560; _conversionTable[74] = 12.580; _conversionTable[75] = 12.600;
  _conversionTable[76] = 12.620; _conversionTable[77] = 12.640; _conversionTable[78] = 12.660; _conversionTable[79] = 12.680; _conversionTable[80] = 12.700;
  _conversionTable[81] = 12.710; _conversionTable[82] = 12.720; _conversionTable[83] = 12.730; _conversionTable[84] = 12.740; _conversionTable[85] = 12.750;
  _conversionTable[86] = 12.760; _conversionTable[87] = 12.770; _conversionTable[88] = 12.780; _conversionTable[89] = 12.790; _conversionTable[90] = 12.800;
  _conversionTable[91] = 12.820; _conversionTable[92] = 12.840; _conversionTable[93] = 12.860; _conversionTable[94] = 12.880; _conversionTable[95] = 12.900;
  _conversionTable[96] = 12.920; _conversionTable[97] = 12.940; _conversionTable[98] = 12.960; _conversionTable[99] = 12.980; _conversionTable[100] = 13.000;
  }


  if(BATTTYPE == 4){
  _conversionTable = (double*)malloc(sizeof(double)*101); //LIFEPO4
  _conversionTable[0] = 10.000;
  _conversionTable[1] = 10.200;  _conversionTable[2] = 10.400; _conversionTable[3] = 10.600; _conversionTable[4] = 10.800; _conversionTable[5] = 11.000;
  _conversionTable[6] = 11.200; _conversionTable[7] = 11.400; _conversionTable[8] = 11.600; _conversionTable[9] = 11.800; _conversionTable[10] = 12.000;
  _conversionTable[11] = 12.080; _conversionTable[12] = 12.160; _conversionTable[13] = 12.240; _conversionTable[14] = 12.320; _conversionTable[15] = 12.400;
  _conversionTable[16] = 12.480; _conversionTable[17] = 12.560; _conversionTable[18] = 12.640; _conversionTable[19] = 12.720; _conversionTable[20] = 12.800;
  _conversionTable[21] = 12.810; _conversionTable[22] = 12.820; _conversionTable[23] = 12.830; _conversionTable[24] = 12.840; _conversionTable[25] = 12.850;
  _conversionTable[26] = 12.860; _conversionTable[27] = 12.870; _conversionTable[28] = 12.880; _conversionTable[29] = 12.890; _conversionTable[30] = 12.900;
  _conversionTable[31] = 12.905; _conversionTable[32] = 12.910; _conversionTable[33] = 12.915; _conversionTable[34] = 12.920; _conversionTable[35] = 12.925;
  _conversionTable[36] = 12.930; _conversionTable[37] = 12.935; _conversionTable[38] = 12.940; _conversionTable[39] = 12.945; _conversionTable[40] = 12.950;
  _conversionTable[41] = 12.955; _conversionTable[42] = 12.960; _conversionTable[43] = 12.965; _conversionTable[44] = 12.970; _conversionTable[45] = 12.975;
  _conversionTable[46] = 12.980; _conversionTable[47] = 12.985; _conversionTable[48] = 12.990; _conversionTable[49] = 12.995; _conversionTable[50] = 13.000;
  _conversionTable[51] = 13.010; _conversionTable[52] = 13.020; _conversionTable[53] = 13.030; _conversionTable[54] = 13.040; _conversionTable[55] = 13.050;
  _conversionTable[56] = 13.060; _conversionTable[57] = 13.070; _conversionTable[58] = 13.080; _conversionTable[59] = 13.090; _conversionTable[60] = 13.100;
  _conversionTable[61] = 13.110; _conversionTable[62] = 13.120; _conversionTable[63] = 13.130; _conversionTable[64] = 13.140; _conversionTable[65] = 13.150;
  _conversionTable[66] = 13.160; _conversionTable[67] = 13.170; _conversionTable[68] = 13.180; _conversionTable[69] = 13.190; _conversionTable[70] = 13.200;
  _conversionTable[71] = 13.210; _conversionTable[72] = 13.220; _conversionTable[73] = 13.230; _conversionTable[74] = 13.240; _conversionTable[75] = 13.250;
  _conversionTable[76] = 13.260; _conversionTable[77] = 13.270; _conversionTable[78] = 13.280; _conversionTable[79] = 13.290; _conversionTable[80] = 13.300;
  _conversionTable[81] = 13.310; _conversionTable[82] = 13.320; _conversionTable[83] = 13.330; _conversionTable[84] = 13.340; _conversionTable[85] = 13.350;
  _conversionTable[86] = 13.360; _conversionTable[87] = 13.370; _conversionTable[88] = 13.380; _conversionTable[89] = 13.390; _conversionTable[90] = 13.400;
  _conversionTable[91] = 13.420; _conversionTable[92] = 13.440; _conversionTable[93] = 13.460; _conversionTable[94] = 13.480; _conversionTable[95] = 13.500;
  _conversionTable[96] = 13.520; _conversionTable[97] = 13.540; _conversionTable[98] = 13.560; _conversionTable[99] = 13.580; _conversionTable[100] = 13.600;
  }


  if(BATTTYPE == 5){
  _conversionTable = (double*)malloc(sizeof(double)*101); //CUSTOM
  _conversionTable[0] = 10.500;
  _conversionTable[1] = 10.580;  _conversionTable[2] = 10.660; _conversionTable[3] = 10.740; _conversionTable[4] = 10.820; _conversionTable[5] = 10.900;
  _conversionTable[6] = 10.980; _conversionTable[7] = 11.060; _conversionTable[8] = 11.140; _conversionTable[9] = 11.220; _conversionTable[10] = 11.300;
  _conversionTable[11] = 11.330; _conversionTable[12] = 11.360; _conversionTable[13] = 11.390; _conversionTable[14] = 11.420; _conversionTable[15] = 11.450;
  _conversionTable[16] = 11.480; _conversionTable[17] = 11.510; _conversionTable[18] = 11.540; _conversionTable[19] = 11.570; _conversionTable[20] = 11.600;
  _conversionTable[21] = 11.620; _conversionTable[22] = 11.640; _conversionTable[23] = 11.660; _conversionTable[24] = 11.680; _conversionTable[25] = 11.700;
  _conversionTable[26] = 11.720; _conversionTable[27] = 11.740; _conversionTable[28] = 11.760; _conversionTable[29] = 11.780; _conversionTable[30] = 11.800;
  _conversionTable[31] = 11.810; _conversionTable[32] = 11.820; _conversionTable[33] = 11.830; _conversionTable[34] = 11.840; _conversionTable[35] = 11.850;
  _conversionTable[36] = 11.860; _conversionTable[37] = 11.870; _conversionTable[38] = 11.880; _conversionTable[39] = 11.890; _conversionTable[40] = 11.900;
  _conversionTable[41] = 11.920; _conversionTable[42] = 11.940; _conversionTable[43] = 11.960; _conversionTable[44] = 11.980; _conversionTable[45] = 12.000;
  _conversionTable[46] = 12.020; _conversionTable[47] = 12.040; _conversionTable[48] = 12.060; _conversionTable[49] = 12.080; _conversionTable[50] = 12.100;
  _conversionTable[51] = 12.110; _conversionTable[52] = 12.120; _conversionTable[53] = 12.130; _conversionTable[54] = 12.140; _conversionTable[55] = 12.150;
  _conversionTable[56] = 12.160; _conversionTable[57] = 12.170; _conversionTable[58] = 12.180; _conversionTable[59] = 12.190; _conversionTable[60] = 12.200;
  _conversionTable[61] = 12.210; _conversionTable[62] = 12.220; _conversionTable[63] = 12.230; _conversionTable[64] = 12.240; _conversionTable[65] = 12.250;
  _conversionTable[66] = 12.260; _conversionTable[67] = 12.270; _conversionTable[68] = 12.280; _conversionTable[69] = 12.290; _conversionTable[70] = 12.300;
  _conversionTable[71] = 12.310; _conversionTable[72] = 12.320; _conversionTable[73] = 12.330; _conversionTable[74] = 12.340; _conversionTable[75] = 12.350;
  _conversionTable[76] = 12.360; _conversionTable[77] = 12.370; _conversionTable[78] = 12.380; _conversionTable[79] = 12.390; _conversionTable[80] = 12.400;
  _conversionTable[81] = 12.410; _conversionTable[82] = 12.420; _conversionTable[83] = 12.430; _conversionTable[84] = 12.440; _conversionTable[85] = 12.450;
  _conversionTable[86] = 12.460; _conversionTable[87] = 12.470; _conversionTable[88] = 12.480; _conversionTable[89] = 12.490; _conversionTable[90] = 12.500;
  _conversionTable[91] = 12.520; _conversionTable[92] = 12.540; _conversionTable[93] = 12.560; _conversionTable[94] = 12.580; _conversionTable[95] = 12.600;
  _conversionTable[96] = 12.620; _conversionTable[97] = 12.640; _conversionTable[98] = 12.660; _conversionTable[99] = 12.680; _conversionTable[100] = 12.700;
  }
}



int BatteryStatsInternal::_avgAnalogRead(int pinNumber, int reads) {
  int totalValue = 0;
  for (int i = 0; i < reads; i++) {
    totalValue += analogRead(pinNumber);
  }
  return (int) (totalValue / reads);
}

int BatteryStatsInternal::_getChargeLevelFromConversionTable(double volts) {
  if (_conversionTable == nullptr) {
    _initConversionTable();
  }

  int index = 50;
  int previousIndex = 0;
  int half = 0;

  while(previousIndex != index) {
    half = abs(index - previousIndex) / 2;
    previousIndex = index;
    if (_conversionTable[index] == volts) {
      return index;
    }
    index = (volts >= _conversionTable[index])
       ? index + half
       : index - half;
  }

  return index;
}

double BatteryStatsInternal::_analogReadToVolts(int readValue) {
  return readValue * CONVFACTOR / 1000;
}

void BatteryStatsInternal::set_conversionFactor(double convFactor){
  CONVFACTOR = convFactor;
}

void BatteryStatsInternal::set_battType(int battType){
  BATTTYPE = battType;
  if (_conversionTable != nullptr) {
    _initConversionTable();
  }
}

double BatteryStatsInternal::get_conversionFactor(){
  return CONVFACTOR;
}

int BatteryStatsInternal::get_battType(){
  return BATTTYPE;
}


//ADS1115-----------------------------------------------------------------------------------------------------

BatteryStatsADS1115::BatteryStatsADS1115() {
}

BatteryStatsADS1115::~BatteryStatsADS1115() {
  free(_conversionTable);
  delete this->_conversionTable;
}

double BatteryStatsADS1115::getBatteryVolts() {
  int readValue = _adcValue;
  return _analogReadToVolts(readValue);
}


int BatteryStatsADS1115::getBatteryChargeLevel() {
  int readValue = _adcValue;
  double volts = _analogReadToVolts(readValue);

if (BATTTYPE == 1){ //Lead Acid
  if (volts >= 12.80) {
    return 100;
  }
  if (volts <= 10.50) {
    return 0;
  }
}
if (BATTTYPE == 2){ //AGM
  if (volts >= 12.90) {
    return 100;
  }
  if (volts <= 10.70) {
    return 0;
  }
}
if (BATTTYPE == 3){ //GEL
  if (volts >= 13.00) {
    return 100;
  }
  if (volts <= 10.80) {
    return 0;
  }
}
if (BATTTYPE == 4){ //LIFEPO4
  if (volts >= 13.60) {
    return 100;
  }
  if (volts <= 10.00) {
    return 0;
  }
}
if (BATTTYPE == 5){ //CUSTOM
  if (volts >= 12.80) {
    return 100;
  }
  if (volts <= 10.50) {
    return 0;
  }
}

  return _getChargeLevelFromConversionTable(volts);
}


void BatteryStatsADS1115::_initConversionTable()
{
  if(BATTTYPE == 1){
  _conversionTable = (double*)malloc(sizeof(double)*101); //Lead Acid
  _conversionTable[0] = 10.500;
  _conversionTable[1] = 10.580;  _conversionTable[2] = 10.660; _conversionTable[3] = 10.740; _conversionTable[4] = 10.820; _conversionTable[5] = 10.900;
  _conversionTable[6] = 10.980; _conversionTable[7] = 11.060; _conversionTable[8] = 11.140; _conversionTable[9] = 11.220; _conversionTable[10] = 11.300;
  _conversionTable[11] = 11.330; _conversionTable[12] = 11.360; _conversionTable[13] = 11.390; _conversionTable[14] = 11.420; _conversionTable[15] = 11.450;
  _conversionTable[16] = 11.480; _conversionTable[17] = 11.510; _conversionTable[18] = 11.540; _conversionTable[19] = 11.570; _conversionTable[20] = 11.600;
  _conversionTable[21] = 11.620; _conversionTable[22] = 11.640; _conversionTable[23] = 11.660; _conversionTable[24] = 11.680; _conversionTable[25] = 11.700;
  _conversionTable[26] = 11.720; _conversionTable[27] = 11.740; _conversionTable[28] = 11.760; _conversionTable[29] = 11.780; _conversionTable[30] = 11.800;
  _conversionTable[31] = 11.810; _conversionTable[32] = 11.820; _conversionTable[33] = 11.830; _conversionTable[34] = 11.840; _conversionTable[35] = 11.850;
  _conversionTable[36] = 11.860; _conversionTable[37] = 11.870; _conversionTable[38] = 11.880; _conversionTable[39] = 11.890; _conversionTable[40] = 11.900;
  _conversionTable[41] = 11.920; _conversionTable[42] = 11.940; _conversionTable[43] = 11.960; _conversionTable[44] = 11.980; _conversionTable[45] = 12.000;
  _conversionTable[46] = 12.020; _conversionTable[47] = 12.040; _conversionTable[48] = 12.060; _conversionTable[49] = 12.080; _conversionTable[50] = 12.100;
  _conversionTable[51] = 12.110; _conversionTable[52] = 12.120; _conversionTable[53] = 12.130; _conversionTable[54] = 12.140; _conversionTable[55] = 12.150;
  _conversionTable[56] = 12.160; _conversionTable[57] = 12.170; _conversionTable[58] = 12.180; _conversionTable[59] = 12.190; _conversionTable[60] = 12.200;
  _conversionTable[61] = 12.210; _conversionTable[62] = 12.220; _conversionTable[63] = 12.230; _conversionTable[64] = 12.240; _conversionTable[65] = 12.250;
  _conversionTable[66] = 12.260; _conversionTable[67] = 12.270; _conversionTable[68] = 12.280; _conversionTable[69] = 12.290; _conversionTable[70] = 12.300;
  _conversionTable[71] = 12.310; _conversionTable[72] = 12.320; _conversionTable[73] = 12.330; _conversionTable[74] = 12.340; _conversionTable[75] = 12.350;
  _conversionTable[76] = 12.360; _conversionTable[77] = 12.370; _conversionTable[78] = 12.380; _conversionTable[79] = 12.390; _conversionTable[80] = 12.400;
  _conversionTable[81] = 12.410; _conversionTable[82] = 12.420; _conversionTable[83] = 12.430; _conversionTable[84] = 12.440; _conversionTable[85] = 12.450;
  _conversionTable[86] = 12.460; _conversionTable[87] = 12.470; _conversionTable[88] = 12.480; _conversionTable[89] = 12.490; _conversionTable[90] = 12.500;
  _conversionTable[91] = 12.520; _conversionTable[92] = 12.540; _conversionTable[93] = 12.560; _conversionTable[94] = 12.580; _conversionTable[95] = 12.600;
  _conversionTable[96] = 12.620; _conversionTable[97] = 12.640; _conversionTable[98] = 12.660; _conversionTable[99] = 12.680; _conversionTable[100] = 12.700;
  }


  if(BATTTYPE == 2){
  _conversionTable = (double*)malloc(sizeof(double)*101); //AGM
  _conversionTable[0] = 10.700;
  _conversionTable[1] = 10.780;  _conversionTable[2] = 10.860; _conversionTable[3] = 10.940; _conversionTable[4] = 11.020; _conversionTable[5] = 11.100;
  _conversionTable[6] = 11.180; _conversionTable[7] = 11.260; _conversionTable[8] = 11.340; _conversionTable[9] = 11.420; _conversionTable[10] = 11.500;
  _conversionTable[11] = 11.520; _conversionTable[12] = 11.540; _conversionTable[13] = 11.560; _conversionTable[14] = 11.580; _conversionTable[15] = 11.600;
  _conversionTable[16] = 11.620; _conversionTable[17] = 11.640; _conversionTable[18] = 11.660; _conversionTable[19] = 11.680; _conversionTable[20] = 11.700;
  _conversionTable[21] = 11.720; _conversionTable[22] = 11.740; _conversionTable[23] = 11.760; _conversionTable[24] = 11.780; _conversionTable[25] = 11.800;
  _conversionTable[26] = 11.820; _conversionTable[27] = 11.840; _conversionTable[28] = 11.860; _conversionTable[29] = 11.880; _conversionTable[30] = 11.900;
  _conversionTable[31] = 11.910; _conversionTable[32] = 11.920; _conversionTable[33] = 11.930; _conversionTable[34] = 11.940; _conversionTable[35] = 11.950;
  _conversionTable[36] = 11.960; _conversionTable[37] = 11.970; _conversionTable[38] = 11.980; _conversionTable[39] = 11.990; _conversionTable[40] = 12.000;
  _conversionTable[41] = 12.020; _conversionTable[42] = 12.040; _conversionTable[43] = 12.060; _conversionTable[44] = 12.080; _conversionTable[45] = 12.100;
  _conversionTable[46] = 12.120; _conversionTable[47] = 12.140; _conversionTable[48] = 12.160; _conversionTable[49] = 12.180; _conversionTable[50] = 12.200;
  _conversionTable[51] = 12.210; _conversionTable[52] = 12.220; _conversionTable[53] = 12.230; _conversionTable[54] = 12.240; _conversionTable[55] = 12.250;
  _conversionTable[56] = 12.260; _conversionTable[57] = 12.270; _conversionTable[58] = 12.280; _conversionTable[59] = 12.290; _conversionTable[60] = 12.300;
  _conversionTable[61] = 12.310; _conversionTable[62] = 12.320; _conversionTable[63] = 12.330; _conversionTable[64] = 12.340; _conversionTable[65] = 12.350;
  _conversionTable[66] = 12.360; _conversionTable[67] = 12.370; _conversionTable[68] = 12.380; _conversionTable[69] = 12.390; _conversionTable[70] = 12.400;
  _conversionTable[71] = 12.420; _conversionTable[72] = 12.440; _conversionTable[73] = 12.460; _conversionTable[74] = 12.480; _conversionTable[75] = 12.500;
  _conversionTable[76] = 12.520; _conversionTable[77] = 12.540; _conversionTable[78] = 12.560; _conversionTable[79] = 12.580; _conversionTable[80] = 12.600;
  _conversionTable[81] = 12.610; _conversionTable[82] = 12.620; _conversionTable[83] = 12.630; _conversionTable[84] = 12.640; _conversionTable[85] = 12.650;
  _conversionTable[86] = 12.660; _conversionTable[87] = 12.670; _conversionTable[88] = 12.680; _conversionTable[89] = 12.690; _conversionTable[90] = 12.700;
  _conversionTable[91] = 12.720; _conversionTable[92] = 12.740; _conversionTable[93] = 12.760; _conversionTable[94] = 12.780; _conversionTable[95] = 12.800;
  _conversionTable[96] = 12.820; _conversionTable[97] = 12.840; _conversionTable[98] = 12.860; _conversionTable[99] = 12.880; _conversionTable[100] = 12.900;
  }


  if(BATTTYPE == 3){
  _conversionTable = (double*)malloc(sizeof(double)*101); //GEL
  _conversionTable[0] = 10.800;
  _conversionTable[1] = 10.880;  _conversionTable[2] = 10.960; _conversionTable[3] = 11.040; _conversionTable[4] = 11.120; _conversionTable[5] = 11.200;
  _conversionTable[6] = 11.280; _conversionTable[7] = 11.360; _conversionTable[8] = 11.440; _conversionTable[9] = 11.520; _conversionTable[10] = 11.600;
  _conversionTable[11] = 11.620; _conversionTable[12] = 11.640; _conversionTable[13] = 11.660; _conversionTable[14] = 11.680; _conversionTable[15] = 11.700;
  _conversionTable[16] = 11.720; _conversionTable[17] = 11.740; _conversionTable[18] = 11.760; _conversionTable[19] = 11.780; _conversionTable[20] = 11.800;
  _conversionTable[21] = 11.830; _conversionTable[22] = 11.860; _conversionTable[23] = 11.890; _conversionTable[24] = 11.920; _conversionTable[25] = 11.950;
  _conversionTable[26] = 11.980; _conversionTable[27] = 12.010; _conversionTable[28] = 12.040; _conversionTable[29] = 12.070; _conversionTable[30] = 12.100;
  _conversionTable[31] = 12.110; _conversionTable[32] = 12.120; _conversionTable[33] = 12.130; _conversionTable[34] = 12.140; _conversionTable[35] = 12.150;
  _conversionTable[36] = 12.160; _conversionTable[37] = 12.170; _conversionTable[38] = 12.180; _conversionTable[39] = 12.190; _conversionTable[40] = 12.200;
  _conversionTable[41] = 12.210; _conversionTable[42] = 12.220; _conversionTable[43] = 12.230; _conversionTable[44] = 12.240; _conversionTable[45] = 12.250;
  _conversionTable[46] = 12.260; _conversionTable[47] = 12.270; _conversionTable[48] = 12.280; _conversionTable[49] = 12.290; _conversionTable[50] = 12.300;
  _conversionTable[51] = 12.310; _conversionTable[52] = 12.320; _conversionTable[53] = 12.330; _conversionTable[54] = 12.340; _conversionTable[55] = 12.350;
  _conversionTable[56] = 12.360; _conversionTable[57] = 12.370; _conversionTable[58] = 12.380; _conversionTable[59] = 12.390; _conversionTable[60] = 12.400;
  _conversionTable[61] = 12.410; _conversionTable[62] = 12.420; _conversionTable[63] = 12.430; _conversionTable[64] = 12.440; _conversionTable[65] = 12.450;
  _conversionTable[66] = 12.460; _conversionTable[67] = 12.470; _conversionTable[68] = 12.480; _conversionTable[69] = 12.490; _conversionTable[70] = 12.500;
  _conversionTable[71] = 12.520; _conversionTable[72] = 12.540; _conversionTable[73] = 12.560; _conversionTable[74] = 12.580; _conversionTable[75] = 12.600;
  _conversionTable[76] = 12.620; _conversionTable[77] = 12.640; _conversionTable[78] = 12.660; _conversionTable[79] = 12.680; _conversionTable[80] = 12.700;
  _conversionTable[81] = 12.710; _conversionTable[82] = 12.720; _conversionTable[83] = 12.730; _conversionTable[84] = 12.740; _conversionTable[85] = 12.750;
  _conversionTable[86] = 12.760; _conversionTable[87] = 12.770; _conversionTable[88] = 12.780; _conversionTable[89] = 12.790; _conversionTable[90] = 12.800;
  _conversionTable[91] = 12.820; _conversionTable[92] = 12.840; _conversionTable[93] = 12.860; _conversionTable[94] = 12.880; _conversionTable[95] = 12.900;
  _conversionTable[96] = 12.920; _conversionTable[97] = 12.940; _conversionTable[98] = 12.960; _conversionTable[99] = 12.980; _conversionTable[100] = 13.000;
  }


  if(BATTTYPE == 4){
  _conversionTable = (double*)malloc(sizeof(double)*101); //LIFEPO4
  _conversionTable[0] = 10.000;
  _conversionTable[1] = 10.200;  _conversionTable[2] = 10.400; _conversionTable[3] = 10.600; _conversionTable[4] = 10.800; _conversionTable[5] = 11.000;
  _conversionTable[6] = 11.200; _conversionTable[7] = 11.400; _conversionTable[8] = 11.600; _conversionTable[9] = 11.800; _conversionTable[10] = 12.000;
  _conversionTable[11] = 12.080; _conversionTable[12] = 12.160; _conversionTable[13] = 12.240; _conversionTable[14] = 12.320; _conversionTable[15] = 12.400;
  _conversionTable[16] = 12.480; _conversionTable[17] = 12.560; _conversionTable[18] = 12.640; _conversionTable[19] = 12.720; _conversionTable[20] = 12.800;
  _conversionTable[21] = 12.810; _conversionTable[22] = 12.820; _conversionTable[23] = 12.830; _conversionTable[24] = 12.840; _conversionTable[25] = 12.850;
  _conversionTable[26] = 12.860; _conversionTable[27] = 12.870; _conversionTable[28] = 12.880; _conversionTable[29] = 12.890; _conversionTable[30] = 12.900;
  _conversionTable[31] = 12.905; _conversionTable[32] = 12.910; _conversionTable[33] = 12.915; _conversionTable[34] = 12.920; _conversionTable[35] = 12.925;
  _conversionTable[36] = 12.930; _conversionTable[37] = 12.935; _conversionTable[38] = 12.940; _conversionTable[39] = 12.945; _conversionTable[40] = 12.950;
  _conversionTable[41] = 12.955; _conversionTable[42] = 12.960; _conversionTable[43] = 12.965; _conversionTable[44] = 12.970; _conversionTable[45] = 12.975;
  _conversionTable[46] = 12.980; _conversionTable[47] = 12.985; _conversionTable[48] = 12.990; _conversionTable[49] = 12.995; _conversionTable[50] = 13.000;
  _conversionTable[51] = 13.010; _conversionTable[52] = 13.020; _conversionTable[53] = 13.030; _conversionTable[54] = 13.040; _conversionTable[55] = 13.050;
  _conversionTable[56] = 13.060; _conversionTable[57] = 13.070; _conversionTable[58] = 13.080; _conversionTable[59] = 13.090; _conversionTable[60] = 13.100;
  _conversionTable[61] = 13.110; _conversionTable[62] = 13.120; _conversionTable[63] = 13.130; _conversionTable[64] = 13.140; _conversionTable[65] = 13.150;
  _conversionTable[66] = 13.160; _conversionTable[67] = 13.170; _conversionTable[68] = 13.180; _conversionTable[69] = 13.190; _conversionTable[70] = 13.200;
  _conversionTable[71] = 13.210; _conversionTable[72] = 13.220; _conversionTable[73] = 13.230; _conversionTable[74] = 13.240; _conversionTable[75] = 13.250;
  _conversionTable[76] = 13.260; _conversionTable[77] = 13.270; _conversionTable[78] = 13.280; _conversionTable[79] = 13.290; _conversionTable[80] = 13.300;
  _conversionTable[81] = 13.310; _conversionTable[82] = 13.320; _conversionTable[83] = 13.330; _conversionTable[84] = 13.340; _conversionTable[85] = 13.350;
  _conversionTable[86] = 13.360; _conversionTable[87] = 13.370; _conversionTable[88] = 13.380; _conversionTable[89] = 13.390; _conversionTable[90] = 13.400;
  _conversionTable[91] = 13.420; _conversionTable[92] = 13.440; _conversionTable[93] = 13.460; _conversionTable[94] = 13.480; _conversionTable[95] = 13.500;
  _conversionTable[96] = 13.520; _conversionTable[97] = 13.540; _conversionTable[98] = 13.560; _conversionTable[99] = 13.580; _conversionTable[100] = 13.600;
  }


  if(BATTTYPE == 5){
  _conversionTable = (double*)malloc(sizeof(double)*101); //CUSTOM
  _conversionTable[0] = 10.500;
  _conversionTable[1] = 10.580;  _conversionTable[2] = 10.660; _conversionTable[3] = 10.740; _conversionTable[4] = 10.820; _conversionTable[5] = 10.900;
  _conversionTable[6] = 10.980; _conversionTable[7] = 11.060; _conversionTable[8] = 11.140; _conversionTable[9] = 11.220; _conversionTable[10] = 11.300;
  _conversionTable[11] = 11.330; _conversionTable[12] = 11.360; _conversionTable[13] = 11.390; _conversionTable[14] = 11.420; _conversionTable[15] = 11.450;
  _conversionTable[16] = 11.480; _conversionTable[17] = 11.510; _conversionTable[18] = 11.540; _conversionTable[19] = 11.570; _conversionTable[20] = 11.600;
  _conversionTable[21] = 11.620; _conversionTable[22] = 11.640; _conversionTable[23] = 11.660; _conversionTable[24] = 11.680; _conversionTable[25] = 11.700;
  _conversionTable[26] = 11.720; _conversionTable[27] = 11.740; _conversionTable[28] = 11.760; _conversionTable[29] = 11.780; _conversionTable[30] = 11.800;
  _conversionTable[31] = 11.810; _conversionTable[32] = 11.820; _conversionTable[33] = 11.830; _conversionTable[34] = 11.840; _conversionTable[35] = 11.850;
  _conversionTable[36] = 11.860; _conversionTable[37] = 11.870; _conversionTable[38] = 11.880; _conversionTable[39] = 11.890; _conversionTable[40] = 11.900;
  _conversionTable[41] = 11.920; _conversionTable[42] = 11.940; _conversionTable[43] = 11.960; _conversionTable[44] = 11.980; _conversionTable[45] = 12.000;
  _conversionTable[46] = 12.020; _conversionTable[47] = 12.040; _conversionTable[48] = 12.060; _conversionTable[49] = 12.080; _conversionTable[50] = 12.100;
  _conversionTable[51] = 12.110; _conversionTable[52] = 12.120; _conversionTable[53] = 12.130; _conversionTable[54] = 12.140; _conversionTable[55] = 12.150;
  _conversionTable[56] = 12.160; _conversionTable[57] = 12.170; _conversionTable[58] = 12.180; _conversionTable[59] = 12.190; _conversionTable[60] = 12.200;
  _conversionTable[61] = 12.210; _conversionTable[62] = 12.220; _conversionTable[63] = 12.230; _conversionTable[64] = 12.240; _conversionTable[65] = 12.250;
  _conversionTable[66] = 12.260; _conversionTable[67] = 12.270; _conversionTable[68] = 12.280; _conversionTable[69] = 12.290; _conversionTable[70] = 12.300;
  _conversionTable[71] = 12.310; _conversionTable[72] = 12.320; _conversionTable[73] = 12.330; _conversionTable[74] = 12.340; _conversionTable[75] = 12.350;
  _conversionTable[76] = 12.360; _conversionTable[77] = 12.370; _conversionTable[78] = 12.380; _conversionTable[79] = 12.390; _conversionTable[80] = 12.400;
  _conversionTable[81] = 12.410; _conversionTable[82] = 12.420; _conversionTable[83] = 12.430; _conversionTable[84] = 12.440; _conversionTable[85] = 12.450;
  _conversionTable[86] = 12.460; _conversionTable[87] = 12.470; _conversionTable[88] = 12.480; _conversionTable[89] = 12.490; _conversionTable[90] = 12.500;
  _conversionTable[91] = 12.520; _conversionTable[92] = 12.540; _conversionTable[93] = 12.560; _conversionTable[94] = 12.580; _conversionTable[95] = 12.600;
  _conversionTable[96] = 12.620; _conversionTable[97] = 12.640; _conversionTable[98] = 12.660; _conversionTable[99] = 12.680; _conversionTable[100] = 12.700;
  }
}



int BatteryStatsADS1115::_getChargeLevelFromConversionTable(double volts) {
  if (_conversionTable == nullptr) {
    _initConversionTable();
  }

  int index = 50;
  int previousIndex = 0;
  int half = 0;

  while(previousIndex != index) {
    half = abs(index - previousIndex) / 2;
    previousIndex = index;
    if (_conversionTable[index] == volts) {
      return index;
    }
    index = (volts >= _conversionTable[index])
       ? index + half
       : index - half;
  }

  return index;
}

void BatteryStatsADS1115::send_adcValue(double adcValue){
  _adcValue = adcValue;
}

double BatteryStatsADS1115::_analogReadToVolts(int readValue) {
  return readValue * CONVFACTOR / 1000;
}

void BatteryStatsADS1115::set_conversionFactor(double convFactor){
  CONVFACTOR = convFactor;
}

void BatteryStatsADS1115::set_battType(int battType){
  BATTTYPE = battType;
  if (_conversionTable != nullptr) {
    _initConversionTable();
  }
}

double BatteryStatsADS1115::get_conversionFactor(){
  return CONVFACTOR;
}

int BatteryStatsADS1115::get_battType(){
  return BATTTYPE;
}

double BatteryStatsADS1115::get_adcValue(){
  return _adcValue;
}
