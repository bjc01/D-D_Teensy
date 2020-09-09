//DRONE 
//three sine oscillators - very close - creates modulations in amplitude
// PINK NOISE + FILTER 
//v6 - remove waveshaper - ADD BITCRUSHER
//waveshape
//add Bounce.h

#include <Bounce.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      pink1;          //xy=128,277
AudioSynthWaveform       waveform2;      //xy=170,161
AudioSynthWaveform       waveform3;      //xy=173,214
AudioSynthWaveform       waveform1;      //xy=179,87
AudioFilterStateVariable filter1;        //xy=262,312
AudioEffectBitcrusher    bitcrusher1;    //xy=425,291
AudioMixer4              mixer1;         //xy=523,143
AudioOutputI2S           i2s1;           //xy=674,144
AudioConnection          patchCord1(pink1, 0, filter1, 0);
AudioConnection          patchCord2(pink1, 0, filter1, 1);
AudioConnection          patchCord3(waveform2, 0, mixer1, 1);
AudioConnection          patchCord4(waveform3, 0, mixer1, 2);
AudioConnection          patchCord5(waveform1, 0, mixer1, 0);
AudioConnection          patchCord6(filter1, 0, bitcrusher1, 0);
AudioConnection          patchCord7(bitcrusher1, 0, mixer1, 3);
AudioConnection          patchCord8(mixer1, 0, i2s1, 0);
AudioConnection          patchCord9(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=501,357
// GUItool: end automatically generated code

// GUItool: end automatically generated code

// Bounce objects to read pushbuttons - cutnpaste from part_2_07_Filters
//not needed for D&D yet
/*
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time
Bounce button2 = Bounce(2, 15);
 */
 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.75);
  waveform1.frequency(55);

  waveform2.begin(WAVEFORM_SINE);
  waveform2.amplitude(0.75);
  waveform2.frequency(110);

  waveform3.begin(WAVEFORM_SINE);
  waveform3.amplitude(0.75);
  waveform3.frequency(220);

  pink1.amplitude(1.0);

  mixer1.gain(0, 0.7);
  mixer1.gain(1, 0.7);
  mixer1.gain(2, 0.7);
  mixer1.gain(3, 0.6);
  delay(1000);

  filter1.frequency(65);
  filter1.resonance(4.9); 
  //Q ranges from 0.7 to 5.0. Resonance greater than 0.707 will amplify the signal near the corner frequency. 
  //You must attenuate the signal before input to this filter, to prevent clipping.

  bitcrusher1.bits(8); 
  bitcrusher1.sampleRate(22050);
  /*xcrushBits sets the bitdepth, from 1 to 16. 
   * A Value of 16 does not crush the bitdepth, and is effectively a passthru for this part of the function.
   * 
   * xsampleRate sets the frequency, from 1 to 44100Hz, 
   * however it works in integer steps so you will only really get a handful of results from the many samplerates you can pass. 44100 is passthru.
   * 
   * set xbitDepth to 16 and xsampleRate to 44100 to pass audio through without any Bitcrush effect.

/*set xbitDepth to 16 and xsampleRate to 44100 to pass audio through without any Bitcrush effect.
 * 
 */
  }

void loop() {
  // put your main code here, to run repeatedly:
{
 }

  // Read the knobs, scale knobs to 0-1.0 - WaveformsModulated
  
  float knob_A0 = (float)analogRead(A0);
  float knob_A1 = (float)analogRead(A1);
  float knob_A2 = (float)analogRead(A2);
  float knob_A3 = (float)analogRead(A3);
  float knob_A4 = (float)analogRead(A4) / 1023.0;
  float knob_A5 = (float)analogRead(A5) / 1023.0;
  float knob_A6 = (float)analogRead(A6) / 1023.0;
  float knob_A7 = (float)analogRead(A7) / 1023.0;

  // use Knobs to adjust the waveform frequency
  waveform1.frequency(knob_A0);
  waveform2.frequency(knob_A1);
  waveform3.frequency(knob_A2);
  filter1.frequency(knob_A3);
  
  // pink1.(knob_A3); - some DRAMA filter cutoff effect parameter
    // use Knobs to adjust the amount of waveform amplitude
  waveform1.amplitude(knob_A4);
  waveform2.amplitude(knob_A5);
  waveform2.amplitude(knob_A6);
  pink1.amplitude(knob_A7);
  
  // read the knob and adjust the filter frequency DRAMA
  int knob = analogRead(A3);
  // quick and dirty equation for exp scale frequency adjust
  float freq =  expf((float)knob / 150.0) * 10.0 + 80.0;
  filter1.frequency(freq);
  Serial.print("frequency = ");
  Serial.println(freq);
  delay(100);
  
 }
